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
    bottomButton = new QPushButton;

    // Add QScrollArea to deckScrollList
    DeckScrollArea *scrollArea = new DeckScrollArea;
    scrollArea->setWidget(deckScrollList);
    scrollArea->setBackgroundRole(QPalette::Midlight);

    // Setup layout
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(deckSearchBar);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(bottomButton);

    // Setup this
    setLayout(mainLayout);


    // Connections
    connect(deckSearchBar, &DeckSearchBar::NeedTitleSearchFor,
            deckScrollList, &DeckScrollList::doATitleSearch);

    connect(deckSearchBar, &DeckSearchBar::NeedLanguageSearchFor,
            deckScrollList, &DeckScrollList::doALanguageSearch);

    connect(bottomButton, &QPushButton::pressed,
            this, &DeckSearcher::bottomButtonPressed);

    connect(deckScrollList, &DeckScrollList::EditButtonPressedOnEntry,
            this, &DeckSearcher::EditButtonPressedOnEntry);

    connect(deckScrollList, &DeckScrollList::languageLockModeChanged,
            deckSearchBar, &DeckSearchBar::setLock);
}

void
DeckSearcher::refillScrollList(){
    deckScrollList->clearEntries();
    for(auto const &deck : *decks){
        deckScrollList->addEntry(&deck);
    }
}
