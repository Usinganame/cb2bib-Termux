/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "document.h"

#include "cb2bib_utilities.h"
#include "settings.h"

#include <QProcess>


document::document(const QString& fn, const Conversion mode)
{
    _document_fn = fn.trimmed();
    settings* settingsP = settings::instance();
    _converter_output = settingsP->tempPath() + "/cb2bib_document_conversion_tmp_" + settingsP->applicationPid();
    setConverter(mode);
}


QString document::fileToString(const QString& fn)
{
    _document_fn = fn.trimmed();
    return toString();
}

QString document::toString()
{
    _error_string.clear();
    _log_string.clear();
    if (_document_fn.isEmpty())
        return QString();
    QFileInfo fbin(_converter_bin);
    if (fbin.isAbsolute())
        if (!fbin.exists() || !fbin.isFile())
        {
            _error_string = QObject::tr("Converter %1 does not exist\n").arg(_converter_bin);
            return QString();
        }
    QFileInfo fi(_document_fn);
    if (!fi.exists() || !fi.isFile())
    {
        _error_string = QObject::tr("File %1 does not exist\n").arg(_document_fn);
        return QString();
    }

    QProcess converter;
    QStringList args(_converter_arg.split(' ', QString::SkipEmptyParts));
    args.append(_document_fn);
    args.append(_converter_output);
    converter.start(_converter_bin, args);
    if (!converter.waitForStarted())
    {
        _error_string += QObject::tr("Converter '%1 %2' could not be started. Check file permissions and path\n")
                         .arg(_converter_bin, _converter_arg);
        return QString();
    }
    if (!converter.waitForFinished(_conversion_mode == Complete ? -1 : 150000))
    {
        converter.kill();
        c2bUtils::warn(QObject::tr("Error: Document conversion timeout for file '%1'").arg(_document_fn));
    }
    QString doc(c2bUtils::fileToString(_converter_output, true));
    _log_string = QString::fromUtf8(converter.readAllStandardOutput().trimmed());
    _log_string += '\n' + QString::fromUtf8(converter.readAllStandardError().trimmed());
    if (converter.exitStatus() != QProcess::NormalExit || doc.isEmpty())
    {
        _error_string +=
            QObject::tr("[%1 %2] Conversion failed for file %3\n").arg(_converter_bin, _converter_arg, _document_fn);
        c2bUtils::warn(QObject::tr("Warning: Text conversion for file '%1' is empty").arg(_document_fn));
        return QString();
    }

    normalize(doc, _conversion_mode);

    // Recheck in case normalize reveals badly encoded PDFs
    if (doc.isEmpty())
        c2bUtils::warn(QObject::tr("Warning: Text conversion for file '%1' is empty").arg(_document_fn));

    return doc;
}

