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

/*
 * ExamMainBox is a widget where the contents of the current Flashcard
 * on a Key, rest words basis. The key is the word initially shown to the user,
 * the rest words are the words shown after user interaction.
 *
 * ExamMainBox gets it's contents from ExamTab, it only has access to the current card's key
 * and rest words.
 * Inside ExamMainBox is a LowerBox widget, which is used to draw labels with rest words contents.
 * LowerBox gets deleted and reinstated every time the user asks for the next card to be displayed.
 * This is to ensure that there is always an equal number of labels inside lower box to the number
 * of rest words on the Flashcard. Since the user will have the ability to merge decks,
 * there may be time when there are 3 rest words, and there may be time when there is only 2.
*/

#include<QWidget>
#include<QSize>
#include<QWeakPointer>
#include<QList>
#include<QVBoxLayout>
#include<QLabel>

#include "deck.h"
#include "windowdefines.h"

const static unsigned int EXAM_MAINBOX_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/2;
const static unsigned int EXAM_MAINBOX_HINT_HEIGHT = EXAM_MAINBOX_HINT_WIDTH;
const static unsigned int EXAM_MAINBOX_MIN_WIDTH = EXAM_MAINBOX_HINT_WIDTH/2;
const static unsigned int EXAM_MAINBOX_MIN_HEIGHT = EXAM_MAINBOX_MIN_WIDTH;

const static unsigned int EXAM_LOWERBOX_HINT_WIDTH = EXAM_MAINBOX_HINT_WIDTH;
const static unsigned int EXAM_LOWERBOX_HINT_HEIGHT = EXAM_MAINBOX_HINT_HEIGHT/3;

class LowerBox : public QWidget
{
    Q_OBJECT
public:

    explicit
    LowerBox(const QStringList &restwords, QWidget* parent = nullptr);

    QSize sizeHint() const override                     { return QSize(EXAM_MAINBOX_HINT_WIDTH, EXAM_LOWERBOX_HINT_HEIGHT); }

public slots:
    //Initializes the Labels based on restWordList.
    void RevealWords();

private:
    // Initializes QLabels from the QStringList argument and stores them in restWordLabels,
    // Called by the constructor, uses the constructor argument.
    void initRestWordLabels(const QStringList &restwords);

    //Creates a label and adds it to mainLayout
    void createRestWordLabel(const QString &string);

    QVBoxLayout *mainLayout;

    QFont restWordsFont;
    QList<QLabel *> restWordsLabels;
};

class ExamMainBox : public QWidget
{
    Q_OBJECT
public:
    explicit ExamMainBox(QWidget *parent = nullptr);

    QSize sizeHint() const override                     { return QSize(EXAM_MAINBOX_HINT_WIDTH, EXAM_MAINBOX_HINT_HEIGHT); }

signals:
    void toRevealCard();

protected:

public slots:

    // Changes the current key and rest words,
    // and then calls update() to make the keyword visible to the user.
    // Connected to ExamTab::changeToNextCard, which is emitted from
    // ExamTab::NextCard()
    void setCard(const QString& key,
                 const QStringList& restwords)          { setKeyWord(key);
                                                          setRestWords(restwords);
                                                          update(); }

    // emitts toRevealCard, so that LowerBox reveals it's labels,
    // and then calls update()
    void RevealCard();

private:
    // Deletes the current LowerBox and reinstates it.
    void resetLowerBox();

    inline
    void setKeyWord(const QString& key)                 { keyWordString = key;
                                                          keyWordLabel->setText(key); }

    inline
    void setRestWords(const QStringList wordlist)       { restWordsList = wordlist;
                                                          resetLowerBox(); }

    QVBoxLayout *mainLayout;
    QString keyWordString;
    QLabel *keyWordLabel;
    QStringList restWordsList;
    LowerBox* lowerBox;
};

#endif // EXAMMAINBOX_H
