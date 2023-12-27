/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef BIBPARSER_H
#define BIBPARSER_H

#include "cb2bib_parameters.h"
#include "coreBibParser.h"
#include "journalDB.h"
#include "monthDB.h"


class bibPreparser;
class heuristicBibParser;
class idMaker;
class preprocess;


/**
    Class for bibliographic reference parsing and manipulation

    @author Pere Constans
*/
class bibParser : public coreBibParser
{

    Q_OBJECT

public:
    explicit bibParser(QObject* parento = 0);
    virtual ~bibParser();

    QString documentFilename(const QString& base_fn, const QString& bibtex_fn);
    QString excerpt(const QString& text, const QStringList& hints) const;
    QString parse(const QString& field, const QString& value, const QString& init_value = QString());
    QString setJournalsToAbbreviated(const QString& text, const bool alternate);
    QString setJournalsToFull(const QString& text, const bool alternate);
    QString setTags(const QString& text) const;
    bibReference& parse(bibReference& reference);
    virtual void setCiteID();
    virtual void setField(const QString& name, const QString& value);
    virtual void setReferenceType(const QString& type);
    void guessFields(const QString& text);
    void parse(const QString& text, QString* out_text, QString* out_tagtext);
    void preparse(const QString& text, QString* out_text);

    inline QString abbreviatedJournal(const QString& name) const
    {
        return _journal_dbP->retrieve(name);
    }
    inline QString fullJournal(const QString& name) const
    {
        return _journal_dbP->retrieveFull(name);
    }
    inline QString alternateAbbreviatedJournal(const QString& name) const
    {
        return _journal_dbP->retrieveAlternate(name);
    }
    inline QString alternateFullJournal(const QString& name) const
    {
        return _journal_dbP->retrieveAlternateFull(name);
    }
    inline const QStringList& abbreviatedJournalList() const
    {
        return _journal_dbP->abbreviatedList();
    }
    inline bool isAutoRecognized() const
    {
        return _auto_recognized;
    }
    inline QString autoRecognizedString() const
    {
        return _auto_recognized_string;
    }
    inline QString toBibTeX(bool sig = true) const
    {
        if (sig)
            return "% cb2Bib " + C2B_VERSION + '\n' + referenceToFomattedBibTeX(_current_reference) + '\n';
        else
            return referenceToFomattedBibTeX(_current_reference);
    }
    inline QString toBibTeX(const bibReference& ref, bool sig = true) const
    {
        if (sig)
            return "% cb2Bib " + C2B_VERSION + '\n' + referenceToFomattedBibTeX(ref) + '\n';
        else
            return referenceToFomattedBibTeX(ref);
    }
    inline const bibReference& currentReference() const
    {
        return _current_reference;
    }
    inline void clearCurrentReference()
    {
        _current_reference.clearReference();
        _auto_recognized = false;
        _auto_recognized_string.clear();
    }
    inline int fieldCount() const
    {
        return coreBibParser::fieldCount(_current_reference);
    }


signals:
    void statusMessage(const QString& ms);


protected:
    bibPreparser* _preparserP;
    bibReference _current_reference;
    idMaker* _cite_idmP;
    idMaker* _file_idmP;
    inline virtual void currentReferenceUpdated() {}
    virtual void checkRegExpFile(const QString& fn);


private:
    QString _auto_recognized_string;
    QString metadataSection(const QString& text, const QString& identifier) const;
    QString removeTags(const QString& text) const;
    bool _auto_recognized;
    heuristicBibParser* _heuristic_parserP;
    journalDB* _journal_dbP;
    monthDB* _month_dbP;
    preprocess* _preprocessP;


    friend class heuristicBibParser;
};

#endif