QString& document::normalize(QString& doc, const Conversion mode)
{
    if (doc.length() == 0)
        return doc;

    const ushort unull(0);
    const ushort unl(10);
    const ushort uspace(32);
    const ushort uhyp(45);

    bool hgrave(false);
    bool hdieresis(false);
    bool haccute(false);
    bool hcedilla(false);
    bool hcircumflex(false);
    bool hcaron(false);
    bool hring(false);
    bool htilde(false);

    bool hreg(false);
    bool hligatures(false);

    ushort* const c0((ushort*)doc.data());
    const ushort* const cn(c0 + doc.length());
    ushort* c(c0 - 1);

    while (c < cn)
    {
        ++c;

        ushort& uc(*c);
        if (uc > 96 && uc < 127)
            continue;
        if (uc > 31 && uc < 94)
            continue;

        const QChar::Category ct(QChar::category(uc));

        if (ct == QChar::Mark_NonSpacing)
            uc = unull;
        else if (ct == QChar::Mark_SpacingCombining)
            uc = uspace;
        else if (ct == QChar::Mark_Enclosing)
            uc = uspace;
        else if (ct == QChar::Separator_Space)
            uc = uspace;
        else if (ct == QChar::Separator_Paragraph)
            uc = unl;
        else if (ct == QChar::Other_Control)
        {
            if (uc == 10 || uc == 13)
                uc = unl;
            else
                uc = uspace;
        }
        else if (ct == QChar::Other_Format)
            uc = uc == 173 ? uhyp : unull;
        else if (ct == QChar::Other_PrivateUse)
            uc = uspace;
        else if (ct == QChar::Other_NotAssigned)
            uc = uspace;
        else if (uc == QChar::ReplacementCharacter)
            uc = uspace;

        else if (uc == 96)
            hgrave = true;
        else if (uc == 168)
            hdieresis = true;
        else if (uc == 180)
            haccute = true;
        else if (uc == 184)
            hcedilla = true;
        else if (uc == 710)
            hcircumflex = true;
        else if (uc == 711)
            hcaron = true;
        else if (uc == 730)
            hring = true;
        else if (uc == 732)
            htilde = true;

        // Normalize apostrophe
        else if (uc == 8216 || uc == 8217)
            uc = 39;

        // Normalize comma
        else if (uc == 65292)
            uc = 44;

        // Normalize quotation
        else if (uc == 8220 || uc == 8221 || uc == 65282)
            uc = 34;

        // Normalize separator
        else if ((uc > 8207 && uc < 8213) || uc == 8722)
            uc = uhyp;

        // Corrections
        else if (uc == 174)
            hreg = true;
        else if (uc == 305)
            uc = 105;
        else if (uc == 1001)
            uc = 43;
        else if (uc == 1002 || uc == 1003)
            uc = 45;
        else if (uc == 306 || uc == 307 || uc == 455 || uc == 460 || uc == 498 || uc == 64256 || uc == 64257 ||
                 uc == 64258 || uc == 64259 || uc == 64260)
            hligatures = true;
    }

    // Diacritics from legacy PDFs are set to text in several manners:
    // - an orphan diacritic is set either before or after the letter
    // - an orphan diacritic might be followed by one or more spaces, resulting in broken words
    // These deficiencies impact on indexing and searching
    // In the following
    // - an orphan diacritic is re-set to the most probably accented letters
    // - extra spaces are removed whenever the risk of joining two independent words is low
    if (haccute)
    {
        const ushort uaccute(180);
        c = c0 + 1;
        const ushort* const cm(cn - 2);
        while (c < cm)
        {
            if (*c == uaccute && *(c + 1) == uspace)
            {
                const QChar r(*(c - 1));
                const QChar s(*(c + 2));
                if (r.isLetter())
                    if ((r.isUpper() && s.isLetter()) || s.category() == QChar::Punctuation_Dash ||
                        s.category() == QChar::Punctuation_Other || s.isSpace())
                        *(c + 1) = unull;
            }
            ++c;
        }
    }

    // Revert hyphenation (skip for FirstPage mode to preserve layout)
    if (mode == Complete)
    {
        c = c0 + 1;
        const ushort* const cm(cn - 2);

        while (c < cm)
        {
            if (*c == uhyp)
            {
                const QChar r(*(c - 1));
                if (r.isLetter())
                {
                    ushort* cs(c);
                    bool h(false);
                    while (cs < cn)
                        if (QChar(*(++cs)).isLetter())
                            break;
                        else if (*cs == unl)
                            h = true;
                        else if (*cs != uspace)
                        {
                            h = false;
                            break;
                        }
                    if (h && cs < cn)
                    {
                        QString testw;
                        for (ushort* cw = c - 1; cw > c0; --cw)
                            if (QChar(*cw).isLetter())
                                testw.prepend(QChar(*cw));
                            else
                                break;
                        testw.append(QChar(uhyp));
                        for (ushort* cw = cs; cw < cn; ++cw)
                            if (QChar(*cw).isLetter())
                                testw.append(QChar(*cw));
                            else
                                break;
                        const QChar s(*cs);

                        // Avoid de-hyphenating 'divide-and-conquer' like cases by checking the word in document
                        if (doc.contains(testw))
                            ++c;
                        // Avoid de-hyphenating 'Hartree-Fock' like cases; replace hyphen by space
                        else if ((r.isLower() && s.isUpper()) || (r.isUpper() && s.isLower()))
                            *(c++) = uspace;

                        for (ushort* z = c; z < cs; ++z)
                            *z = unull;
                        c = cs + 1;
                    }
                }
            }
            ++c;
        }
    }

    // Clear extra spaces on enclosing marks
    {
        c = c0;
        while (c < cn)
        {
            ++c;

            ushort& uc(*c);
            if (uc < 40)
                continue;
            if (uc > 41 && uc < 91)
                continue;
            if (uc > 93 && uc < 123)
                continue;

            const QChar::Category ct(QChar::category(uc));
            if (ct == QChar::Punctuation_Open)
            {
                for (ushort* co = c + 1; co < cn; ++co)
                    if (*co == uspace || *co == unl || *co == unull)
                        *co = unull;
                    else
                        break;
            }
            else if (ct == QChar::Punctuation_Close)
            {
                for (ushort* cc = c - 1; cc > c0; --cc)
                    if (*cc == uspace || *cc == unl || *cc == unull)
                        *cc = unull;
                    else
                        break;
            }
        }
    }

    // Remove null characters (djvutxt end of page, and other control characters)
    doc.remove(QChar(unull));

    if (hreg)
    {
        // Correct frequent misencoding of "fi" as circle R in PDFs (Adobe Standard Encoding)
        doc.replace(QRegExp(QString("%1([a-z])").arg(QChar(174))), "fi\\1");
    }
    if (hligatures)
    {
        // Revert Latin ligatures
        doc.replace(QChar(306), "IJ");
        doc.replace(QChar(307), "ij");
        doc.replace(QChar(455), "LJ");
        doc.replace(QChar(460), "nj");
        doc.replace(QChar(498), "Dz");
        doc.replace(QChar(64256), "ff");
        doc.replace(QChar(64257), "fi");
        doc.replace(QChar(64258), "fl");
        doc.replace(QChar(64259), "ffi");
        doc.replace(QChar(64260), "ffl");
    }
    if (hgrave)
    {
        const QChar grave(96);
        doc.replace('a' + grave, QChar(224));
        doc.replace(grave + 'a', QChar(224));
        doc.replace('e' + grave, QChar(232));
        doc.replace(grave + 'e', QChar(232));
        doc.replace('o' + grave, QChar(242));
        doc.replace('u' + grave, QChar(249));
        doc.replace('y' + grave, QChar(7923));
        doc.replace('A' + grave, QChar(192));
        doc.replace('E' + grave, QChar(200));
        doc.replace('O' + grave, QChar(210));
    }
    if (hdieresis)
    {
        const QChar dieresis(168);
        doc.replace(QRegExp(dieresis + ' ' + '+'), dieresis);
        doc.replace(dieresis + ' ', dieresis);
        doc.replace('a' + dieresis, QChar(228));
        doc.replace('e' + dieresis, QChar(235));
        doc.replace('i' + dieresis, QChar(239));
        doc.replace('o' + dieresis, QChar(246));
        doc.replace('u' + dieresis, QChar(252));
        doc.replace('A' + dieresis, QChar(196));
        doc.replace('E' + dieresis, QChar(203));
        doc.replace('I' + dieresis, QChar(207));
        doc.replace('O' + dieresis, QChar(214));
        doc.replace('U' + dieresis, QChar(220));
        doc.replace(dieresis + 'a', QChar(228));
        doc.replace(dieresis + 'e', QChar(235));
        doc.replace(dieresis + 'i', QChar(239));
        doc.replace(dieresis + 'o', QChar(246));
        doc.replace(dieresis + 'u', QChar(252));
        doc.replace(dieresis + 'A', QChar(196));
        doc.replace(dieresis + 'E', QChar(203));
        doc.replace(dieresis + 'I', QChar(207));
        doc.replace(dieresis + 'O', QChar(214));
        doc.replace(dieresis + 'U', QChar(220));
    }
    if (haccute)
    {
        const QChar accute(180);
        doc.replace('e' + accute, QChar(233));
        doc.replace(accute + 'e', QChar(233));
        doc.replace('A' + accute, QChar(193));
        doc.replace(accute + 'A', QChar(193));
        doc.replace('a' + accute, QChar(225));
        doc.replace(accute + 'a', QChar(225));
        doc.replace('o' + accute, QChar(243));
        doc.replace(accute + 'o', QChar(243));
        doc.replace('i' + accute, QChar(237));
        doc.replace(accute + 'i', QChar(237));
        doc.replace('E' + accute, QChar(201));
        doc.replace(accute + 'E', QChar(201));
        doc.replace('u' + accute, QChar(250));
        doc.replace(accute + 'u', QChar(250));
        doc.replace('O' + accute, QChar(211));
        doc.replace(accute + 'O', QChar(211));
        doc.replace('I' + accute, QChar(205));
        doc.replace(accute + 'I', QChar(205));
        doc.replace('U' + accute, QChar(218));
        doc.replace(accute + 'U', QChar(218));
        doc.replace('c' + accute, QChar(263));
        doc.replace('C' + accute, QChar(262));
        doc.replace('y' + accute, QChar(253));
        doc.replace('Y' + accute, QChar(221));
    }
    if (hcedilla)
    {
        const QChar cedilla(184);
        doc.replace('c' + cedilla, QChar(231));
        doc.replace(cedilla + 'c', QChar(231));
        doc.replace('C' + cedilla, QChar(199));
        doc.replace(cedilla + 'C', QChar(199));
        doc.replace('s' + cedilla, QChar(351));
        doc.replace(cedilla + 's', QChar(351));
        doc.replace('S' + cedilla, QChar(350));
        doc.replace(cedilla + 'S', QChar(350));
        doc.replace('e' + cedilla, QChar(553));
        doc.replace(cedilla + 'e', QChar(553));
        doc.replace('E' + cedilla, QChar(552));
        doc.replace(cedilla + 'E', QChar(552));
    }
    if (hcircumflex)
    {
        const QChar circumflex(710);
        doc.replace('a' + circumflex, QChar(226));
        doc.replace(circumflex + 'a', QChar(226));
        doc.replace('e' + circumflex, QChar(234));
        doc.replace(circumflex + 'e', QChar(234));
        doc.replace('i' + circumflex, QChar(238));
        doc.replace(circumflex + 'i', QChar(238));
        doc.replace('o' + circumflex, QChar(244));
        doc.replace(circumflex + 'o', QChar(244));
    }
    if (hcaron)
    {
        const QChar caron(711);
        doc.replace('c' + caron, QChar(269));
        doc.replace(caron + 'c', QChar(269));
        doc.replace('C' + caron, QChar(268));
        doc.replace(caron + 'C', QChar(268));
        doc.replace('z' + caron, QChar(382));
        doc.replace(caron + 'z', QChar(382));
        doc.replace('Z' + caron, QChar(381));
        doc.replace(caron + 'Z', QChar(381));
        doc.replace('s' + caron, QChar(353));
        doc.replace(caron + 's', QChar(353));
        doc.replace('S' + caron, QChar(352));
        doc.replace(caron + 'S', QChar(352));
        doc.replace('r' + caron, QChar(345));
        doc.replace(caron + 'r', QChar(345));
        doc.replace('R' + caron, QChar(344));
        doc.replace(caron + 'R', QChar(344));
    }
    if (hring)
    {
        const QChar ring(730);
        doc.replace('a' + ring, QChar(229));
        doc.replace('A' + ring, QChar(197));
        doc.replace(ring + 'a', QChar(229));
        doc.replace(ring + 'A', QChar(197));
    }
    if (htilde)
    {
        const QChar tilde(732);
        doc.replace('n' + tilde, QChar(241));
        doc.replace('N' + tilde, QChar(209));
        doc.replace('a' + tilde, QChar(227));
        doc.replace('A' + tilde, QChar(195));
    }

    // Simplify (skip for FirstPage mode to preserve layout)
    if (mode == Complete)
        c2bUtils::simplifyString(doc);

    return doc;
}

void document::setConverter(const Conversion mode)
{
    _conversion_mode = mode;
    settings* s(settings::instance());
    switch (_conversion_mode)
    {
    case Complete:
        setConverter(s->fileName("c2bBibSearcher/Pdf2TextBin"), s->value("c2bBibSearcher/Pdf2TextArg").toString());
        break;
    case FirstPage:
    default:
        setConverter(s->fileName("c2bPdfImport/Pdf2TextBin"), s->value("c2bPdfImport/Pdf2TextArg").toString());
        break;
    }
}

void document::setConverter(const QString& bin, const QString& args)
{
    _converter_bin = bin.trimmed();
    _converter_arg = args.simplified();
}
