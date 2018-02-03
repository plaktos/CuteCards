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


    mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(searchBar, 0,1,1,1);
    mainLayout->addWidget(wordScrollArea, 1,0,1,2);

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
