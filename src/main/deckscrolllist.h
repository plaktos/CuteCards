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
 * Should be contained within a DeckSearcher, which provides a SearchBar,
 * whose textChanged signal should be connected with DeckScrollList changeTextToSearchFor,
 * Apply DeckScrollArea to it after construction to make it scrollable.
*/

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QTimer>
#include<QRegularExpression>
#include<QScrollArea>

#include "windowdefines.h"
#include "deckscrolllistentry.h"

const static unsigned int DECKSCROLLIST_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT-200;
const static unsigned int DECKSCROLLIST_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/4;

class DeckScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit
    DeckScrollArea(QWidget *parent = nullptr)
        : QScrollArea(parent) { }

    QSize sizeHint() const override                                 { return QSize(DECKSCROLLIST_HINT_WIDTH,
                                                                                   DECKSCROLLIST_HINT_HEIGHT); }
};

class DeckScrollList : public QWidget
{
    Q_OBJECT
public:
    explicit DeckScrollList(QWidget *parent = nullptr);

    QSize sizeHint() const override                                 { return QSize(DECKSCROLLIST_HINT_WIDTH,
                                                                                   DECKSCROLLIST_HINT_HEIGHT); }

signals:
    // Upon the user selecting decks a selectionChanged signal gets sent.
    void selectionChanged(QVector<int> indexes);
    void EditButtonPressedOnEntry(const int &index);
    void SelectedStateChangedOnEntry(const int &index,
                                     const Qt::CheckState &state);

public slots:
    // changes the text to search for among the titles, and start the timer,
    // so as to avoid searching every time the SearchBar recieves an input.
    void changeTextToSearchFor(const QString& text)                  { textToSearchFor = text;
                                                                          searchTimer->start(300);}

    // Changes the deckTitleList, should be connected to DeckSearcher's DeckTitleListChanged signal,
    void setDeckTitleList(const QStringList& titles)                 { deckTitleList = titles;
                                                                          InitTitleLabels(); }

private:
    // Deletes previous Labels, and initializes new ones,
    // based on the titles in deckTitleList.
    void InitTitleLabels();

    //Hides all labels, called by doASearch(), before doing a search
    void HideAllTitleLabels();

    //Searches for textToSearchFor in the deck Titles, and makes the Labels,
    //which correspond to those titles visible
    void doASearch();

    // Layout is vertical. Labels are listed one after another
    QVBoxLayout *mainLayout;

    QStringList deckTitleList;
    QList<DeckScrollListEntry *> scrollListEntries;
    QTimer *searchTimer;
    QString textToSearchFor;
};

#endif // DECKSCROLLLIST_H
