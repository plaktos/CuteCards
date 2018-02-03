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

#ifndef WORDSEARCHER_H
#define WORDSEARCHER_H

/*
 * WordSearcher is a widget, which contains a search bar,
 * which lets the user search among the words in the scroll list.
 * And the WordScrollList which contains WordScrollListEntry widgets,
 * each entry describes a Flashcard in the deck loaded into the
 * DeckEditor.
*/

#include <QWidget>
#include<QGridLayout>
#include<QScrollArea>

#include"deck.h"
#include"wordscrolllist.h"
#include "wordsearcherbar.h"

class WordSearcher : public QWidget
{
    Q_OBJECT
public:
    explicit
    WordSearcher(QWidget *parent = nullptr);

signals:
    // Signal that notifies the DeckEditor that the user selected,
    // a word in the WordScrollList and it should be loaded into the
    // WordEditor
    void ToEditFlashcardAt(int index);

    // Signal that notifies the DeckEditor that the user pressed the
    // delete button on one of the entries in WordScrollList and
    // it should be deleted from the deck.
    void ToDeleteEntryAt(int index);

public slots:
    // Populates the WordScrollList with the flashcard in deck
    // passed as an argument
    void refreshListWithDeck(const Deck& deck);

private:
    QGridLayout *mainLayout;
    WordSearcherBar *searchBar;
    WordScrollList *wordScrollList;

};

#endif // WORDSEARCHER_H
