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

#ifndef EXAMTAB_H
#define EXAMTAB_H


/*
 * ExamTab is where the actual exam happens.
 * Contains an ExamMainBox member, and holds a weak pointer
 * to deck created from the decks selected by the user in the Deck Selection tab.
 * Upon user interaction it sends the data of the next Flashcard to
 * its ExamMainBox, where the words get drawn.
 *
*/

#include <QWidget>
#include<QPushButton>
#include<QFileDialog>
#include<QGridLayout>
#include<QTimer>

#include "exammainbox.h"
#include "deckloader.h"

class ExamTab : public QWidget
{
    Q_OBJECT
public:

    explicit
    ExamTab(QWidget *parent = nullptr);

    QSize sizeHint() const override                 { return QSize(800,600); }

signals:
    // Sends out a signal with the current key and restwords data of the
    // next Flashcard to be presented to the user.
    // Connected to ExamMainBox::setCard
    void changeToCard(const QString& key,
                      const QStringList& restwords);

    // Signal emitted upon user interaction. Notifies ExamMainBox,
    // to reveal the rest words content of the current Card
    void toRevealCard();

public slots:
    // Connected to DeckSelectionTab, starts an exam with the deck,
    // created from the user's selections on the Deck Selection tab
    void StartExamWithDeck(const QWeakPointer<Deck> &d);

protected:

    // Overriding the keyPressEvent for Enter and Space interaction
    void keyPressEvent(QKeyEvent *event) override;

private:
    // Changes the card data to the next card's and emits changeToCard
    void NextCard();

    QGridLayout *mainLayout;

    ExamMainBox *mainBox;
    QTimer *cardTimer;
    QPushButton *nextCardButton;
    QPushButton *revealCardButton;

    QWeakPointer<Deck> deck;

    QString currKey;
    QStringList currRestWords;
    int currCardIndex;
};

#endif // EXAMTAB_H
