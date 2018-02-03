//
//This file is part of CuteCards software.
//
//    CuteCards is Flashcard software developed in C++, with the use of the Qt Framework
//    Copyright (C) 2018 Peter Lakatos
//
//    CuteCards is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    CuteCards is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with CuteCards.  If not, see <http://www.gnu.org/licenses/>.
//

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
