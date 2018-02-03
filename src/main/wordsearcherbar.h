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

#ifndef WORDSEARCHERBAR_H
#define WORDSEARCHERBAR_H

/*
 * Search bar widget for WordSearcher
*/

#include <QWidget>
#include<QLineEdit>
#include<QTimer>

class WordSearcherBar : public QLineEdit
{
    Q_OBJECT
public:
    WordSearcherBar(QWidget* parent = nullptr);

signals:
    void needSearchFor(const QString& text);

protected:
    void mousePressEvent(QMouseEvent *e) override;

private:
    QTimer *searchTimer;

};

#endif // WORDSEARCHERBAR_H
