/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bBibParser.h"

#include "c2b.h"
#include "c2bSettings.h"

#include <bibPreparser.h>

#include <QComboBox>
#include <QMessageBox>


c2bBibParser::c2bBibParser(QObject* parento) : bibParser(parento)
{
    _c2b_mainP = c2b::mainWidget();
    _bp_updates_gui = false;

    // Warn users if journal database file is not setup
    const QString journal_f(_settingsP->fileName("cb2Bib/JournalFile"));
    if (journal_f.isEmpty())
        QMessageBox::information(_c2b_mainP, tr("Information - cb2Bib"),
                                 tr("No Abbreviation Journal file has been specified.\n\n"
                                    "Note: Abbreviation files are specified through the cb2Bib Configure dialog."),
                                 QMessageBox::Ok);
    else
    {
        QFile f(journal_f);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) // jdbfile.exists wouldn't produce an errorString
            QMessageBox::warning(_c2b_mainP, tr("Warning - cb2Bib"),
                                 tr("Unable to open the Journal Abbreviation file %1 for reading.\nError: '%2'.\n\n"
                                    "Note: Abbreviation files are specified through the cb2Bib Configure dialog.")
                                 .arg(journal_f, f.errorString()),
                                 QMessageBox::Ok);
        else
            f.close();
    }

    // Set status messages
    connect(this, SIGNAL(statusMessage(QString)), c2b::instance(), SIGNAL(statusMessage(QString)));

    // Set preparser log
    connect(_preparserP, SIGNAL(preparserLogAvailable(QString)), this, SLOT(showLog(QString)));
}

c2bBibParser::~c2bBibParser() {}


void c2bBibParser::currentReferenceUpdated()
{
    // Current reference has been updated by the base class.
    // Update it in the GUI
    _bp_updates_gui = true;
    bibReferenceIterator i;
    for (i = _current_reference.constBegin(); i != _current_reference.constEnd(); ++i)
        _field_editors[i.key()]->setText(i.value());
    // Set default type to article
    if (_current_reference.typeName.isEmpty())
        _current_reference.typeName = "article";
    setReferenceType(_current_reference.typeName);
    setCiteID();
    _bp_updates_gui = false;
    emit bibModified(fieldCount() > 0);
}

void c2bBibParser::clearCurrentReference()
{
    _bp_updates_gui = true;
    // Clear by setting empty QString as a workaround for bug
    // http://bugreports.qt.nokia.com/browse/QTBUG-7866
    // Affects versions 4.6.x, expected to be fixed in 4.6.3
    for (int i = 0; i < _bibliographic_fields.count(); ++i)
        _field_editors[_bibliographic_fields.at(i)]->setText(QString());
    // _field_editors[_bibliographic_fields.at(i)]->clear();
    _field_editors["id"]->setText(QString());
    // _field_editors["id"]->clear();
    bibParser::clearCurrentReference();
    _current_reference.typeName = "article";
    _type_editor->setCurrentIndex(1);
    _bp_updates_gui = false;
    emit bibModified(false);
}

void c2bBibParser::referenceEdited(const QString& value)
{
    if (_bp_updates_gui)
        return;
    if (sender())
    {
        const QString name(sender()->objectName());
        if (name == "id")
        {
            _current_reference.citeidName = value;
            emit setDocumentFilename();
        }
        else if (name == "typecombo")
            _current_reference.typeName = value;
        else if (name == "file")
            _current_reference[name] = value;
        else
        {
            // Attention: No name checking is done.
            // Only reference editors must be connected here.
            _current_reference[name] = value;
            setCiteID();
            emit setDocumentFilename();
        }
        emit bibModified(fieldCount() > 0);
    }
}

void c2bBibParser::setCiteID()
{
    bibParser::setCiteID();
    _field_editors["id"]->setText(_current_reference.citeidName);
}

void c2bBibParser::setField()
{
    if (sender())
    {
        const QString name(sender()->objectName());
        if (_field_editors.contains(name))
            _field_editors[name]->setText(parse(name, _field_editors.value(name)->text()));
    }
}

void c2bBibParser::setReferenceType(const QString& type)
{
    int i(0);
    while (i < _type_editor->count())
    {
        if (_type_editor->itemText(i) == type)
        {
            _type_editor->setCurrentIndex(i);
            return;
        }
        ++i;
    }
    _type_editor->setCurrentIndex(0);
    _type_editor->setItemText(0, type);
}

void c2bBibParser::setWidgetMapping()
{
    // Setting Reference Types
    _type_editor->insertItems(0, _bibliographic_types);
    _type_editor->setCurrentIndex(1);
    _current_reference.typeName = "article";

    // Tracking Field Editor Line changes
    // Track using textChanged instead of editTextChanged. The latter does not track line clears
    for (int i = 0; i < _bibliographic_fields.count(); ++i)
    {
        const QString& name = _bibliographic_fields.at(i);
        connect(_field_editors.value(name), SIGNAL(returnPressed()), this, SLOT(setField()));
        connect(_field_editors.value(name), SIGNAL(textChanged(QString)), this, SLOT(referenceEdited(QString)));
    }
    connect(_field_editors.value("id"), SIGNAL(textChanged(QString)), this, SLOT(referenceEdited(QString)));
    connect(_type_editor, SIGNAL(editTextChanged(QString)), this, SLOT(referenceEdited(QString)));
}

void c2bBibParser::showLog(const QString& log)
{
    if (!_preparser_logP)
        _preparser_logP = new c2bBibPreparserLog(_c2b_mainP);
    _preparser_logP->append(log);
    _preparser_logP->show(); // Don't use exec(), it could be a recursive call if clipboard changed
}

void c2bBibParser::checkRegExpFile(const QString& fn)
{
    if (fn.isEmpty())
    {
        QMessageBox::information(_c2b_mainP, tr("Information - cb2Bib"),
                                 tr("No RegExp filename has been specified.\n\n"
                                    "Note: RegExp files are specified through the cb2Bib Configure dialog."),
                                 QMessageBox::Ok);
        return;
    }
    QFile f(fn);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::warning(_c2b_mainP, tr("Warning - cb2Bib"),
                             tr("Unable to open the RegExp file %1 for reading.\nError: '%2'.\n\n"
                                "Note: RegExp files are specified through the cb2Bib Configure dialog. "
                                "After manual matching, patterns can be edited and stored in a "
                                "RegExp file for future autodetection.")
                             .arg(fn, f.errorString()),
                             QMessageBox::Ok);
    else
        f.close();
}
