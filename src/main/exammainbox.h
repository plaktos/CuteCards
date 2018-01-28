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

#ifndef EXAMMAINBOX_H
#define EXAMMAINBOX_H

#include<QWidget>
#include<QSize>
#include<QWeakPointer>
#include<QList>
#include<QVBoxLayout>
#include<QLabel>

#include "deck.h"
#include "constdefines.h"

class LowerBox : public QWidget
{
    Q_OBJECT
public:

    explicit
    LowerBox(const QList<QString> list,
             QWidget* parent = nullptr);

    QSize sizeHint() const override                     { return QSize(EXAM_MAINBOX_HINT_WIDTH, EXAM_LOWERBOX_HINT_HEIGHT); }

public slots:
    //Initializes the Labels based on the current card,
    //calls createRestWordLabel
    void RevealWords();

private:
    void initRestWordLabels();
    //Creates a label and adds it to mainLayout
    void createRestWordLabel(const QString& string);

    QVBoxLayout *mainLayout;

    QFont restWordsFont;
    QList<QString> restWordsList;
    QList<QLabel *> restWordsLabels;
};

class ExamMainBox : public QWidget
{
    Q_OBJECT
public:
    explicit ExamMainBox(QWidget *parent = nullptr);

    QSize sizeHint() const override                     { return QSize(EXAM_MAINBOX_HINT_WIDTH, EXAM_MAINBOX_HINT_HEIGHT); }

signals:
    void changeToNextCard(unsigned int);
    void toRevealCard();

protected:

public slots:
    void setCurrentDeck(QWeakPointer<Deck> d)           { deck = d; }
    void NextCard(unsigned int currCardIndex);
    void RevealCard();

private:
    void resetLowerBox();

    QVBoxLayout *mainLayout;
    QWeakPointer<Deck> deck;
    QString keyWordString;
    QLabel *keyWordLabel;
    QList<QString> restWordsList;
    LowerBox* lowerBox;
};

#endif // EXAMMAINBOX_H
