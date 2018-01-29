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

#ifndef DECKSCROLLLIST_H
#define DECKSCROLLLIST_H

/*
 * DeckScrollList holds a list of DeckScrollListEntry widgets
 * provides a way for the user to select one more multiple decks
 * and then send a signal with these indexes.
 * Should be contained within a DeckSearcher, which provides a SearchBar,
 * whose textChanged signal should be connected with DeckScrollList changeTextToSearchFor,
 * Apply DeckScrollArea to it after construction to make it scrollable.
*/

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QRegularExpression>
#include<QScrollArea>

#include "windowdefines.h"
#include "deckscrolllistentry.h"
#include "deck.h"

const static unsigned int DECKSCROLLIST_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT-200;
const static unsigned int DECKSCROLLIST_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/2-50;

class DeckScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit
    DeckScrollArea(QWidget *parent = nullptr)
        : QScrollArea(parent)                                       {setSizePolicy(QSizePolicy::MinimumExpanding,
                                                                                   QSizePolicy::MinimumExpanding);}
};

class DeckScrollList : public QWidget
{
    Q_OBJECT
public:
    explicit DeckScrollList(QWidget *parent = nullptr);
    ~DeckScrollList()                                               { clearEntries(); }

    QSize sizeHint() const override                                 { return QSize(DECKSCROLLIST_HINT_WIDTH,
                                                                                   DECKSCROLLIST_HINT_HEIGHT); }

    // Adds a new DeckScrollListEntry, and intializes a label,
    // based on the deck passed as argument.
    void addEntry(const Deck *d);

    QMap<int, Qt::CheckState> getSelectedDeckIndexes()                { return selectedEntries; }

    // Deletes all previous Labels and clears deckList
    void clearEntries();

signals:
    void EditButtonPressedOnEntry(const int &index);
    void languageLockModeChanged(bool lock);

public slots:
    //Searches for textToSearchFor in the deck Titles, and makes the Labels,
    //which correspond to those titles visible
    void doATitleSearch(const QString &text);
    void doALanguageSearch(const QString &text);

private:
    //Hides all labels, called by doASearch(), before doing a search
    void setHiddenForAllTitleLabels(bool flag);
    void SelectedStateChangedOnEntry(const int &index,
                                     const Qt::CheckState &state);
    void lockLanguages(const QStringList& list);
    void unlockLanguages();

    // Layout is vertical. Labels are listed one after another
    QVBoxLayout *mainLayout;

    QList<DeckScrollListEntry *> scrollListEntries;
    QMap<int, Qt::CheckState> selectedEntries;

    bool languageLockMode;

};

#endif // DECKSCROLLLIST_H
