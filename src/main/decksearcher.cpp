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

#include "decksearcher.h"

DeckSearcher::DeckSearcher(QWidget *parent)
    : QWidget(parent)
{

    // Initialize members
    deckSearchBar = new DeckSearchBar;
    deckScrollList = new DeckScrollList;
    startButton = new QPushButton("Start");
    startButton->setMaximumSize(200,50);
    keyLanguageSelector = new KeyLanguageSelector;

    // Add QScrollArea to deckScrollList
    DeckScrollArea *scrollArea = new DeckScrollArea;
    scrollArea->setWidget(deckScrollList);
    QPalette scrollAreaPalette(scrollArea->palette());
    scrollAreaPalette.setColor(QPalette::Background, Qt::darkGray);
    scrollArea->setAutoFillBackground(true);
    scrollArea->setPalette(scrollAreaPalette);

    // Setup layout
    mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(5,0,5,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(deckSearchBar, 0,1,1,2);
    mainLayout->addWidget(scrollArea, 1,0,2,3);
    mainLayout->addWidget(startButton,3,2,1,1);
    mainLayout->addWidget(keyLanguageSelector, 3,0,1,2);

    // Setup this
    setLayout(mainLayout);


    // Connections
    connect(deckSearchBar, &DeckSearchBar::NeedTitleSearchFor,
            deckScrollList, &DeckScrollList::doATitleSearch);

    connect(deckSearchBar, &DeckSearchBar::NeedLanguageSearchFor,
            deckScrollList, &DeckScrollList::doALanguageSearch);

    connect(startButton, &QPushButton::pressed,
            [this](){
        emit StartButtonPressedWithKeyIndex(keyLanguageSelector->getKeyLanguageIndex());
    });

    connect(deckScrollList, &DeckScrollList::EditButtonPressedOnEntry,
            this, &DeckSearcher::EditButtonPressedOnEntry);

    connect(deckScrollList, &DeckScrollList::languageLockModeChanged,
            deckSearchBar, &DeckSearchBar::setLanguageLock);

    connect(deckScrollList, &DeckScrollList::languagesLockedFromDeckAt,
            this, &DeckSearcher::initKeyLanguageSelectorWithDeckAt);

    connect(deckScrollList, &DeckScrollList::languageLockModeCleared,
            [this](){
       keyLanguageSelector->clear();
    });
}

void
DeckSearcher::refillScrollList(){
    deckScrollList->clearEntries();
    for(auto const &deck : *decks){
        deckScrollList->addEntry(&deck);
    }
}

void
DeckSearcher::initKeyLanguageSelectorWithDeckAt(int index){
    QStringList languages = decks->at(index).getLanguages();

    keyLanguageSelector->clear();
    for(auto lang : languages){
        keyLanguageSelector->addLanguage(lang);
    }
}
