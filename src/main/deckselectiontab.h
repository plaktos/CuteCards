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

#ifndef DECKSELECTIONTAB_H
#define DECKSELECTIONTAB_H

#include <QWidget>
#include<QVector>
#include<QDir>
#include<QStringList>
#include<QMap>
#include<QGridLayout>
#include<QRandomGenerator>

#include<algorithm>

#include "decksearcher.h"
#include "deckloader.h"

class DeckSelectionTab : public QWidget
{
    Q_OBJECT
public:
    explicit DeckSelectionTab(QWidget *parent = nullptr);

    QSize sizeHint() const override                                     { return QSize(800, 600); }

signals:
    // Signal requesting an exam to start with the deck created from
    // the selections in the availableDecksSearcher
    void ExamToStartWithDeck(const QWeakPointer<Deck>& deck);

    // Signal with the new decks, connected to DeckSearcher setDeck slot.
    void AvailableDecksChanged(const QList<Deck> &decklist);

    // Notifies CentralWidget to load the DeckEditor with the signal argument.
    void ToEditDeck(const Deck& deck);

public slots:
    inline
    void SignalToEditAvailableDeckAt(const int &index)                  { emit ToEditDeck(availableDecks[index]); }

    // Loads the decks from the ./decks folder into availableDecks.
    // and emits AvailableDecksChanged
    void LoadAvailableDecks();

    // Creates a new deck based on the selections in availableDeckSearcher.
    // Shuffles the deck.
    // Sets the key language based on the argument keylangindex
    // and emits an ExamToStartWithDeck signal.
    void StartExam(int keylangindex);

private:
    void ShuffleExamDeck();

    QVBoxLayout *mainLayout;

    DeckSearcher *availableDecksSearcher;

    QList<Deck> availableDecks;
    QSharedPointer<Deck> currExamDeck;
};

#endif // DECKSELECTIONTAB_H
