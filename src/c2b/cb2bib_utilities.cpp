/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "cb2bib_utilities.h"

#include "txtmatcher.h"

#include <QRegularExpressionMatchIterator>


#if defined(C2B_USE_LZSSE)
#include "./lzsse4/lzsse4.h"
#elif defined(C2B_USE_LZ4)
#include <lz4.h>
#include <lz4hc.h>
#elif defined(C2B_USE_LZO)
#include <lzo/lzo1x.h>
#include <lzo/lzoconf.h>
#endif


namespace c2bUtils
{

const QRegExp nonAsciiLetter("[^A-Za-z]");
const QRegExp nonLetter("\\W");

const QString arxivUrl("https://arxiv.org/abs/%1");
// Link set according to: "Creating a Web Link to the Entrez Databases",
// http://www.ncbi.nlm.nih.gov/books/bv.fcgi?rid=helplinks.chapter.linkshelp#linkshelp.Retrieve_PubMed_Cita
const QString pubmedUrl("https://pubmed.ncbi.nlm.nih.gov/%1");
const QString metadatasection("\n[Raw Metadata\n%1\n/Raw Metadata]\n");

QString setCapitalization(const QString& str)
{
    QString cap_string(str);
    if (isUpperCaseString(str))
        cap_string = cap_string.toLower();
    bool do_upper(true);
    for (int i = 0; i < cap_string.length(); ++i)
        if (cap_string.at(i).isLetter())
        {
            if (do_upper)
            {
                // Check for special cases: pH, mRNA, l-Alanine, Ea.hy926, p53, α/β-barrel
                bool can_do_upper(true);
                for (int j = i + 1; j < cap_string.length(); ++j)
                    if (cap_string.at(j).isDigit() || (cap_string.at(j).isLetter() && cap_string.at(j).isUpper()) ||
                        (j - i <= 3 && cap_string.at(j) == QLatin1Char('-') && cap_string.at(i) >= QChar(945)))
                    {
                        can_do_upper = false;
                        break;
                    }
                    else if (cap_string.at(j) == QLatin1Char(' '))
                        break;
                if (can_do_upper)
                    cap_string[i] = cap_string.at(i).toUpper();
            }
            do_upper = false;
        }
        else if (cap_string.at(i) == QLatin1Char('.') || cap_string.at(i) == QLatin1Char(':') ||
                 cap_string.at(i) == QLatin1Char('?'))
            do_upper = true;
        else if (cap_string.at(i) != QLatin1Char(' '))
            do_upper = false;
    return cap_string;
}

QString& simplifyString(QString& str)
{
    if (str.length() == 0)
        return str;
    const ushort space(32);
    ushort* const c0 = (ushort*)str.data();
    ushort* const cn = c0 + str.length();
    ushort* c = c0;
    ushort* o = c0;
    while (c < cn)
    {
        const ushort ch = *c;
        if ((ch > 32 && ch < 160) || !(ch == space || QChar(ch).isSpace()))
            *o++ = ch;
        else if (o > c0 && *(o - 1) != space)
            *o++ = space;
        ++c;
    }
    if (o > c0 && *(o - 1) == space)
        --o;
    str.truncate(int(o - c0));
    return str;
}

QString& fillString(QString& str, const QStringMatcher& pattern, const QChar& ch)
{
    if (str.length() == 0)
        return str;
    const int pl(pattern.pattern().length());
    const ushort uch(ch.unicode());
    ushort* const c0((ushort*)str.data());
    int p(0);
    while (p >= 0)
    {
        p = pattern.indexIn(str, p);
        if (p > -1)
        {
            ushort* c(c0 + p);
            const ushort* const cpl(c + pl);
            while (c < cpl)
                *c++ = uch;
            p += pl;
        }
    }
    return str;
}

QString& fillString(QString& str, const QString& pattern, const QChar& ch)
{
    return fillString(str, QStringMatcher(pattern, Qt::CaseSensitive), ch);
}

QString& fillString(QString& str, const txtmatcher& pattern, const QChar& ch)
{
    if (str.length() == 0)
        return str;
    const int pl(pattern.pattern().length());
    const ushort uch(ch.unicode());
    ushort* const c0((ushort*)str.data());
    int p(0);
    while (p >= 0)
    {
        p = pattern.indexIn(str, p);
        if (p > -1)
        {
            ushort* c(c0 + p);
            const ushort* const cpl(c + pl);
            while (c < cpl)
                *c++ = uch;
            p += pl;
        }
    }
    return str;
}

QString& fillString(QString& str, const QRegExp& pattern, const QChar& ch)
{
    if (str.length() == 0)
        return str;
    const ushort uch(ch.unicode());
    ushort* const c0((ushort*)str.data());
    int p(0);
    while (p >= 0)
    {
        p = pattern.indexIn(str, p);
        if (p > -1)
        {
            const int pl(pattern.matchedLength());
            ushort* c(c0 + p);
            const ushort* const cpl(c + pl);
            while (c < cpl)
                *c++ = uch;
            p += pl;
        }
    }
    return str;
}

QString& fillString(QString& str, const QRegularExpression& pattern, const QChar& ch)
{
    if (str.length() == 0)
        return str;
    const ushort uch(ch.unicode());
    ushort* const c0((ushort*)str.data());
    QRegularExpressionMatchIterator it(pattern.globalMatch(str));
    while (it.hasNext())
    {
        const QRegularExpressionMatch match(it.next());
        ushort* c(c0 + match.capturedStart());
        const ushort* const cpl(c + match.capturedLength());
        while (c < cpl)
            *c++ = uch;
    }
    return str;
}

static const unsigned short _cyrillic_to_ascii[] =
{
    // Code points 1024 to 1309
    // See http://en.wikipedia.org/wiki/ISO_9
    69,   69,   68,   71,   69,   90,   73,   73,   74,   76,   78,   67,   75,   73,   85,   68,   65,   66,
    86,   71,   68,   69,   90,   90,   73,   74,   75,   76,   77,   78,   79,   80,   82,   83,   84,   85,
    70,   72,   67,   67,   83,   83,   698,  89,   697,  69,   85,   65,   97,   98,   118,  103,  100,  101,
    122,  122,  105,  106,  107,  108,  109,  110,  111,  112,  114,  115,  116,  117,  102,  104,  99,   99,
    115,  115,  698,  121,  697,  101,  117,  97,   101,  101,  100,  103,  101,  122,  105,  105,  106,  108,
    110,  99,   107,  105,  117,  100,  1120, 1121, 69,   101,  1124, 1125, 1126, 1127, 1128, 1129, 65,   97,
    1132, 1133, 1134, 1135, 1136, 1137, 70,   102,  89,   121,  89,   121,  1144, 1145, 1146, 1147, 1148, 1149,
    1150, 1151, 1152, 1153, 1154, 1155, 1156, 1157, 1158, 1159, 1160, 1161, 1162, 1163, 1164, 1165, 1166, 1167,
    71,   103,  71,   103,  71,   103,  90,   122,  1176, 1177, 75,   107,  75,   107,  75,   107,  75,   107,
    78,   110,  78,   110,  80,   112,  79,   111,  83,   115,  84,   116,  85,   117,  85,   117,  72,   104,
    67,   99,   67,   99,   67,   99,   72,   104,  67,   99,   67,   99,   1216, 90,   122,  75,   107,  76,
    108,  78,   110,  78,   110,  67,   99,   1229, 1230, 1231, 65,   97,   65,   97,   1236, 1237, 69,   101,
    65,   97,   65,   97,   90,   122,  90,   122,  90,   122,  73,   105,  73,   105,  79,   111,  79,   111,
    79,   111,  69,   101,  85,   117,  85,   117,  85,   117,  67,   99,   1270, 1271, 89,   121,  1274, 1275,
    1276, 1277, 1278, 1279, 1280, 1281, 1282, 1283, 1284, 1285, 1286, 1287, 1288, 1289, 78,   110,  1292, 1293,
    84,   116,  1296, 1297, 1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305, 81,   113,  87,   119
};

static inline QString& _to_ascii_transliterate(QString& str)
{
    // Strip diacritics, undo ligatures, transliterate
    if (str.length() == 0)
        return str;
    ushort* const c0 = (ushort*)str.data();
    ushort* const cn = c0 + str.length();
    ushort* c = c0 - 1;
    bool do_ligatures_198(false);
    bool do_ligatures_223(false);
    bool do_ligatures_230(false);
    bool do_ligatures_338(false);
    bool do_ligatures_339(false);
    while (c < cn)
    {
        ++c;
        if (*c < 128)
            continue;
        if (*c > 1023 && *c < 1310)
        {
            *c = _cyrillic_to_ascii[*c - 1024];
            if (*c == 1236)
            {
                *c = 198;
                do_ligatures_198 = true;
            }
            if (*c == 1237)
            {
                *c = 230;
                do_ligatures_230 = true;
            }
            continue;
        }
        QChar qc(*c);
        if (!qc.isLetter())
            continue;
        switch (*c)
        {
        case 216:
            *c = QChar('O').unicode();
            break;
        case 248:
            *c = QChar('o').unicode();
            break;
        case 272:
            *c = QChar('D').unicode();
            break;
        case 273:
            *c = QChar('d').unicode();
            break;
        case 321:
            *c = QChar('L').unicode();
            break;
        case 322:
            *c = QChar('l').unicode();
            break;
        case 198:
            do_ligatures_198 = true;
            break;
        case 223:
            do_ligatures_223 = true;
            break;
        case 230:
            do_ligatures_230 = true;
            break;
        case 338:
            do_ligatures_338 = true;
            break;
        case 339:
            do_ligatures_339 = true;
            break;
        }
        if (qc.decompositionTag() == QChar::NoDecomposition)
            continue;
        qc = qc.decomposition().at(0);
        *c = qc.unicode();
        if (qc.decompositionTag() == QChar::NoDecomposition)
            continue;
        qc = qc.decomposition().at(0);
        *c = qc.unicode();
    }
    if (do_ligatures_198)
        str.replace(QChar(198), "AE", Qt::CaseSensitive);
    if (do_ligatures_223)
        str.replace(QChar(223), "ss", Qt::CaseSensitive);
    if (do_ligatures_230)
        str.replace(QChar(230), "ae", Qt::CaseSensitive);
    if (do_ligatures_338)
        str.replace(QChar(338), "OE", Qt::CaseSensitive);
    if (do_ligatures_339)
        str.replace(QChar(339), "oe", Qt::CaseSensitive);
    return str;
}

static inline QString& _to_ascii_keep_words(QString& str)
{
    // Do:
    // const QRegExp nonAsciiWords("[^A-Za-z0-9\\+\\- ]");
    // str.replace(nonAsciiWords, " ");
    // str = str.simplified();
    if (str.length() == 0)
        return str;
    const ushort dash(QChar('-').unicode());
    const ushort la(QChar('a').unicode());
    const ushort lz(QChar('z').unicode());
    const ushort n0(QChar('0').unicode());
    const ushort n9(QChar('9').unicode());
    const ushort plus(QChar('+').unicode());
    const ushort space(QChar(' ').unicode());
    const ushort ua(QChar('A').unicode());
    const ushort uz(QChar('Z').unicode());

    ushort* const c0 = (ushort*)str.data();
    ushort* const cn = c0 + str.length();
    ushort* c = c0;
    ushort* o = c0;

    while (c < cn)
    {
        const ushort ch = *c;
        if ((ch >= la && ch <= lz) || (ch >= ua && ch <= uz) || (ch >= n0 && ch <= n9) || ch == dash || ch == plus)
            *o++ = ch;
        else if (o > c0 && *(o - 1) != space)
            *o++ = space;
        ++c;
    }
    if (o > c0 && *(o - 1) == space)
        --o;
    str.truncate(int(o - c0));
    return str;
}

QString toAscii(const QString& str, const AsciiConversion type)
{
    QString ascii(str);
    if (type == FromBibTeX)
        cleanEquations(ascii);
    _to_ascii_transliterate(ascii);
    if (type == Collation)
    {
        for (int i = 0; i < ascii.length(); ++i)
            if (ascii.at(i).category() == QChar::Punctuation_Dash)
                ascii[i] = QLatin1Char(' ');
        return ascii.toCaseFolded();
    }
    if (type == KeepWords || type == FromBibTeX)
        _to_ascii_keep_words(ascii);
    else if (type == Cleanup)
        ascii.remove(nonAsciiLetter);
    return ascii;
}

QString& stripDiacritics(QString& str)
{
    _to_ascii_transliterate(str);
    return str;
}

QString& c2bToBib(QString& str)
{
    // Escape common Extended Latin characters
    str.replace(QLatin1String(" &"), QLatin1String(" \\&"));
    str.replace(QChar(192), QLatin1String("{\\`A}"));
    str.replace(QChar(193), QLatin1String("{\\'A}"));
    str.replace(QChar(194), QLatin1String("{\\^A}"));
    str.replace(QChar(195), QLatin1String("{\\~A}"));
    str.replace(QChar(196), QLatin1String("{\\\"A}"));
    str.replace(QChar(197), QLatin1String("{\\AA}"));
    str.replace(QChar(198), QLatin1String("{\\AE}"));
    str.replace(QChar(199), QLatin1String("{\\c C}"));
    str.replace(QChar(200), QLatin1String("{\\`E}"));
    str.replace(QChar(201), QLatin1String("{\\'E}"));
    str.replace(QChar(202), QLatin1String("{\\^E}"));
    str.replace(QChar(203), QLatin1String("{\\\"E}"));
    str.replace(QChar(204), QLatin1String("{\\`I}"));
    str.replace(QChar(205), QLatin1String("{\\'I}"));
    str.replace(QChar(206), QLatin1String("{\\^I}"));
    str.replace(QChar(207), QLatin1String("{\\\"I}"));
    str.replace(QChar(209), QLatin1String("{\\~N}"));
    str.replace(QChar(210), QLatin1String("{\\`O}"));
    str.replace(QChar(211), QLatin1String("{\\'O}"));
    str.replace(QChar(212), QLatin1String("{\\^O}"));
    str.replace(QChar(213), QLatin1String("{\\~O}"));
    str.replace(QChar(214), QLatin1String("{\\\"O}"));
    str.replace(QChar(216), QLatin1String("{\\O}"));
    str.replace(QChar(217), QLatin1String("{\\`U}"));
    str.replace(QChar(218), QLatin1String("{\\'U}"));
    str.replace(QChar(219), QLatin1String("{\\^U}"));
    str.replace(QChar(220), QLatin1String("{\\\"U}"));
    str.replace(QChar(221), QLatin1String("{\\'Y}"));
    str.replace(QChar(223), QLatin1String("{\\ss}"));
    str.replace(QChar(224), QLatin1String("{\\`a}"));
    str.replace(QChar(225), QLatin1String("{\\'a}"));
    str.replace(QChar(226), QLatin1String("{\\^a}"));
    str.replace(QChar(227), QLatin1String("{\\~a}"));
    str.replace(QChar(228), QLatin1String("{\\\"a}"));
    str.replace(QChar(229), QLatin1String("{\\aa}"));
    str.replace(QChar(230), QLatin1String("{\\ae}"));
    str.replace(QChar(231), QLatin1String("{\\c c}"));
    str.replace(QChar(232), QLatin1String("{\\`e}"));
    str.replace(QChar(233), QLatin1String("{\\'e}"));
    str.replace(QChar(234), QLatin1String("{\\^e}"));
    str.replace(QChar(235), QLatin1String("{\\\"e}"));
    str.replace(QChar(236), QLatin1String("{\\`i}"));
    str.replace(QChar(237), QLatin1String("{\\'i}"));
    str.replace(QChar(238), QLatin1String("{\\^i}"));
    str.replace(QChar(239), QLatin1String("{\\\"i}"));
    str.replace(QChar(241), QLatin1String("{\\~n}"));
    str.replace(QChar(242), QLatin1String("{\\`o}"));
    str.replace(QChar(243), QLatin1String("{\\'o}"));
    str.replace(QChar(244), QLatin1String("{\\^o}"));
    str.replace(QChar(245), QLatin1String("{\\~o}"));
    str.replace(QChar(246), QLatin1String("{\\\"o}"));
    str.replace(QChar(248), QLatin1String("{\\o}"));
    str.replace(QChar(249), QLatin1String("{\\`u}"));
    str.replace(QChar(250), QLatin1String("{\\'u}"));
    str.replace(QChar(251), QLatin1String("{\\^u}"));
    str.replace(QChar(252), QLatin1String("{\\\"u}"));
    str.replace(QChar(253), QLatin1String("{\\'y}"));
    str.replace(QChar(255), QLatin1String("{\\\"y}"));
    str.replace(QChar(256), QLatin1String("{\\=A}"));
    str.replace(QChar(257), QLatin1String("{\\=a}"));
    str.replace(QChar(258), QLatin1String("{\\u A}"));
    str.replace(QChar(259), QLatin1String("{\\u a}"));
    str.replace(QChar(260), QLatin1String("{\\c A}"));
    str.replace(QChar(261), QLatin1String("{\\c a}"));
    str.replace(QChar(262), QLatin1String("{\\'C}"));
    str.replace(QChar(263), QLatin1String("{\\'c}"));
    str.replace(QChar(264), QLatin1String("{\\^C}"));
    str.replace(QChar(265), QLatin1String("{\\^c}"));
    str.replace(QChar(266), QLatin1String("{\\.C}"));
    str.replace(QChar(267), QLatin1String("{\\.c}"));
    str.replace(QChar(268), QLatin1String("{\\v C}"));
    str.replace(QChar(269), QLatin1String("{\\v c}"));
    str.replace(QChar(270), QLatin1String("{\\v D}"));
    str.replace(QChar(271), QLatin1String("{\\v d}"));
    str.replace(QChar(272), QLatin1String("{\\DJ}"));
    str.replace(QChar(273), QLatin1String("{\\dj}"));
    str.replace(QChar(274), QLatin1String("{\\=E}"));
    str.replace(QChar(275), QLatin1String("{\\=e}"));
    str.replace(QChar(276), QLatin1String("{\\u E}"));
    str.replace(QChar(277), QLatin1String("{\\u e}"));
    str.replace(QChar(278), QLatin1String("{\\.E}"));
    str.replace(QChar(279), QLatin1String("{\\.e}"));
    str.replace(QChar(280), QLatin1String("{\\c E}"));
    str.replace(QChar(281), QLatin1String("{\\c e}"));
    str.replace(QChar(282), QLatin1String("{\\v E}"));
    str.replace(QChar(283), QLatin1String("{\\v e}"));
    str.replace(QChar(284), QLatin1String("{\\^G}"));
    str.replace(QChar(285), QLatin1String("{\\^g}"));
    str.replace(QChar(286), QLatin1String("{\\u G}"));
    str.replace(QChar(287), QLatin1String("{\\u g}"));
    str.replace(QChar(288), QLatin1String("{\\.G}"));
    str.replace(QChar(289), QLatin1String("{\\.g}"));
    str.replace(QChar(290), QLatin1String("{\\c G}"));
    str.replace(QChar(291), QLatin1String("{\\c g}"));
    str.replace(QChar(292), QLatin1String("{\\^H}"));
    str.replace(QChar(293), QLatin1String("{\\^h}"));
    str.replace(QChar(294), QLatin1String("{\\H}"));
    str.replace(QChar(295), QLatin1String("{\\h}"));
    str.replace(QChar(296), QLatin1String("{\\~I}"));
    str.replace(QChar(297), QLatin1String("{\\~i}"));
    str.replace(QChar(298), QLatin1String("{\\=I}"));
    str.replace(QChar(299), QLatin1String("{\\=i}"));
    str.replace(QChar(300), QLatin1String("{\\u I}"));
    str.replace(QChar(301), QLatin1String("{\\u i}"));
    str.replace(QChar(302), QLatin1String("{\\c I}"));
    str.replace(QChar(303), QLatin1String("{\\c i}"));
    str.replace(QChar(304), QLatin1String("{\\.I}"));
    str.replace(QChar(305), QLatin1String("{\\i}"));
    str.replace(QChar(321), QLatin1String("{\\L}"));
    str.replace(QChar(322), QLatin1String("{\\l}"));
    str.replace(QChar(323), QLatin1String("{\\'N}"));
    str.replace(QChar(324), QLatin1String("{\\'n}"));
    str.replace(QChar(325), QLatin1String("{\\c N}"));
    str.replace(QChar(326), QLatin1String("{\\c n}"));
    str.replace(QChar(327), QLatin1String("{\\v N}"));
    str.replace(QChar(328), QLatin1String("{\\v n}"));
    str.replace(QChar(332), QLatin1String("{\\=O}"));
    str.replace(QChar(333), QLatin1String("{\\=o}"));
    str.replace(QChar(334), QLatin1String("{\\u O}"));
    str.replace(QChar(335), QLatin1String("{\\u o}"));
    str.replace(QChar(336), QLatin1String("{\\H O}"));
    str.replace(QChar(337), QLatin1String("{\\H o}"));
    str.replace(QChar(338), QLatin1String("{\\OE}"));
    str.replace(QChar(339), QLatin1String("{\\oe}"));
    str.replace(QChar(340), QLatin1String("{\\'R}"));
    str.replace(QChar(341), QLatin1String("{\\'r}"));
    str.replace(QChar(342), QLatin1String("{\\c R}"));
    str.replace(QChar(343), QLatin1String("{\\c r}"));
    str.replace(QChar(344), QLatin1String("{\\v R}"));
    str.replace(QChar(345), QLatin1String("{\\v r}"));
    str.replace(QChar(346), QLatin1String("{\\'S}"));
    str.replace(QChar(347), QLatin1String("{\\'s}"));
    str.replace(QChar(348), QLatin1String("{\\^S}"));
    str.replace(QChar(349), QLatin1String("{\\^s}"));
    str.replace(QChar(350), QLatin1String("{\\c S}"));
    str.replace(QChar(351), QLatin1String("{\\c s}"));
    str.replace(QChar(352), QLatin1String("{\\v S}"));
    str.replace(QChar(353), QLatin1String("{\\v s}"));
    str.replace(QChar(354), QLatin1String("{\\c T}"));
    str.replace(QChar(355), QLatin1String("{\\c t}"));
    str.replace(QChar(356), QLatin1String("{\\v T}"));
    str.replace(QChar(357), QLatin1String("{\\v t}"));
    str.replace(QChar(374), QLatin1String("{\\^Y}"));
    str.replace(QChar(375), QLatin1String("{\\^y}"));
    str.replace(QChar(376), QLatin1String("{\\\"Y}"));
    str.replace(QChar(377), QLatin1String("{\\'Z}"));
    str.replace(QChar(378), QLatin1String("{\\'z}"));
    str.replace(QChar(379), QLatin1String("{\\.Z}"));
    str.replace(QChar(380), QLatin1String("{\\.z}"));
    str.replace(QChar(381), QLatin1String("{\\v Z}"));
    str.replace(QChar(382), QLatin1String("{\\v z}"));
    // Escape common Greek and math
    // Some uppercases might require engrec package
    str.replace(QChar(181), QLatin1String("$\\mu$"));
    str.replace(QChar(183), QLatin1String("$\\cdot$"));
    str.replace(QChar(913), QLatin1String("$\\Alpha$"));
    str.replace(QChar(914), QLatin1String("$\\Beta$"));
    str.replace(QChar(915), QLatin1String("$\\Gamma$"));
    str.replace(QChar(916), QLatin1String("$\\Delta$"));
    str.replace(QChar(917), QLatin1String("$\\Epsilon$"));
    str.replace(QChar(918), QLatin1String("$\\Zeta$"));
    str.replace(QChar(919), QLatin1String("$\\Eta$"));
    str.replace(QChar(920), QLatin1String("$\\Theta$"));
    str.replace(QChar(921), QLatin1String("$\\Iota$"));
    str.replace(QChar(922), QLatin1String("$\\Kappa$"));
    str.replace(QChar(923), QLatin1String("$\\Lambda$"));
    str.replace(QChar(924), QLatin1String("$\\Mu$"));
    str.replace(QChar(925), QLatin1String("$\\Nu$"));
    str.replace(QChar(926), QLatin1String("$\\Xi$"));
    str.replace(QChar(927), QLatin1String("$\\Omicron$"));
    str.replace(QChar(928), QLatin1String("$\\Pi$"));
    str.replace(QChar(929), QLatin1String("$\\Rho$"));
    str.replace(QChar(931), QLatin1String("$\\Sigma$"));
    str.replace(QChar(932), QLatin1String("$\\Tau$"));
    str.replace(QChar(933), QLatin1String("$\\Upsilon$"));
    str.replace(QChar(934), QLatin1String("$\\Phi$"));
    str.replace(QChar(935), QLatin1String("$\\Chi$"));
    str.replace(QChar(936), QLatin1String("$\\Psi$"));
    str.replace(QChar(937), QLatin1String("$\\Omega$"));
    str.replace(QChar(945), QLatin1String("$\\alpha$"));
    str.replace(QChar(946), QLatin1String("$\\beta$"));
    str.replace(QChar(947), QLatin1String("$\\gamma$"));
    str.replace(QChar(948), QLatin1String("$\\delta$"));
    str.replace(QChar(949), QLatin1String("$\\varepsilon$"));
    str.replace(QChar(950), QLatin1String("$\\zeta$"));
    str.replace(QChar(951), QLatin1String("$\\eta$"));
    str.replace(QChar(952), QLatin1String("$\\theta$"));
    str.replace(QChar(953), QLatin1String("$\\iota$"));
    str.replace(QChar(954), QLatin1String("$\\kappa$"));
    str.replace(QChar(955), QLatin1String("$\\lambda$"));
    str.replace(QChar(956), QLatin1String("$\\mu$"));
    str.replace(QChar(957), QLatin1String("$\\nu$"));
    str.replace(QChar(958), QLatin1String("$\\xi$"));
    str.replace(QChar(959), QLatin1String("$\\omicron$"));
    str.replace(QChar(960), QLatin1String("$\\pi$"));
    str.replace(QChar(961), QLatin1String("$\\rho$"));
    str.replace(QChar(962), QLatin1String("$\\varsigma$"));
    str.replace(QChar(963), QLatin1String("$\\sigma$"));
    str.replace(QChar(964), QLatin1String("$\\tau$"));
    str.replace(QChar(965), QLatin1String("$\\upsilon$"));
    str.replace(QChar(966), QLatin1String("$\\phi$"));
    str.replace(QChar(967), QLatin1String("$\\chi$"));
    str.replace(QChar(968), QLatin1String("$\\psi$"));
    str.replace(QChar(969), QLatin1String("$\\omega$"));
    str.replace(QChar(977), QLatin1String("$\\vartheta$"));
    str.replace(QChar(981), QLatin1String("$\\varphi$"));
    str.replace(QChar(982), QLatin1String("$\\varpi$"));
    str.replace(QChar(989), QLatin1String("$\\digamma$"));
    str.replace(QChar(1008), QLatin1String("$\\varkappa$"));
    str.replace(QChar(1009), QLatin1String("$\\varrho$"));
    str.replace(QChar(1013), QLatin1String("$\\epsilon$"));
    str.replace(QChar(8211), '-');
    str.replace(QChar(8462), QLatin1String("$\\hbar$"));
    str.replace(QChar(8463), QLatin1String("$\\hslash$"));
    str.replace(QChar(8467), QLatin1String("$\\ell$"));
    str.replace(QChar(8476), QLatin1String("$\\Re$"));
    str.replace(QChar(8706), QLatin1String("$\\partial$"));
    str.replace(QChar(8722), '-');
    str.replace(QChar(8734), QLatin1String("$\\infty$"));
    str.replace(QChar(8764), QLatin1String("$\\sim$"));
    str.replace(QChar(8943), QLatin1String("$\\cdots$"));

    return str;
}

QHash<QString, QChar> latex_to_unicode()
{
    QHash<QString, QChar> lu;

    lu.insert(QLatin1String("{\\&}"), QChar(38));
    lu.insert(QLatin1String("$\\cdot$"), QChar(183));
    lu.insert(QLatin1String("{\\`A}"), QChar(192));
    lu.insert(QLatin1String("{\\'A}"), QChar(193));
    lu.insert(QLatin1String("{\\^A}"), QChar(194));
    lu.insert(QLatin1String("{\\~A}"), QChar(195));
    lu.insert(QLatin1String("{\\\"A}"), QChar(196));
    lu.insert(QLatin1String("{\\AA}"), QChar(197));
    lu.insert(QLatin1String("{\\AE}"), QChar(198));
    lu.insert(QLatin1String("{\\c C}"), QChar(199));
    lu.insert(QLatin1String("{\\`E}"), QChar(200));
    lu.insert(QLatin1String("{\\'E}"), QChar(201));
    lu.insert(QLatin1String("{\\^E}"), QChar(202));
    lu.insert(QLatin1String("{\\\"E}"), QChar(203));
    lu.insert(QLatin1String("{\\`I}"), QChar(204));
    lu.insert(QLatin1String("{\\'I}"), QChar(205));
    lu.insert(QLatin1String("{\\^I}"), QChar(206));
    lu.insert(QLatin1String("{\\\"I}"), QChar(207));
    lu.insert(QLatin1String("{\\~N}"), QChar(209));
    lu.insert(QLatin1String("{\\`O}"), QChar(210));
    lu.insert(QLatin1String("{\\'O}"), QChar(211));
    lu.insert(QLatin1String("{\\^O}"), QChar(212));
    lu.insert(QLatin1String("{\\~O}"), QChar(213));
    lu.insert(QLatin1String("{\\\"O}"), QChar(214));
    lu.insert(QLatin1String("{\\O}"), QChar(216));
    lu.insert(QLatin1String("{\\`U}"), QChar(217));
    lu.insert(QLatin1String("{\\'U}"), QChar(218));
    lu.insert(QLatin1String("{\\^U}"), QChar(219));
    lu.insert(QLatin1String("{\\\"U}"), QChar(220));
    lu.insert(QLatin1String("{\\'Y}"), QChar(221));
    lu.insert(QLatin1String("{\\ss}"), QChar(223));
    lu.insert(QLatin1String("{\\`a}"), QChar(224));
    lu.insert(QLatin1String("{\\'a}"), QChar(225));
    lu.insert(QLatin1String("{\\^a}"), QChar(226));
    lu.insert(QLatin1String("{\\~a}"), QChar(227));
    lu.insert(QLatin1String("{\\\"a}"), QChar(228));
    lu.insert(QLatin1String("{\\aa}"), QChar(229));
    lu.insert(QLatin1String("{\\ae}"), QChar(230));
    lu.insert(QLatin1String("{\\c c}"), QChar(231));
    lu.insert(QLatin1String("{\\`e}"), QChar(232));
    lu.insert(QLatin1String("{\\'e}"), QChar(233));
    lu.insert(QLatin1String("{\\^e}"), QChar(234));
    lu.insert(QLatin1String("{\\\"e}"), QChar(235));
    lu.insert(QLatin1String("{\\`\\i}"), QChar(236));
    lu.insert(QLatin1String("{\\`i}"), QChar(236));
    lu.insert(QLatin1String("{\\'\\i}"), QChar(237));
    lu.insert(QLatin1String("{\\'i}"), QChar(237));
    lu.insert(QLatin1String("{\\^\\i}"), QChar(238));
    lu.insert(QLatin1String("{\\^i}"), QChar(238));
    lu.insert(QLatin1String("{\\\"\\i}"), QChar(239));
    lu.insert(QLatin1String("{\\\"i}"), QChar(239));
    lu.insert(QLatin1String("{\\~n}"), QChar(241));
    lu.insert(QLatin1String("{\\`o}"), QChar(242));
    lu.insert(QLatin1String("{\\'o}"), QChar(243));
    lu.insert(QLatin1String("{\\^o}"), QChar(244));
    lu.insert(QLatin1String("{\\~o}"), QChar(245));
    lu.insert(QLatin1String("{\\\"o}"), QChar(246));
    lu.insert(QLatin1String("{\\o}"), QChar(248));
    lu.insert(QLatin1String("{\\`u}"), QChar(249));
    lu.insert(QLatin1String("{\\'u}"), QChar(250));
    lu.insert(QLatin1String("{\\^u}"), QChar(251));
    lu.insert(QLatin1String("{\\\"u}"), QChar(252));
    lu.insert(QLatin1String("{\\'y}"), QChar(253));
    lu.insert(QLatin1String("{\\\"y}"), QChar(255));
    lu.insert(QLatin1String("{\\=A}"), QChar(256));
    lu.insert(QLatin1String("{\\=a}"), QChar(257));
    lu.insert(QLatin1String("{\\u A}"), QChar(258));
    lu.insert(QLatin1String("{\\u a}"), QChar(259));
    lu.insert(QLatin1String("{\\c A}"), QChar(260));
    lu.insert(QLatin1String("{\\c a}"), QChar(261));
    lu.insert(QLatin1String("{\\'C}"), QChar(262));
    lu.insert(QLatin1String("{\\'c}"), QChar(263));
    lu.insert(QLatin1String("{\\^C}"), QChar(264));
    lu.insert(QLatin1String("{\\^c}"), QChar(265));
    lu.insert(QLatin1String("{\\.C}"), QChar(266));
    lu.insert(QLatin1String("{\\.c}"), QChar(267));
    lu.insert(QLatin1String("{\\v C}"), QChar(268));
    lu.insert(QLatin1String("{\\v c}"), QChar(269));
    lu.insert(QLatin1String("{\\v D}"), QChar(270));
    lu.insert(QLatin1String("{\\v d}"), QChar(271));
    lu.insert(QLatin1String("{\\DJ}"), QChar(272));
    lu.insert(QLatin1String("{\\dj}"), QChar(273));
    lu.insert(QLatin1String("{\\=E}"), QChar(274));
    lu.insert(QLatin1String("{\\=e}"), QChar(275));
    lu.insert(QLatin1String("{\\u E}"), QChar(276));
    lu.insert(QLatin1String("{\\u e}"), QChar(277));
    lu.insert(QLatin1String("{\\.E}"), QChar(278));
    lu.insert(QLatin1String("{\\.e}"), QChar(279));
    lu.insert(QLatin1String("{\\c E}"), QChar(280));
    lu.insert(QLatin1String("{\\c e}"), QChar(281));
    lu.insert(QLatin1String("{\\v E}"), QChar(282));
    lu.insert(QLatin1String("{\\v e}"), QChar(283));
    lu.insert(QLatin1String("{\\^G}"), QChar(284));
    lu.insert(QLatin1String("{\\^g}"), QChar(285));
    lu.insert(QLatin1String("{\\u G}"), QChar(286));
    lu.insert(QLatin1String("{\\u g}"), QChar(287));
    lu.insert(QLatin1String("{\\.G}"), QChar(288));
    lu.insert(QLatin1String("{\\.g}"), QChar(289));
    lu.insert(QLatin1String("{\\c G}"), QChar(290));
    lu.insert(QLatin1String("{\\c g}"), QChar(291));
    lu.insert(QLatin1String("{\\^H}"), QChar(292));
    lu.insert(QLatin1String("{\\^h}"), QChar(293));
    lu.insert(QLatin1String("{\\H}"), QChar(294));
    lu.insert(QLatin1String("{\\h}"), QChar(295));
    lu.insert(QLatin1String("{\\~I}"), QChar(296));
    lu.insert(QLatin1String("{\\~i}"), QChar(297));
    lu.insert(QLatin1String("{\\=I}"), QChar(298));
    lu.insert(QLatin1String("{\\=i}"), QChar(299));
    lu.insert(QLatin1String("{\\u I}"), QChar(300));
    lu.insert(QLatin1String("{\\u i}"), QChar(301));
    lu.insert(QLatin1String("{\\c I}"), QChar(302));
    lu.insert(QLatin1String("{\\c i}"), QChar(303));
    lu.insert(QLatin1String("{\\.I}"), QChar(304));
    lu.insert(QLatin1String("{\\i}"), QChar(305));
    lu.insert(QLatin1String("{\\L}"), QChar(321));
    lu.insert(QLatin1String("{\\l}"), QChar(322));
    lu.insert(QLatin1String("{\\'N}"), QChar(323));
    lu.insert(QLatin1String("{\\'n}"), QChar(324));
    lu.insert(QLatin1String("{\\c N}"), QChar(325));
    lu.insert(QLatin1String("{\\c n}"), QChar(326));
    lu.insert(QLatin1String("{\\v N}"), QChar(327));
    lu.insert(QLatin1String("{\\v n}"), QChar(328));
    lu.insert(QLatin1String("{\\=O}"), QChar(332));
    lu.insert(QLatin1String("{\\=o}"), QChar(333));
    lu.insert(QLatin1String("{\\u O}"), QChar(334));
    lu.insert(QLatin1String("{\\u o}"), QChar(335));
    lu.insert(QLatin1String("{\\H O}"), QChar(336));
    lu.insert(QLatin1String("{\\H o}"), QChar(337));
    lu.insert(QLatin1String("{\\OE}"), QChar(338));
    lu.insert(QLatin1String("{\\oe}"), QChar(339));
    lu.insert(QLatin1String("{\\'R}"), QChar(340));
    lu.insert(QLatin1String("{\\'r}"), QChar(341));
    lu.insert(QLatin1String("{\\c R}"), QChar(342));
    lu.insert(QLatin1String("{\\c r}"), QChar(343));
    lu.insert(QLatin1String("{\\v R}"), QChar(344));
    lu.insert(QLatin1String("{\\v r}"), QChar(345));
    lu.insert(QLatin1String("{\\'S}"), QChar(346));
    lu.insert(QLatin1String("{\\'s}"), QChar(347));
    lu.insert(QLatin1String("{\\^S}"), QChar(348));
    lu.insert(QLatin1String("{\\^s}"), QChar(349));
    lu.insert(QLatin1String("{\\c S}"), QChar(350));
    lu.insert(QLatin1String("{\\c s}"), QChar(351));
    lu.insert(QLatin1String("{\\v S}"), QChar(352));
    lu.insert(QLatin1String("{\\v s}"), QChar(353));
    lu.insert(QLatin1String("{\\c T}"), QChar(354));
    lu.insert(QLatin1String("{\\c t}"), QChar(355));
    lu.insert(QLatin1String("{\\v T}"), QChar(356));
    lu.insert(QLatin1String("{\\v t}"), QChar(357));
    lu.insert(QLatin1String("{\\^Y}"), QChar(374));
    lu.insert(QLatin1String("{\\^y}"), QChar(375));
    lu.insert(QLatin1String("{\\\"Y}"), QChar(376));
    lu.insert(QLatin1String("{\\'Z}"), QChar(377));
    lu.insert(QLatin1String("{\\'z}"), QChar(378));
    lu.insert(QLatin1String("{\\.Z}"), QChar(379));
    lu.insert(QLatin1String("{\\.z}"), QChar(380));
    lu.insert(QLatin1String("{\\v Z}"), QChar(381));
    lu.insert(QLatin1String("{\\v z}"), QChar(382));
    lu.insert(QLatin1String("$\\Alpha$"), QChar(913));
    lu.insert(QLatin1String("$\\Beta$"), QChar(914));
    lu.insert(QLatin1String("$\\Gamma$"), QChar(915));
    lu.insert(QLatin1String("$\\Delta$"), QChar(916));
    lu.insert(QLatin1String("$\\Epsilon$"), QChar(917));
    lu.insert(QLatin1String("$\\Zeta$"), QChar(918));
    lu.insert(QLatin1String("$\\Eta$"), QChar(919));
    lu.insert(QLatin1String("$\\Theta$"), QChar(920));
    lu.insert(QLatin1String("$\\Iota$"), QChar(921));
    lu.insert(QLatin1String("$\\Kappa$"), QChar(922));
    lu.insert(QLatin1String("$\\Lambda$"), QChar(923));
    lu.insert(QLatin1String("$\\Mu$"), QChar(924));
    lu.insert(QLatin1String("$\\Nu$"), QChar(925));
    lu.insert(QLatin1String("$\\Xi$"), QChar(926));
    lu.insert(QLatin1String("$\\Omicron$"), QChar(927));
    lu.insert(QLatin1String("$\\Pi$"), QChar(928));
    lu.insert(QLatin1String("$\\Rho$"), QChar(929));
    lu.insert(QLatin1String("$\\Sigma$"), QChar(931));
    lu.insert(QLatin1String("$\\Tau$"), QChar(932));
    lu.insert(QLatin1String("$\\Upsilon$"), QChar(933));
    lu.insert(QLatin1String("$\\Phi$"), QChar(934));
    lu.insert(QLatin1String("$\\Chi$"), QChar(935));
    lu.insert(QLatin1String("$\\Psi$"), QChar(936));
    lu.insert(QLatin1String("$\\Omega$"), QChar(937));
    lu.insert(QLatin1String("$\\alpha$"), QChar(945));
    lu.insert(QLatin1String("$\\beta$"), QChar(946));
    lu.insert(QLatin1String("$\\gamma$"), QChar(947));
    lu.insert(QLatin1String("$\\delta$"), QChar(948));
    lu.insert(QLatin1String("$\\varepsilon$"), QChar(949));
    lu.insert(QLatin1String("$\\zeta$"), QChar(950));
    lu.insert(QLatin1String("$\\eta$"), QChar(951));
    lu.insert(QLatin1String("$\\theta$"), QChar(952));
    lu.insert(QLatin1String("$\\iota$"), QChar(953));
    lu.insert(QLatin1String("$\\kappa$"), QChar(954));
    lu.insert(QLatin1String("$\\lambda$"), QChar(955));
    lu.insert(QLatin1String("$\\mu$"), QChar(956));
    lu.insert(QLatin1String("$\\nu$"), QChar(957));
    lu.insert(QLatin1String("$\\xi$"), QChar(958));
    lu.insert(QLatin1String("$\\omicron$"), QChar(959));
    lu.insert(QLatin1String("$\\pi$"), QChar(960));
    lu.insert(QLatin1String("$\\rho$"), QChar(961));
    lu.insert(QLatin1String("$\\sigmaf$"), QChar(962));
    lu.insert(QLatin1String("$\\varsigma$"), QChar(962));
    lu.insert(QLatin1String("$\\sigma$"), QChar(963));
    lu.insert(QLatin1String("$\\tau$"), QChar(964));
    lu.insert(QLatin1String("$\\upsilon$"), QChar(965));
    lu.insert(QLatin1String("$\\phi$"), QChar(966));
    lu.insert(QLatin1String("$\\chi$"), QChar(967));
    lu.insert(QLatin1String("$\\psi$"), QChar(968));
    lu.insert(QLatin1String("$\\omega$"), QChar(969));
    lu.insert(QLatin1String("$\\vartheta$"), QChar(977));
    lu.insert(QLatin1String("$\\varphi$"), QChar(981));
    lu.insert(QLatin1String("$\\varpi$"), QChar(982));
    lu.insert(QLatin1String("$\\digamma$"), QChar(989));
    lu.insert(QLatin1String("$\\varkappa$"), QChar(1008));
    lu.insert(QLatin1String("$\\varrho$"), QChar(1009));
    lu.insert(QLatin1String("$\\epsilon$"), QChar(1013));
    lu.insert(QLatin1String("$\\hbar$"), QChar(8462));
    lu.insert(QLatin1String("$\\hslash$"), QChar(8463));
    lu.insert(QLatin1String("$\\ell$"), QChar(8467));
    lu.insert(QLatin1String("$\\Re$"), QChar(8476));
    lu.insert(QLatin1String("$\\partial$"), QChar(8706));
    lu.insert(QLatin1String("$\\infty$"), QChar(8734));
    lu.insert(QLatin1String("$\\sim$"), QChar(8764));
    lu.insert(QLatin1String("$\\cdots$"), QChar(8943));

    return lu;
}

const QHash<QString, QChar> latex_to_unicode_hash(latex_to_unicode());

const txtmatcher hasLatex("\\", Qt::CaseSensitive, 0);

QString& bibToC2b(QString& str)
{
    const int length(str.length());
    if (length < 2)
        return str;
    int cursor(hasLatex.indexIn(str));
    if (cursor < 0)
        return str;

    QChar* const s(str.data());
    QString latex;
    bool modified(false);
    const QChar amp('&');
    const QChar close('}');
    const QChar del(0);
    const QChar dollar('$');
    const QChar open('{');
    const int mblen(7), mdlen(14);

    if (cursor == 0)
    {
        if (s[cursor + 1] == amp)
        {
            s[cursor] = del;
            modified = true;
        }
        ++cursor;
    }
    while (true)
    {
        cursor = hasLatex.indexIn(s, length, cursor);
        if (cursor < 1)
            break;

        if (s[cursor - 1] == open)
        {
            const int ls(cursor - 1);
            const int m(std::min(cursor + mblen, length));
            for (; cursor < m; ++cursor)
                if (s[cursor] == close)
                {
                    latex.setRawData(s + ls, cursor - ls + 1);
                    if (latex_to_unicode_hash.contains(latex))
                    {
                        s[ls] = latex_to_unicode_hash.value(latex);
                        for (int l = ls + 1; l <= cursor; ++l)
                            s[l] = del;
                        modified = true;
                    }
                    break;
                }
            cursor = ls + 2;
            continue;
        }
        if (s[cursor - 1] == dollar)
        {
            const int ls(cursor - 1);
            const int m(std::min(cursor + mdlen, length));
            for (; cursor < m; ++cursor)
                if (s[cursor] == dollar)
                {
                    latex.setRawData(s + ls, cursor - ls + 1);
                    if (latex_to_unicode_hash.contains(latex))
                    {
                        s[ls] = latex_to_unicode_hash.value(latex);
                        for (int l = ls + 1; l <= cursor; ++l)
                            s[l] = del;
                        modified = true;
                    }
                    break;
                }
            cursor = ls + 2;
            continue;
        }
        if (s[cursor + 1] == amp)
        {
            s[cursor] = del;
            modified = true;
            cursor += 2;
            continue;
        }
        cursor += 1;
        continue;
    }
    if (modified)
    {
        int c(0);
        for (int l = 0; l < length; ++l)
            if (s[l] != del)
                s[c++] = s[l];
        str.truncate(c);
    }
    return str;
}

const QRegExp isBibToC2b("[\\{\\[\\$\\(\\\\<>]");
const QRegExp pnasGreekLetters("[\\{\\[\\(](alpha|beta|gamma|delta|varepsilon|"
                               "zeta|eta|theta|iota|kappa|lambda|mu|nu|xi|"
                               "omicron|pi|rho|sigmaf|varsigma|sigma|tau|"
                               "upsilon|phi|chi|psi|omega|vartheta|varphi|"
                               "varpi|digamma|varkappa|varrho|epsilon)[\\}\\]\\)]",
                               Qt::CaseInsensitive);

QString& fullBibToC2b(QString& str)
{
    // Escape TeX and other special characters to Unicode
    if (!str.contains(isBibToC2b))
        return str;
    // PNAS Style
    str.replace(pnasGreekLetters, "$\\\\1$");
    str.replace(QLatin1String("{micro}"), QLatin1String("$\\mu$"));
    str.replace(QLatin1String("{middle dot}"), QLatin1String("$\\cdot$"));
    // Sub and superscripts
    str.replace(QRegExp("<sub>([^<]*)</sub>"), "$_{\\1}$");
    str.replace(QRegExp("<sup>([^<]*)</sup>"), "$^{\\1}$");
    str.replace(QRegExp("\\[sub ([^\\]]*)\\]"), "$_{\\1}$");
    str.replace(QRegExp("\\[sup ([^\\]]*)\\]"), "$^{\\1}$");
    str.replace(QRegExp("\\}\\$\\$([_\\^])\\{"), "}\\1{"); // merge if both
    // Normalize TeX
    str.replace(QRegExp("\\{\\\\(\\W)\\{([\\\\]{0,1}\\w)\\}\\}"), "{\\\\1\\2}");  // {\'{A}} to {\'A}
    str.replace(QRegExp("\\{\\\\(\\w)\\{([\\\\]{0,1}\\w)\\}\\}"), "{\\\\1 \\2}"); // {\c{C}} to {\c C}
    str.replace(QRegExp("\\\\(\\W)\\{([\\\\]{0,1}\\w)\\}"), "{\\\\1\\2}");        // \'{A} to {\'A}
    str.replace(QRegExp("\\\\(\\w)\\{([\\\\]{0,1}\\w)\\}"), "{\\\\1 \\2}");       // \c{C} to {\c C}
    str.replace(QRegExp("\\{\\\\(.{1,2})\\{(\\w{0,2})\\}\\}"), "{\\\\1\\2}");     // {\\AA{}} to {\\AA}
    str.replace(QRegExp("\\\\\\{([A-Z]\\w{1,7})\\\\\\}"), "\\1");                 // \{NaCl\} to NaCl
    // TeX to Unicode
    bibToC2b(str);
    return str;
}

QString fromUtf8(const QByteArray& ba)
{
    // Based on Qt's QString::fromUtf8 function. Input ba must be an UTF-8
    // encoded array produced by QString::toUtf8. Encoding correctness is
    // assumed and checking omitted for efficiency.

    const char* b = ba.constData();
    const char* const bn = b + ba.length();
    QString output;
    output.resize(ba.length());
    ushort* o = (ushort*)output.unicode();
    uint c;
    while (b < bn)
    {
        c = uint(*b);
        if (c & 0x80)
        {
            if ((c & 0xe0) == 0xc0)
            {
                c &= 0x1f;
                c = (uint)((c << 6) | (*++b & 0x3f));
            }
            else if ((c & 0xf0) == 0xe0)
            {
                c &= 0x0f;
                c = (uint)((c << 6) | (b[1] & 0x3f));
                c = (uint)((c << 6) | (b[2] & 0x3f));
                b += 2;
            }
            else if ((c & 0xf8) == 0xf0)
            {
                c &= 0x07;
                c = (uint)((c << 6) | (b[1] & 0x3f));
                c = (uint)((c << 6) | (b[2] & 0x3f));
                c = (uint)((c << 6) | (b[3] & 0x3f));
                *o++ = QChar::highSurrogate(c);
                c = QChar::lowSurrogate(c);
                b += 3;
            }
            else
                c = QChar::ReplacementCharacter;
        }
        *o++ = ushort(c);
        ++b;
    }
    output.truncate(int(o - (ushort*)output.unicode()));
    // QString check = QString::fromUtf8(ba);
    // qDebug() << (check == output);
    return output;
}

#if defined(C2B_USE_LZSSE)
namespace lzsse
{
static const int HEADER_LENGTH = 10;

QByteArray compress(const QByteArray& decompressed)
{
    const int sdecompressed(decompressed.size());
    if (sdecompressed == 0)
        return QByteArray();

    LZSSE4_OptimalParseState* state(LZSSE4_MakeOptimalParseState(static_cast<size_t>(sdecompressed)));
    if (!state)
    {
        warn("compress: lzsse: internal error - compression failed");
        return QByteArray();
    }
    QByteArray compressed;
    const int sdst(sdecompressed);
    const int scompressed(HEADER_LENGTH + sdst);
    compressed.resize(scompressed);
    char* dst(compressed.data() + HEADER_LENGTH);
    const unsigned int clevel(17);
    const int sactual(LZSSE4_CompressOptimalParse(state, decompressed.constData(), sdecompressed, dst, sdst, clevel));
    LZSSE4_FreeOptimalParseState(state);
    if (sactual == 0)
    {
        warn("compress: lzsse: internal error - compression failed");
        return QByteArray();
    }
    compressed.resize(sactual + HEADER_LENGTH);

    QByteArray header(QByteArray::number(qulonglong(sdecompressed)));
    for (int i = 0; i < std::min(header.length(), HEADER_LENGTH); ++i)
        compressed[i] = header[i];
    for (int i = std::min(header.length(), HEADER_LENGTH); i < HEADER_LENGTH; ++i)
        compressed[i] = ' ';
    return compressed;
}

QByteArray decompress(const QByteArray& compressed)
{
    const int scompressed(compressed.size());
    if (scompressed <= HEADER_LENGTH)
        return QByteArray();

    const int sdecompressed(compressed.left(HEADER_LENGTH).trimmed().toULong());
    QByteArray decompressed;
    decompressed.resize(sdecompressed);
    const int ssrc(scompressed - HEADER_LENGTH);
    const char* src(compressed.constData() + HEADER_LENGTH);

    const int sactual(LZSSE4_Decompress(src, ssrc, decompressed.data(), sdecompressed));
    if (sactual != sdecompressed)
    {
        warn("decompress: lzsse: internal error - decompression failed");
        return QByteArray();
    }
    return decompressed;
}

} // namespace lzsse

QByteArray compressString(const QString& decompressed)
{
    return lzsse::compress(
               QByteArray(reinterpret_cast<const char*>(decompressed.unicode()), decompressed.size() * sizeof(ushort)));
}

QString decompressString(const QByteArray& compressed)
{
    const int scompressed(compressed.size());
    if (scompressed <= lzsse::HEADER_LENGTH)
        return QString();

    const int sdecompressedchars(compressed.left(lzsse::HEADER_LENGTH).trimmed().toULong());
    const int sdecompressed(sdecompressedchars / sizeof(ushort));
    QString decompressed;
    decompressed.resize(sdecompressed);
    const int ssrc(scompressed - lzsse::HEADER_LENGTH);
    const char* src(compressed.constData() + lzsse::HEADER_LENGTH);

    const int sactual(LZSSE4_Decompress(src, ssrc, reinterpret_cast<char*>(decompressed.data()), sdecompressedchars));
    if (sactual != sdecompressedchars)
    {
        warn("decompress: lzsse: internal error - decompression failed");
        return QString();
    }
    return decompressed;
}
#elif defined(C2B_USE_LZ4)
namespace lz4
{
static const int HEADER_LENGTH = 10;

QByteArray compress(const QByteArray& decompressed)
{
    const int sdecompressed(decompressed.size());
    if (sdecompressed == 0)
        return QByteArray();

    QByteArray compressed;
    const int sdst(LZ4_compressBound(sdecompressed));
    const int scompressed(HEADER_LENGTH + sdst);
    compressed.resize(scompressed);
    char* dst(compressed.data() + HEADER_LENGTH);

    const int sactual(LZ4_compress_HC(decompressed.constData(), dst, sdecompressed, sdst, LZ4HC_CLEVEL_DEFAULT));
    if (sactual <= 0)
    {
        warn("compress: lz4: internal error - compression failed");
        return QByteArray();
    }
    compressed.resize(sactual + HEADER_LENGTH);

    QByteArray header(QByteArray::number(qulonglong(sdecompressed)));
    for (int i = 0; i < std::min(header.length(), HEADER_LENGTH); ++i)
        compressed[i] = header[i];
    for (int i = std::min(header.length(), HEADER_LENGTH); i < HEADER_LENGTH; ++i)
        compressed[i] = ' ';
    return compressed;
}

QByteArray decompress(const QByteArray& compressed)
{
    const int scompressed(compressed.size());
    if (scompressed <= HEADER_LENGTH)
        return QByteArray();

    const int sdecompressed(compressed.left(HEADER_LENGTH).trimmed().toULong());
    QByteArray decompressed;
    decompressed.resize(sdecompressed);
    const int ssrc(scompressed - HEADER_LENGTH);
    const char* src(compressed.constData() + HEADER_LENGTH);

    const int sactual(LZ4_decompress_safe(src, decompressed.data(), ssrc, sdecompressed));
    if (sactual != sdecompressed)
    {
        warn("decompress: lz4: internal error - decompression failed");
        return QByteArray();
    }
    return decompressed;
}

} // namespace lz4

QByteArray compressString(const QString& decompressed)
{
    return lz4::compress(
               QByteArray(reinterpret_cast<const char*>(decompressed.unicode()), decompressed.size() * sizeof(ushort)));
}

QString decompressString(const QByteArray& compressed)
{
    const int scompressed(compressed.size());
    if (scompressed <= lz4::HEADER_LENGTH)
        return QString();

    const int sdecompressedchars(compressed.left(lz4::HEADER_LENGTH).trimmed().toULong());
    const int sdecompressed(sdecompressedchars / sizeof(ushort));
    QString decompressed;
    decompressed.resize(sdecompressed);
    const int ssrc(scompressed - lz4::HEADER_LENGTH);
    const char* src(compressed.constData() + lz4::HEADER_LENGTH);

    const int sactual(LZ4_decompress_safe(src, reinterpret_cast<char*>(decompressed.data()), ssrc, sdecompressedchars));
    if (sactual != sdecompressedchars)
    {
        warn("decompress: lz4: internal error - decompression failed");
        return QString();
    }
    return decompressed;
}
#elif defined(C2B_USE_LZO)
namespace lzo
{
static const int HEADER_LENGTH = 10;

QByteArray compress(const QByteArray& data)
{
    const lzo_uint src_s(data.size());
    if (src_s == 0)
        return QByteArray();
    if (lzo_init() != LZO_E_OK)
    {
        warn("compress: lzo: internal error - initialization failed");
        return QByteArray();
    }
    const lzo_bytep src_p = reinterpret_cast<const lzo_bytep>(data.constData());

    QByteArray compressed;
    const lzo_uint dest_s = HEADER_LENGTH + (src_s + src_s / 16 + 64 + 3);
    compressed.resize((int)dest_s);
    lzo_bytep compressed_p = reinterpret_cast<lzo_bytep>(compressed.data());
    lzo_bytep dest_p = compressed_p + HEADER_LENGTH;
    lzo_uint enc_dest_s = dest_s - HEADER_LENGTH;

    QByteArray wrkmem;
    wrkmem.resize(LZO1X_999_MEM_COMPRESS);
    lzo_bytep wrkmem_p = reinterpret_cast<lzo_bytep>(wrkmem.data());

    if (lzo1x_999_compress(src_p, src_s, dest_p, &enc_dest_s, wrkmem_p) == LZO_E_OK)
    {
        compressed.resize((int)enc_dest_s + HEADER_LENGTH);
        QByteArray header(QByteArray::number((qulonglong)src_s));
        for (int i = 0; i < std::min(header.length(), HEADER_LENGTH); ++i)
            compressed[i] = header[i];
        for (int i = std::min(header.length(), HEADER_LENGTH); i < HEADER_LENGTH; ++i)
            compressed[i] = ' ';
        return compressed;
    }
    else
    {
        warn("compress: lzo: internal error - compression failed");
        return QByteArray();
    }
}

QByteArray decompress(const QByteArray& data)
{
    const lzo_uint data_s(data.size());
    if (data_s <= (unsigned int)HEADER_LENGTH)
        return QByteArray();
    if (lzo_init() != LZO_E_OK)
    {
        warn("decompress: lzo: internal error - initialization failed");
        return QByteArray();
    }
    const lzo_bytep data_p = reinterpret_cast<const lzo_bytep>(data.constData());
    const lzo_bytep src_p = data_p + HEADER_LENGTH;
    const lzo_uint src_s = data_s - HEADER_LENGTH;

    QByteArray decompressed;
    const ulong expected_dest_s = data.left(HEADER_LENGTH).trimmed().toULong();
    lzo_uint dest_s = std::max(expected_dest_s, lzo_uint(1));
    decompressed.resize((int)dest_s);
    lzo_bytep dest_p = reinterpret_cast<lzo_bytep>(decompressed.data());

    if (lzo1x_decompress(src_p, src_s, dest_p, &dest_s, NULL) == LZO_E_OK && (ulong)dest_s == expected_dest_s)
        return decompressed;
    else
    {
        warn("decompress: lzo: internal error - decompression failed");
        return QByteArray();
    }
}

} // namespace lzo

QByteArray compressString(const QString& decompressed)
{
    return lzo::compress(decompressed.toUtf8());
}

QString decompressString(const QByteArray& compressed)
{
    return fromUtf8(lzo::decompress(compressed));
}
#else
QByteArray compressString(const QString& decompressed)
{
    return qCompress(decompressed.toUtf8());
}

QString decompressString(const QByteArray& compressed)
{
    return fromUtf8(qUncompress(compressed));
}
#endif

} // namespace c2bUtils
