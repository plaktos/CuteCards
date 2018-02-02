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

#include<algorithm>

#include "windowdefines.h"
#include "decksearcher.h"
#include "deckloader.h"

const static unsigned int DECKSELECTIONTAB_HINT_WIDTH = MAINWINDOW_HINT_WIDTH;
const static unsigned int DECKSELECTIONTAB_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT;

class DeckSelectionTab : public QWidget
{
    Q_OBJECT
public:
    explicit DeckSelectionTab(QWidget *parent = nullptr);

    QSize sizeHint() const override                                     { return QSize(DECKSELECTIONTAB_HINT_WIDTH,
                                                                                       DECKSELECTIONTAB_HINT_HEIGHT); }

signals:
    // Send out a signal requesting an exam to start with the deck created from
    // the availableDeckSelectionIndexes
    void ExamToStartWithDeck(const QWeakPointer<Deck>& deck);

    // Send out a signal with the new titles of the decks
    void AvailableDecksChanged(const QList<Deck> &decklist);

    void ToEditDeck(const Deck& deck);

public slots:
    //inline
    //void chaneSelectedExamDecksList(const int &index,
    //                                Qt::CheckState state);            { examDecksSelectionIndexes[index] = state; }

    inline
    void SignalToEditAvailableDeckAt(const int &index)                  { emit ToEditDeck(availableDecks[index]); }

    void LoadAvailableDecks();

    // Connected to the signal of examDecksSearcher's bottom button.
    // Creates a new deck from the selectionIndexes
    // and emits the ExamToStartWithDeck signal
    void StartExam(int index);

protected:

private:
    QVBoxLayout *mainLayout;

    DeckSearcher *availableDecksSearcher;
    DeckSearcher *examDecksSearcher;

    QList<Deck> availableDecks;
    QList<Deck> examDecks;

    QSharedPointer<Deck> currExamDeck;

};

#endif // DECKSELECTIONTAB_H
