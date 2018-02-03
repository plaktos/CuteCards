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

#ifndef DECKOPTIONSPANEL_H
#define DECKOPTIONSPANEL_H

/*
 *
 * Provides a panel in Deck Editor tab for altering the deck title
 * and importing/exporting other formats.
 * getTitle() returns the title entered for the deck by the user
 * Sends the signals ImportCSVButtonPressed, ExportCSVButtonPressed
*/

#include <QFrame>
#include<QPushButton>
#include<QLineEdit>
#include<QGridLayout>

class DeckOptionsPanel : public QFrame
{
    Q_OBJECT
public:
    explicit
    DeckOptionsPanel(QWidget* parent = nullptr);

    QString getTitle() const                   { return titleLineEdit->text(); }
    void clearTitle()                          { titleLineEdit->clear(); }

signals:
    void ImportCSVButtonPressed();
    void ExportCSVButtonPressed();


private:
    QGridLayout *mainLayout;

    QLineEdit *titleLineEdit;
    QPushButton *importCSVButton;
    QPushButton *exportCSVButton;
};

#endif // DECKOPTIONSPANEL_H
