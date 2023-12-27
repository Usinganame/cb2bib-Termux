/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bColors.h"
#include "c2bSettings.h"


c2bColors::c2bColors()
{
    colorList.insert("BibTeX delimiters", &bib_delimiter_color);
    colorList.insert("BibTeX reference field", &bib_reference_field_color);
    colorList.insert("BibTeX reference type", &bib_reference_type_color);
    colorList.insert("Comments and line numbers", &comment_color);
    colorList.insert("NetQInf command contents", &netqinf_command_content_color);
    colorList.insert("NetQInf command keys", &netqinf_command_key_color);
    colorList.insert("RegExp and NetQInf cb2Bib tags", &cb2bib_tag_color);
    colorList.insert("cb2Bib digits", &cb2bib_digit_color);
    colorList.insert("cb2Bib highly relevant text", &cb2bib_highly_relevant_color);
    colorList.insert("cb2Bib metadata", &cb2bib_metadata_color);
    colorList.insert("cb2Bib relevant text", &cb2bib_relevant_color);
    colorList.insert("cb2Bib unrelevant text", &cb2bib_unrelevant_color);
}

c2bColors::~c2bColors() {}


void c2bColors::updateColor(const QColor& color, const QString& colorName)
{
    *colorList[colorName] = color;
}

void c2bColors::saveColors(c2bSettings* settings)
{
    settings->setValue("c2bColors/bib_delimiter_color", bib_delimiter_color);
    settings->setValue("c2bColors/bib_reference_field_color", bib_reference_field_color);
    settings->setValue("c2bColors/bib_reference_type_color", bib_reference_type_color);
    settings->setValue("c2bColors/cb2bib_digit_color", cb2bib_digit_color);
    settings->setValue("c2bColors/cb2bib_highly_relevant_color", cb2bib_highly_relevant_color);
    settings->setValue("c2bColors/cb2bib_metadata_color", cb2bib_metadata_color);
    settings->setValue("c2bColors/cb2bib_relevant_color", cb2bib_relevant_color);
    settings->setValue("c2bColors/cb2bib_tag_color", cb2bib_tag_color);
    settings->setValue("c2bColors/cb2bib_unrelevant_color", cb2bib_unrelevant_color);
    settings->setValue("c2bColors/comment_color", comment_color);
    settings->setValue("c2bColors/netqinf_command_content_color", netqinf_command_content_color);
    settings->setValue("c2bColors/netqinf_command_key_color", netqinf_command_key_color);
}

void c2bColors::loadColors(c2bSettings* settings)
{
    bib_delimiter_color = settings->value("c2bColors/bib_delimiter_color", "#555555").value<QColor>();
    bib_reference_field_color = settings->value("c2bColors/bib_reference_field_color", "#00007f").value<QColor>();
    bib_reference_type_color = settings->value("c2bColors/bib_reference_type_color", "#00007f").value<QColor>();
    cb2bib_digit_color = settings->value("c2bColors/cb2bib_digit_color", "#005500").value<QColor>();
    cb2bib_highly_relevant_color = settings->value("c2bColors/cb2bib_highly_relevant_color", "#0000ff").value<QColor>();
    cb2bib_metadata_color = settings->value("c2bColors/cb2bib_metadata_color", "#595942").value<QColor>();
    cb2bib_relevant_color = settings->value("c2bColors/cb2bib_relevant_color", "#005500").value<QColor>();
    cb2bib_tag_color = settings->value("c2bColors/cb2bib_tag_color", "#550000").value<QColor>();
    cb2bib_unrelevant_color = settings->value("c2bColors/cb2bib_unrelevant_color", "#595942").value<QColor>();
    comment_color = settings->value("c2bColors/comment_color", "#595942").value<QColor>();
    netqinf_command_content_color =
        settings->value("c2bColors/netqinf_command_content_color", "#000000").value<QColor>();
    netqinf_command_key_color = settings->value("c2bColors/netqinf_command_key_color", "#00007f").value<QColor>();
}
