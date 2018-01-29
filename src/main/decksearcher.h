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
 * DeckSearcher provides a widget, on which the user can
 * choose from loaded deck titles. These selections are emitted as indexes
 * DeckSelectionTab is connected to this signal, to update the current selection indexes
 * This widget contains a SearchBar, a DeckScrollList and a BottomButton,
 * typing in the SearchBar updates the contents of DeckScrollList, this is where
 * the user makes the selections
 * Pressing the bottom button sends out a bottomButtonPressed signal.
 * So this button can be programmed to do any functionality.
 * Normally the Deck Selection tab will contain two DeckSearch widgets.
*/


#include <QWidget>
#include<QVBoxLayout>
#include<QSizePolicy>
#include<QPushButton>

#include "decksearchbar.h"
#include "deckscrolllist.h"
#include "deck.h"
#include "windowdefines.h"

const static unsigned int DECKSEARCHER_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/3;
const static unsigned int DECKSEARCHER_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT - 50;

class DeckSearcher : public QWidget
{
    Q_OBJECT
public:
    explicit DeckSearcher(QWidget *parent = nullptr);

    QSize sizeHint() const override                             { return QSize(DECKSEARCHER_HINT_WIDTH,
                                                                               DECKSEARCHER_HINT_HEIGHT); }

    void setBottomButtonText(const QString &text)               { bottomButton->setText(text); }

    // Returns the selectionIndexes that are set by recieving a signal
    // to changeSelection
    QVector<int> selection()                                    { return selectionIndexes; }
    void setHideBottomButton(bool b)                                     { bottomButton->setHidden(b); }

signals:
    void bottomButtonPressed();

    // Just for forwarding the titles to the member DeckScrollList
    void DeckTitleListChanged(const QStringList &titles);

    void EditButtonPressedOnEntry(const int &index);
    void SelectedStateChangedOnEntry(const int &index,
                                     const Qt::CheckState &state);

public slots:
    void setDeckTitleList(const QStringList &titles)         { emit DeckTitleListChanged(titles); }

private:
    // Layout for this. Vertical layout, on the top is the DeckSearchBar,
    // Below that is the DeckScroll list, and on the bottom is a button
    QVBoxLayout *mainLayout;

    DeckSearchBar *deckSearchBar;
    DeckScrollList *deckScrollList;
    QPushButton *bottomButton;

    QVector<int> selectionIndexes;
};

#endif // DECKSEARCHER_H