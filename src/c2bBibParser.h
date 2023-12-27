/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BBIBPARSER_H
#define C2BBIBPARSER_H

#include "c2bBibPreparserLog.h"
#include "c2bLineEdit.h"

#include <bibParser.h>
#include <journalDB.h>

#include <QPointer>


class QComboBox;

/**
    cb2Bib interface to bibParser

    This class groups Bib Parser functionality related to GUI

    @author Pere Constans
*/
class c2bBibParser : public bibParser
{

    Q_OBJECT

public:
    explicit c2bBibParser(QObject* parento = 0);
    ~c2bBibParser();

    void clearCurrentReference();
    void setWidgetMapping();

    inline void addField(const QString& name, c2bLineEdit* editor)
    {
        _field_editors.insert(name, editor);
    }
    inline void addTypes(QComboBox* types)
    {
        _type_editor = types;
    }
    inline QString field(const QString& name) const
    {
        return _field_editors.value(name)->text();
    }
    inline void setField(const QString& name, const QString& value) override
    {
        _field_editors[name]->setText(parse(name, value));
    }
    inline void setField(const QString& name, const QString& value, const QString& init_value)
    {
        if (name == "addauthors")
            _field_editors["author"]->setText(parse(name, value, init_value));
        else if (name == "addeditors")
            _field_editors["editor"]->setText(parse(name, value, init_value));
    }


signals:
    void bibModified(bool modified);
    void setDocumentFilename();


private:
    QComboBox* _type_editor;
    QHash<QString, c2bLineEdit*> _field_editors;
    QPointer<c2bBibPreparserLog> _preparser_logP;
    QWidget* _c2b_mainP;
    bool _bp_updates_gui;
    void checkRegExpFile(const QString& fn) override;
    void currentReferenceUpdated() override;
    void setCiteID() override;
    void setReferenceType(const QString& type) override;


private slots:
    void referenceEdited(const QString& value);
    void setField();
    void showLog(const QString& log);
};

#endif
