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

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

/*
 * CentralWidget handles all the tabs.
 * Its member TabSelector is a collection of buttons,
 * it sends signals based on which tab is selected,
 * then CentralWidget can handle the actual switching.
 * It switches between DeckSelection, DeckEditor Exam and Statistics,
 * and handles the communication between them.
 *
*/

#include <QWidget>

#include "tabselector.h"
#include "examtab.h"
#include "deckselectiontab.h"
#include "deckeditortab.h"

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);

signals:

public slots:
    void changeToDeckSelectionTab();
    void changeToDeckEditorTab();
    void changeToStatisticsTab();
    void StartExamWithDeck(const QWeakPointer<Deck> &d);
    void StartDeckEditorWithDeck(const Deck& deck);

private:
    // Used to hide all tabs, then we unhid the current tab, called by the changeTo*Tab functions
    void HideAllTabs();

    // Layout for *this. always has the TabSelector on top and below that the current tab.
    QHBoxLayout *mainLayout;

    // Widget that contains buttons corresponding to tabs sends signals
    // that need to be connected to the correct changeTo*Tab function
    TabSelector *tabSelector;

    // Exam tab is the tab where the actual flashcard exam takes place.
    ExamTab *examTab;

    // Deck Selection tab is where the user can select decks for the current exam.
    DeckSelectionTab *deckSelectionTab;

    // Deck Editor tab is where the user can create new or edit existing decks.
    DeckEditorTab *deckEditorTab;

    // Statistics tab shows statistics about the users performance.
    // And provides the ability to start an exam based on the decks
    // the user knows the least.
    //StatisticsTab *statisticsTab;
};

#endif // CENTRALWIDGET_H
