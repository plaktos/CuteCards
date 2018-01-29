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

#ifndef TABSELECTOR_H
#define TABSELECTOR_H

/*
 * Simple widget holding buttons corresponding to tabs,
 * sends out signals if they are pressed.
 *
 * Later will be customized for custom gui.
*/

#include <QWidget>
#include<QSize>
#include<QHBoxLayout>
#include<QPushButton>

#include "windowdefines.h"

//TabSelector variables
const static unsigned int CENTRAL_TABSELECTOR_HINT_WIDTH = MAINWINDOW_HINT_WIDTH;
const static unsigned int CENTRAL_TABSELECTOR_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT/8;
const static unsigned int CENTRAL_TABSELECTOR_BUTTONS_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/5;

class TabSelector : public QWidget
{
    Q_OBJECT
public:
    explicit
    TabSelector(QWidget *parent = nullptr);

    QSize
    sizeHint() const override                   { return QSize(CENTRAL_TABSELECTOR_HINT_WIDTH,
                                                               CENTRAL_TABSELECTOR_HINT_HEIGHT); }

signals:
    void DeckSelectionTabSelected();
    void DeckEditorTabSelected();
    void StatisticsTabSelected();

public slots:

private:
    QHBoxLayout *mainLayout;

    QPushButton *deckSelectionTabButton;
    QPushButton *deckEditorTabButton;
    QPushButton *statisticsTabButton;

};

#endif // TABSELECTOR_H
