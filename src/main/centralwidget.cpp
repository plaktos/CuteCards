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

#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{

    // Create the tabs
    tabSelector = new TabSelector;
    examTab = new ExamTab;
    deckSelectionTab = new DeckSelectionTab;
    deckEditorTab = new DeckEditorTab;
    //statisticsTab = new StatisticsTab;

    // Hide all tabs initially
    deckSelectionTab->setHidden(true);
    examTab->setHidden(true);
    deckEditorTab->setHidden(true);
    //statisticsTab->setHidden(true);

    // Initialize the Layout and add the widgets
    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(examTab);
    mainLayout->addWidget(deckSelectionTab);
    mainLayout->addWidget(deckEditorTab);
    //mainLayout->addWidget(statisticsTab);
    mainLayout->addWidget(tabSelector);

    // Setup this
    setLayout(mainLayout);


    //Connections with tabSelector
    connect(tabSelector, SIGNAL(DeckSelectionTabSelected()),
            this, SLOT(changeToDeckSelectionTab()));
    connect(tabSelector, SIGNAL(DeckEditorTabSelected()),
            this, SLOT(changeToDeckEditorTab()));
    connect(tabSelector, SIGNAL(StatisticsTabSelected()),
            this, SLOT(changeToStatisticsTab()));

    //Connections between tabs
    connect(deckSelectionTab, &DeckSelectionTab::ExamToStartWithDeck,
            this, &CentralWidget::StartExamWithDeck);

    connect(deckSelectionTab, &DeckSelectionTab::ToEditDeck,
            this, &CentralWidget::StartDeckEditorWithDeck);

    //Start off with Deck Selection.
    //Change later to a welcome tab
    changeToDeckSelectionTab();
}

void
CentralWidget::HideAllTabs(){
    examTab->setHidden(true);
    deckSelectionTab->setHidden(true);
    deckEditorTab->setHidden(true);
    //statisticsTab->setHidden(true);
}

void
CentralWidget::changeToDeckSelectionTab(){

    //If exam is running, abort it

    if(deckSelectionTab->isHidden()){
        HideAllTabs();
        deckSelectionTab->setHidden(false);
        //Upon changing to Deck selection we load the available decks.
        // Change later to a button to reload.
        deckSelectionTab->LoadAvailableDecks();
    }
}

void
CentralWidget::StartExamWithDeck(const QWeakPointer<Deck> &d){

    //If exam is running, abort it
    HideAllTabs();
    examTab->setHidden(false);
    examTab->StartExamWithDeck(d);
}

void
CentralWidget::changeToDeckEditorTab(){

    //If exam is running, abort it
    deckEditorTab->loadDeck(Deck());
    HideAllTabs();
    deckEditorTab->setHidden(false);
}

void
CentralWidget::StartDeckEditorWithDeck(const Deck& deck){
    deckEditorTab->loadDeck(deck);
    HideAllTabs();
    deckEditorTab->setHidden(false);
}

void
CentralWidget::changeToStatisticsTab(){

    //If exam is running, abort it
    /*
    if(statisticsTab->isHidden()){
        HideAllTabs();
        statisticsTab->setHidden(false)
    }
    */
}
