#include "wordsearcher.h"

WordSearcher::WordSearcher(QWidget *parent)
    : QWidget(parent)
{
    searchBar = new WordSearcherBar;
    wordScrollList = new WordScrollList(this);

    QScrollArea *wordScrollArea = new QScrollArea;
    wordScrollArea->setWidget(wordScrollList);
    QPalette scrollAreaPalette(wordScrollArea->palette());
    scrollAreaPalette.setColor(QPalette::Background, Qt::darkGray);
    wordScrollArea->setAutoFillBackground(true);
    wordScrollArea->setPalette(scrollAreaPalette);


    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(searchBar);
    mainLayout->addWidget(wordScrollArea);

    setLayout(mainLayout);
    setMinimumSize(300,350);

    connect(wordScrollList, &WordScrollList::EntrySelectedAt,
            this, &WordSearcher::ToEditFlashcardAt);

    connect(wordScrollList, &WordScrollList::DeleteButtonPressedForEntryAt,
            this, &WordSearcher::ToDeleteEntryAt);

    connect(searchBar, &WordSearcherBar::needSearchFor,
            wordScrollList, &WordScrollList::searchFor);

}

void
WordSearcher::refreshListWithDeck(const Deck &deck){
    wordScrollList->clear();
    for(int i = 0; i < deck.size(); ++i){
        wordScrollList->addEntry(deck.at(i));
    }
}
