/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BTESTS_H
#define C2BTESTS_H

#include <QString>

class QTextStream;
class bibParser;
class bibReference;


/**
    Test cb2Bib functionality
*/
class c2bTests
{

public:
    c2bTests();
    ~c2bTests();

    int allTests();
    int writeInformation();


private:
    QString _bibliographic_dir;
    QTextStream& cout;
    int _failed_test_count;
    int _test_count;
    void author_parser();
    void check_abbreviations_txt();
    void check_test(const bool passed, const QString& input, const QString& output);
    void compression_check();
    void heuristic(bibParser& bp, const bibReference& reference, const QString& text);
    void heuristic_author();
    void heuristic_check_patterns();
    void heuristic_journal();
    void heuristic_misc();
    void heuristic_pvny();
    void write(const bibParser& bp, const bibReference& reference);
    void write_information();

    static QString decomposition(const QChar& c);

    static inline const char* boolToStr(bool b)
    {
        if (b)
            return "passed";
        else
            return "failed";
    }
};

#endif
