#include<QObject>
#include<QtTest/QtTest>

#include"deckloader.h"

class test_deckloader : public QObject
{
    Q_OBJECT
public:
    test_deckloader();

private slots:
    void test_fromDeckFile_pos();
    void test_fromDeckFile_neg();

    void test_fromCSVFile_pos();
    void test_fromCSVFile_neg();
};
