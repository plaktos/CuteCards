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

#ifndef DECKSEARCHBAR_H
#define DECKSEARCHBAR_H

/*
 * To be implemented, currently just a QLineEdit
 *
*/

#include <QLineEdit>
#include<QMouseEvent>
#include<QFocusEvent>

class DeckSearchBar : public QLineEdit
{
public:
    DeckSearchBar(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;

private:

};

#endif // DECKSEARCHBAR_H
