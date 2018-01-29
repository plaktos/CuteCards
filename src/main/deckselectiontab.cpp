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

#include "deckselectiontab.h"

DeckSelectionTab::DeckSelectionTab(QWidget* parent)
    : QWidget(parent)
{
    // Setup member widgets
    availableDecksSearcher = new DeckSearcher;
    availableDecksSearcher->setBottomButtonText("Start");
    //examDecksSearcher = new DeckSearcher;
    //examDecksSearcher->setBottomButtonText("Start");

    // Setup layout
    mainLayout = new QHBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addWidget(availableDecksSearcher);
    mainLayout->addStretch(25);
    //mainLayout->addWidget(examDecksSearcher);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);

    // Connections

    connect(this, &DeckSelectionTab::AvailableDeckTitlesChanged,
            availableDecksSearcher, &DeckSearcher::setDeckTitleList);

    //connect(examDecksSearcher, &DeckSearcher::SelectionChanged,
    //        this, &DeckSelectionTab::setExamDecksSelectedIndexes);

    //connect(examDecksSearcher, &DeckSearcher::bottomButtonPressed,
    //        this, &DeckSelectionTab::StartExam);

    connect(availableDecksSearcher, &DeckSearcher::EditButtonPressedOnEntry,
            this, &DeckSelectionTab::SignalToEditAvailableDeckAt);

    connect(availableDecksSearcher, &DeckSearcher::SelectedStateChangedOnEntry,
            this, &DeckSelectionTab::changeSelectedAvailableDecksList);

    // Temporary
    connect(availableDecksSearcher, &DeckSearcher::bottomButtonPressed,
            this, &DeckSelectionTab::StartExam);

}

void
DeckSelectionTab::LoadAvailableDecks(){
    availableDecks.clear();
    availableDecksSelectionIndexes.clear();

    QDir resDir("./res");
    QStringList entries = resDir.entryList(QStringList{"*.deck"});
    for(int i = 0; i < entries.size(); ++i){
        QString path = QString("res/") + entries[i];
        Deck deck = DeckLoader::fromDeckFile(path);
        if(!deck.empty()){
            availableDecks.append(deck);
        }
    }

    QStringList deckTitlesList;
    for(auto &deck : availableDecks){
        deckTitlesList.append(deck.getTitle());
    }

    for(int i = 0; i < availableDecks.size(); ++i)
        availableDecksSelectionIndexes.push_back(Qt::Unchecked);

    emit AvailableDeckTitlesChanged(deckTitlesList);
}

void
DeckSelectionTab::StartExam(){
    currExamDeck = QSharedPointer<Deck>(new Deck);
    for(int i = 0; i < availableDecksSelectionIndexes.size(); ++i){
        if(availableDecksSelectionIndexes[i] == Qt::Checked)
            currExamDeck.data()->mergeDeck(availableDecks[i]);
    }
    if(!currExamDeck.data()->empty()){
        emit ExamToStartWithDeck(currExamDeck.toWeakRef());
    }
}
