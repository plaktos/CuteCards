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
 * Upon selecting a deck the list gets refreshed, to only show compatible decks.
 * Contained within a DeckSearcher, which provides a SearchBar,
 * whose NeedSearch signals is connected to the corresponding slots.
 * QScrollArea is applied to it after construction to make it scrollable.
*/

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QRegularExpression>
#include<QScrollArea>

#include "deckscrolllistentry.h"
#include "deck.h"

class DeckScrollList : public QWidget
{
    Q_OBJECT
public:
    explicit
    DeckScrollList(QWidget *parent = nullptr);

    ~DeckScrollList()                                               { clearEntries(); }

    // sizeHint returns a low number because the sizePolicy is set to expanding.
    // resize is called everytime the list gets refreshed.
    // this is to ensure the widget never over expands.
    QSize sizeHint() const override                                 { return QSize(100, 100); }

    // Adds a new DeckScrollListEntry, and intializes a label,
    // based on the deck passed as argument.
    // connects the new entry with editButtonPressedOnEntry,
    // and setSelectedForEntryAt
    void addEntry(const Deck *d);

    // Return the indexes of the decks selected by the user
    QVector<int> getSelectedEntries();

    // Deletes all previous labels and clears deckList
    void clearEntries();

signals:
    // Sent when the user wishes to edit one of the decks in the entry list
    // CentralWidget is connected to it and switches to Deck Edit tab,
    // loading the deck at index into the editor.
    void EditButtonPressedOnEntry(const int &index);

    // Emitted when the language lock mode changes,
    // Language lock mode happens when the user first selects a deck,
    // the languages of the selected deck which other decks can be selected.
    // connected with DeckSearchBar in DeckSearcher,
    // notifies that the search bar should be locked down.
    void languageLockModeChanged(bool lock);

    // Notifies DeckSearcher which deck's languages is locked,
    // used by KeyLanguageSelector to determine which languages
    // can the user choose between to become the key language for the exam.
    void languagesLockedFromDeckAt(int index);

    // Nootifies DeckSearcher that the language lock mode is cleared,
    // and KeyLanguageSelector should be cleared.
    void languageLockModeCleared();

public slots:
    // Searches for the argument text in the deck Titles, and marks the decks,
    // with matching titles for search matched.
    // this determines whether they are shown to the user or not in the
    // refreshEntries method.
    void doATitleSearch(const QString &text);

    // Searches for the argument text in the deck langauges,
    // if it matches it marks the deck as search matched
    void doALanguageSearch(const QString &text);

    // Connected with DeckScrollListEntries,
    // upon changing the selection state of a DeckScrollListEntry it sends a signal,
    // with it's id and selection flag.
    // That signal is connected to this methor,
    // which stores it in selectedEntries.
    void setSelectedForEntryAt(int index, bool flag);

private:
    // Determines which decks should be visible to the user,
    // based on previous selections and searches,
    // And then changes the corresponding deck's entry's hidden parameter.
    void refreshEntries();

    // Calls setHidden(true) for all entries
    void setHiddenForAllEntry(bool flag);

    // Calls setHidden(flag) for entry at index
    void setHiddenForEntryAt(int index, bool flag);

    // Sets languageLockMode to true and adds the entries,
    // that match the argument languages to languageMatchedEntries.
    void lockLanguages(const QStringList& list);
    void unlockLanguages();

    QVBoxLayout *mainLayout;

    QList<DeckScrollListEntry *> scrollListEntries;

    bool selectionActive;
    // A map to keep track of entries that match the search,
    // we search within this to see which ones are selected.
    // in index - bool fashion. Initially all of them are set to 1,
    // meaning they all match the search
    QMap<int, bool> searchedEntries;

    // Contains indexes of entries that are selected
    QMap<int, bool> selectedEntries;
    // Contains indexes of entries that are matched by language.
    QMap<int, bool> languageMatchedEntries;

    bool languageLockMode;
    bool emptyTitleSearch;

};

#endif // DECKSCROLLLIST_H
