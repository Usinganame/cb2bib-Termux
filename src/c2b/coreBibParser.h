/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef COREBIBPARSER_H
#define COREBIBPARSER_H

#include "authorString.h"
#include "bibReference.h"
#include "settings.h"
#include "txtmatcher.h"

#include <QDir>
#include <QObject>


/**
    Class for bibliographic reference parsing

    @author Pere Constans
*/
class coreBibParser : public QObject
{

    Q_OBJECT

public:
    explicit coreBibParser(QObject* parento = 0);
    inline virtual ~coreBibParser() {}

    QString referenceToBibTeX(const bibReference& ref) const;
    QString referenceToFomattedBibTeX(const bibReference& ref) const;
    QString singleReferenceField(const QString& field, const bibReference& ref) const;
    bibReference wholeReference(const QString& str) const;
    bool referenceAtKey(const QString& key, const QString& str, bibReference* ref);
    bool referencesIn(const QString& str, bibReference* ref);
    void initReferenceParsing(const QString& dir, const QStringList& fields, bibReference* ref);

    inline const QStringList& bibliographicFields() const
    {
        return _bibliographic_fields;
    }
    inline const QStringList& sortedBibliographicFields() const
    {
        return _sorted_bibliographic_fields;
    }
    inline const QStringList& bibliographicTypes() const
    {
        return _bibliographic_types;
    }
    inline void setReferenceParsingDir(const QString& dir)
    {
        // Set base dir for cases of relative 'file'
        // Terminate dirname with separator to avoid adding it to each reference
        _bib_file_dir = QDir::toNativeSeparators(QFileInfo(dir).absolutePath() + QDir::separator());
    }
    inline bool hasBibTeX(const QString& str) const
    {
        if (_bib_begin0_re.indexIn(str) > -1)
            return true;
        else
            return _bib_begin1_re.indexIn(str) > -1;
    }
    inline int fieldCount(const bibReference& ref) const
    {
        // Counting non empty fields
        int n(0);
        bibReferenceIterator i;
        for (i = ref.constBegin(); i != ref.constEnd(); ++i)
            if (!i.value().isEmpty())
                ++n;
        return n;
    }
    inline QString& authorFromBibTeX(QString& as)
    {
        // Avoid BibTeX reverse names
        if (as.contains(_comma))
            as = _authorString.toBibTeX(as, _settingsP->value("cb2Bib/UseFullNames").toBool());
        return as;
    }
    inline QString authorFromMedline(const QString& author) const
    {
        return _authorString.fromMedline(author);
    }
    inline const QString& authorPrefixes() const
    {
        return _authorString.prefixes();
    }


protected:
    QRegExp _field_re;
    QString adjacentNumbers(const QString& numbers) const;
    QStringList _bibliographic_fields;
    QStringList _bibliographic_types;
    QStringList _current_bibliographic_fields;
    QStringList _sorted_bibliographic_fields;
    authorString _authorString;
    settings* _settingsP;


private:
    QRegExp _bib_begin0_re;
    QRegExp _bib_begin1_re;
    QRegExp _bib_begin_re;
    QString _bib_file_dir;
    const QChar _at;
    const QChar _close;
    const QChar _colon;
    const QChar _comma;
    const QChar _cr;
    const QChar _hyphen;
    const QChar _lca;
    const QChar _lcz;
    const QChar _nl;
    const QChar _open;
    const QChar _period;
    const QChar _pound;
    const QChar _quote;
    const QChar _space;
    const QChar _tilde;
    const QChar _uca;
    const QChar _ucz;
    txtmatcher _bib_begin_at;
    txtmatcher _bib_field_delimiter;

    void referenceContents(const QString& str, bibReference* ref, int pos) const;
    void setFields();
    void setRegularExpressions();
    void setTypes();

    void _parse_reference_fields(const QString& bibstr, const QStringList& fields, bibReference* ref) const;
    int _in_braces_ends(const QChar* const b, const int p, const int length) const;

    inline int referenceStarts(const QString& str, int pos = 0) const
    {
        while (true)
        {
            const int i(_bib_begin_at.indexIn(str, pos));
            if (i > 0)
            {
                for (int j = i - 1; j >= pos; --j)
                    if (str.at(j) == _nl || str.at(j) == _cr)
                        goto check;
                    else if (!str.at(j).isSpace())
                        goto next;
                if (pos > 0)
                    goto next;
            }
            else if (i < 0)
                return i;
check:
            if (_bib_begin_re.indexIn(str, i, QRegExp::CaretAtOffset) == i)
                return i;
next:
            pos = i + 2;
        }
    }
    inline int referenceStarts(const QString& key, const QString& str) const
    {
        if (!str.contains(key))
            return -1;
        int i(str.indexOf(QRegExp("^\\s*@\\w+\\s*\\{" + key + ',')));
        if (i < 0)
            i = str.indexOf(QRegExp("[\\r\\n]\\s*@\\w+\\s*\\{" + key + ','));
        if (i < 0)
            return i;
        return str.indexOf(QRegExp("@\\w+\\s*\\{" + key + ','), i);
    }
    inline int referenceEnds(const QString& str, const int pos = 0) const
    {
        // If referenceStarts call is successful, we know for sure
        // that there is an opening { right after pos.
        // Do not check again here.
        // Checking for brace closure is the safest way for parsing.
        // It will fail, though, for references incorrectly written.
        // Avoid overextending in these cases by checking the
        // start of the next reference.
        int ref_length(referenceStarts(str, pos + 2) - 1);
        if (ref_length < 0)
            ref_length = str.length();
        const int brace_pos(str.indexOf(_open, pos));
        int open_braces(1);
        for (int i = brace_pos + 1; i < ref_length; ++i)
        {
            if (str.at(i) < _open)
                continue;
            const QChar& si(str.at(i));
            if (si == _open)
                open_braces++;
            else if (si == _close)
                open_braces--;
            if (open_braces == 0)
                return i;
        }
        return ref_length - 1;
    }
    inline void setReferenceEnd(QString* str) const
    {
        // Set safer termination: field="..." } -> field="...",}
        const unsigned int length(str->length());
        if (str->at(length - 2) == _space)
            (*str)[length - 2] = _comma;
        else
            (*str)[length - 1] = _comma;
    }
    inline QString referenceAt(const QString& str, int* pos) const
    {
        // String str contains one or multiple references (file contents)
        const int p(referenceEnds(str, *pos) + 1);
        const QString str_ref(str.mid(*pos, p - (*pos)));
        *pos = p;
        return str_ref;
    }
};

#endif
