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

#ifndef DECKEDITORTAB_H
#define DECKEDITORTAB_H

/*
 * Deck Editor tab is where the user can create/import new,
 * edit/export preexisting decks.
*/

#include <QWidget>
#include<QFrame>
#include<QList>
#include<QFileDialog>
#include<QJsonDocument>
#include<QGridLayout>
#include<QLineEdit>

#include "deck.h"
#include "deckloader.h"
#include "wordsearcher.h"
#include "wordeditor.h"
#include "deckeditorsavebar.h"
#include "deckoptionspanel.h"

class DeckEditorTab : public QWidget
{
    Q_OBJECT
public:
    explicit DeckEditorTab(QWidget *parent = nullptr);

    // Assigns the new deck to workingDeck and initializes
    // the child widgets, to represent the new deck.
    void loadDeck(const Deck& deck);
signals:

    // Signal that tells the central widget, that the user has finished
    // editing the deck and can switch back to Deck Selection tab,
    // sent when the user clicks on one of the buttons in DeckEditorSaveBar.
    void finishedDeckEditing();

    // Signal that tells the child widgets that the deck has changed,
    // and they should update their contents.
    void workingDeckChanged(const Deck& newdeck);

public slots:
    // Prompts the user for a filename to save the workingDeck as a .deck file.
    // then converts the workingDeck to a json representation and saves it.
    // Connected to the saveButton in DeckEditorSaveBar
    void saveDeck();

    // Imports a deck from CSV values, and prompts the user for the languages,
    // that should be assigned to the deck
    void importDeckFromCSV();

    // To implement
    void exportDeckToCSV();

    // Connected to WordSearcher ToEditFlashcardAt signal,
    // loads the flashcard seletcted by the user on the WordScrollList widget
    // into the WordEditor for editing
    void LoadFlashcardAtIntoWordEditor(int index);

    // Connected to WordEditor addCardPressedWithCard,
    // adds the new card with the data entered by the user on the WordEditor widget.
    void addFlashcardToWorkingDeck(const Flashcard& card);

    // If the user has previously selected a word from WordSearcher
    // it gets loaded into WordEditor, where the user can change the data,
    // related to that flashcard. The user can then overwrite the old card,
    // with this new one.
    // Connected to WordEditor saveCardPressedWithCard.
    // replaces the card in workingDeck[index] with the card in the argument
    void saveFlashcardToWorkingDeck(const int &index,
                               const Flashcard& card);

    // Deletes the flashcard from the working deck at index.
    // Connected to WordSearcher toDeleteEntryAt signal.
    void deleteFlashcardFromWorkingDeckAt(const int &index);

private:
    QGridLayout *mainLayout;

    WordSearcher *wordSearcher;
    WordEditor *wordEditor;
    DeckOptionsPanel *deckOptionsPanel;
    DeckEditorSaveBar *deckEditorSaveBar;
    Deck workingDeck;

};

#endif // DECKEDITORTAB_H
