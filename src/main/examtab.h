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

#include <QWidget>
#include<QPushButton>
#include<QFileDialog>

#include "tab.h"
#include "exammainbox.h"
#include "deckloader.h"
#include "constdefines.h"

class ExamTab : public Tab
{
    Q_OBJECT
public:

    explicit
    ExamTab(QWidget *parent = nullptr);

    QSize sizeHint() const override                 { return QSize(EXAMTAB_HINT_WIDTH,EXAMTAB_HINT_HEIGHT); }

signals:
    void changeToNextCard(unsigned int i);
    void deckChanged(const QWeakPointer<Deck>& d);
    void toRevealCard();

public slots:
    void StartExamWithDeck(const QWeakPointer<Deck> &d);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void NextCard();

    QWeakPointer<Deck> deck;
    ExamMainBox *mainBox;

    int currCardIndex;
};

#endif // EXAMTAB_H
