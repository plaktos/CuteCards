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

#ifndef DECKSEARCHER_H
#define DECKSEARCHER_H

/*
 * DeckSearcher is a container widget for DeckScrollList
 * DeckSearchBar, startButton and KeyLanguageSelector,
 *
 * Handles communication between these child widgets and DeckSelectionTab
*/


#include <QWidget>
#include<QGridLayout>
#include<QSizePolicy>
#include<QPushButton>
#include<QPalette>

#include "decksearchbar.h"
#include "deckscrolllist.h"
#include "deck.h"
#include "keylanguageselector.h"

class DeckSearcher : public QWidget
{
    Q_OBJECT
public:
    explicit DeckSearcher(QWidget *parent = nullptr);

    // Returns the selected entries' indexes in deckScrollList
    QVector<int> selection()                                    { return deckScrollList->getSelectedEntries(); }

signals:
    // Sends out a signal, notifing DeckSelectionTab that the user
    // wants to start an exam. keylandindex is determined by the
    // users choice of key language on the keyLanguageSelector widget.
    void StartButtonPressedWithKeyIndex(int keylangindex);

    // Forwarded signal from DeckScrollList
    void EditButtonPressedOnEntry(const int &index);

public slots:
    void setDeck(const QList<Deck> &newdeck)                  { decks = &newdeck;
                                                                refillScrollList(); }

    // Initializes the keyLanguageSelector widget, based on the languages
    // from the deck at decks[index]
    void initKeyLanguageSelectorWithDeckAt(int index);

private:
    // Repopulates the scroll list with the data from the current deck list
    void refillScrollList();

    QGridLayout *mainLayout;

    DeckSearchBar *deckSearchBar;
    DeckScrollList *deckScrollList;
    QPushButton *startButton;
    KeyLanguageSelector *keyLanguageSelector;

    const QList<Deck> *decks;
};

#endif // DECKSEARCHER_H
