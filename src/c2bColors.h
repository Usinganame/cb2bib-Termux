/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCOLORS_H
#define C2BCOLORS_H

#include <QColor>
#include <QHash>


class c2bSettings;

/**
    cb2Bib Color Scheme
*/
class c2bColors
{

public:
    c2bColors();
    ~c2bColors();

    QColor bib_delimiter_color;
    QColor bib_reference_field_color;
    QColor bib_reference_type_color;
    QColor cb2bib_digit_color;
    QColor cb2bib_highly_relevant_color;
    QColor cb2bib_metadata_color;
    QColor cb2bib_relevant_color;
    QColor cb2bib_tag_color;
    QColor cb2bib_unrelevant_color;
    QColor comment_color;
    QColor netqinf_command_content_color;
    QColor netqinf_command_key_color;
    QHash<QString, QColor*> colorList;
    void loadColors(c2bSettings* settings);
    void saveColors(c2bSettings* settings);
    void updateColor(const QColor& color, const QString& colorName);
};

#endif
