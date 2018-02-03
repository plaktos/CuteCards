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

#ifndef WORDSCROLLLISTENTRY_H
#define WORDSCROLLLISTENTRY_H

/*
 * WordScrollListEntry consists of
 * a WordScrollListEntryDeleteButton and
 * a number of WordScrollListEntryLabel labels
 *
 * It is contained in a WordScrollList,
 * where each entry corresponds to one flashcard
 * in the deck.
*/

#include <QWidget>
#include<QCheckBox>
#include<QHBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QFont>
#include<QMouseEvent>

class WordScrollListEntryLabel : public QLabel
{
    Q_OBJECT
public:
    explicit
    WordScrollListEntryLabel(const QString &text,
                             QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class WordScrollListEntryDeleteButton : public QPushButton
{
    Q_OBJECT
public:
    explicit
    WordScrollListEntryDeleteButton(const QString &text,
                                    QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class WordScrollListEntry : public QWidget
{
    Q_OBJECT
public:
    explicit
    WordScrollListEntry(int index,
                        QWidget *parent = nullptr);

    void addWord(const QString& word);
    QStringList getWords()                      { return words; }
    QSize sizeHint() const override             { return QSize(300,30); }
signals:
    void selected(int id);
    void DeleteButtonPressed(int id);

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QHBoxLayout *mainLayout;
    int id;
    QStringList words;
    WordScrollListEntryDeleteButton *deleteButton;

};

#endif // WORDSCROLLLISTENTRY_H
