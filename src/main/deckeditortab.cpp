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

#include "deckeditortab.h"

DeckEditorTab::DeckEditorTab(QWidget *parent)
    : QWidget(parent)
{
    wordSearcher = new WordSearcher(this);
    wordEditor = new WordEditor;
    deckOptionsPanel = new DeckOptionsPanel;
    deckEditorSaveBar = new DeckEditorSaveBar;

    mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(5,10,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(wordEditor, 2,0,1,1);
    mainLayout->addWidget(deckOptionsPanel, 1,0,1,1);
    mainLayout->addWidget(wordSearcher, 0,1,4,1);
    mainLayout->addWidget(deckEditorSaveBar, 0,3,4,1);

    setLayout(mainLayout);

    connect(deckEditorSaveBar, &DeckEditorSaveBar::saveButtonPressed,
            this, &DeckEditorTab::saveDeck);
    connect(deckEditorSaveBar, &DeckEditorSaveBar::saveButtonPressed,
            this, &DeckEditorTab::finishedDeckEditing);
    connect(deckEditorSaveBar, &DeckEditorSaveBar::cancelButtonPressed,
            this, &DeckEditorTab::finishedDeckEditing);

    connect(wordEditor, &WordEditor::addCardPressedWithCard,
            this, &DeckEditorTab::addFlashcardToWorkingDeck);
    connect(wordEditor, &WordEditor::saveCardPressedWithCard,
            this, &DeckEditorTab::saveFlashcardToWorkingDeck);

    connect(wordSearcher, &WordSearcher::ToDeleteEntryAt,
            this, &DeckEditorTab::deleteFlashcardFromWorkingDeckAt);
    connect(wordSearcher, &WordSearcher::ToEditFlashcardAt,
            this, &DeckEditorTab::LoadFlashcardAtIntoWordEditor);

    connect(this, &DeckEditorTab::workingDeckChanged,
            wordSearcher, &WordSearcher::refreshListWithDeck);

    connect(deckOptionsPanel, &DeckOptionsPanel::ImportCSVButtonPressed,
            this, &DeckEditorTab::importDeckFromCSV);
    connect(deckOptionsPanel, &DeckOptionsPanel::ExportCSVButtonPressed,
            this, &DeckEditorTab::exportDeckToCSV);
}

void
DeckEditorTab::loadDeck(const Deck &deck){
    workingDeck = deck;
    deckOptionsPanel->clearTitle();
    wordEditor->InitWithDeck(workingDeck);
    emit workingDeckChanged(workingDeck);
}

void
DeckEditorTab::importDeckFromCSV(){
    QString filename = QFileDialog::getOpenFileName(this, "Open .CSV",
                                                    "./", "CSV(*.csv)");

    workingDeck = DeckLoader::fromCSVFile(filename);

    // If the deck is not empty, prompt the user to add languages,
    // equal to the number of needed languages in the deck.
    if(!workingDeck.empty()){
        for(int i = 0; i < workingDeck.getNumOfLanguages(); ++i){
            wordEditor->PromptToAddLanguageToScrollList();
        }
        wordEditor->setLanguageEditMode(false);
    }
    else{
        wordEditor->setLanguageEditMode(true);
    }

    emit workingDeckChanged(workingDeck);
}

void
DeckEditorTab::exportDeckToCSV(){

}

void
DeckEditorTab::LoadFlashcardAtIntoWordEditor(int index){
    wordEditor->setFlashcard(index,workingDeck[index]);
}

void
DeckEditorTab::addFlashcardToWorkingDeck(const Flashcard &card){
    if(!card.empty()){
        workingDeck.addCard(card);
        emit workingDeckChanged(workingDeck);
    }
}

void
DeckEditorTab::saveFlashcardToWorkingDeck(const int &index, const Flashcard &card){
    if(!card.empty()){
            workingDeck[index] = card;
            emit workingDeckChanged(workingDeck);
    }
}

void
DeckEditorTab::deleteFlashcardFromWorkingDeckAt(const int &index)
{
    workingDeck.removeAt(index);
    emit workingDeckChanged(workingDeck);
}

void
DeckEditorTab::saveDeck(){
    if(!(deckOptionsPanel->getTitle() == "")){
        workingDeck.setTitle(deckOptionsPanel->getTitle());
        workingDeck.setLanguages(wordEditor->getLanguages());
        QString filename = QFileDialog::getSaveFileName(this, "Save as .deck",
                                                        "./decks", "Decks (*.deck)");
        QFile deckfile(filename);
        if(!deckfile.open(QIODevice::WriteOnly)){
            qWarning("Couldn't open file for writing.");
            return;
        }

        QJsonDocument json(workingDeck.ToJsonObject());
        deckfile.write(json.toJson());
        deckfile.close();
    }
}
