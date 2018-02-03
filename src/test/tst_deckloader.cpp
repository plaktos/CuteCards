#include "tst_deckloader.h"

test_deckloader::test_deckloader(){

}

void
test_deckloader::test_fromDeckFile_pos(){
    Deck deck_pos = DeckLoader::fromDeckFile("./res/test_pos.deck");
    QVERIFY(!deck_pos.empty());

    if(deck_pos.empty())
        QSKIP("Deck empty, skipping rest of test");

    QCOMPARE(deck_pos.size(), 3);
    QCOMPARE(deck_pos.getTitle(), "Test deck (positive)");

    QStringList langlist;
    langlist.append("english");
    langlist.append("chinese");
    langlist.append("pinyin");
    QCOMPARE(deck_pos.getLanguages(), langlist);

    QStringList wordlist;
    wordlist.append("apple");
    wordlist.append("苹果");
    wordlist.append("ping2 guo3");

    Flashcard at0(wordlist);
    QCOMPARE(deck_pos.at(0), wordlist);

    wordlist.clear();
    wordlist.append("table");
    wordlist.append("桌子");
    wordlist.append("zhuo1 zi0");

    Flashcard at1(wordlist);
    QCOMPARE(deck_pos.at(1), at1);

    wordlist.clear();
    wordlist.append("fire");
    wordlist.append("火");
    wordlist.append("huo3");

    Flashcard at2(wordlist);
    QCOMPARE(deck_pos.at(2), at2);
}

void
test_deckloader::test_fromDeckFile_neg(){
    Deck not_found = DeckLoader::fromDeckFile("./res/notfound.deck");
    QVERIFY(not_found.empty());

    Deck invalid_json = DeckLoader::fromDeckFile("./res/test_neg_json.deck");
    QVERIFY(invalid_json.empty());

    Deck invalid_deck = DeckLoader::fromDeckFile("./res/test_neg_deck.deck");
    QVERIFY(invalid_deck.empty());
}

void
test_deckloader::test_fromCSVFile_pos(){
    Deck deck_pos = DeckLoader::fromCSVFile("./res/test_pos.csv");
    QVERIFY(!deck_pos.empty());

    if(deck_pos.empty())
        QSKIP("Deck empty, skipping rest of test");

    QCOMPARE(deck_pos.size(), 3);

    QStringList wordlist;
    wordlist.append("爱");
    wordlist.append("ài");
    wordlist.append("to love");

    Flashcard at0(wordlist);
    QCOMPARE(deck_pos.at(0), wordlist);

    wordlist.clear();
    wordlist.append("八");
    wordlist.append("bā");
    wordlist.append("eight");

    Flashcard at1(wordlist);
    QCOMPARE(deck_pos.at(1), at1);

    wordlist.clear();
    wordlist.append("爸爸");
    wordlist.append("bà ba");
    wordlist.append("(informal) father");

    Flashcard at2(wordlist);
    QCOMPARE(deck_pos.at(2), at2);
}

void
test_deckloader::test_fromCSVFile_neg(){
    Deck not_found = DeckLoader::fromCSVFile("./res/notfound.csv");
    QVERIFY(not_found.empty());

    Deck invalid_csv = DeckLoader::fromCSVFile("./res/test_neg_invalid.csv");
    QVERIFY(invalid_csv.empty());

    Deck empty_csv = DeckLoader::fromCSVFile("./res/test_neg_empty.csv");
    QVERIFY(empty_csv.empty());
}
