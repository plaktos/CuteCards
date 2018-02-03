#include <QtTest/QtTest>

#include"tst_deckloader.h"

int main(){
    //Unit Tests

    test_deckloader deckLoaderTest;
    QTest::qExec(&deckLoaderTest);

    return 0;
}
