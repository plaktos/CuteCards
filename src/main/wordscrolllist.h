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

#ifndef WORDSCROLLLIST_H
#define WORDSCROLLLIST_H

/*
 * WordScrollList provides a list of words in the deck
 * for the user to see and interact with.
 * If the user clicks on any one of the words in the list.
 * The word gets loaded into the WordEditor widget for editing.
*/

#include <QWidget>
#include<QVBoxLayout>
#include<QPaintEvent>
#include<memory>
#include<vector>

#include "flashcard.h"
#include"wordscrolllistentry.h"

class WordScrollList : public QWidget
{
    Q_OBJECT
public:
    ~WordScrollList();
    explicit WordScrollList(QWidget *parent = nullptr);

    void clear();
    void addEntry(const Flashcard& card);

signals:
    void EntrySelectedAt(int index);
    void DeleteButtonPressedForEntryAt(int index);

public slots:
    void searchFor(const QString& text);

private:

    QVBoxLayout *mainLayout;
    std::vector<std::unique_ptr<WordScrollListEntry>> entries;
};

#endif // WORDSCROLLLIST_H
