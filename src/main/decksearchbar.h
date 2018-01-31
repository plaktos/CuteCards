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

#include<QWidget>
#include<QHBoxLayout>
#include <QLineEdit>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QFocusEvent>
#include<QTimer>

const static unsigned int DECKSEARCHBAR_HINT_WIDTH = 300;
const static unsigned int DECKSEARCHBAR_HINT_HEIGHT = 50;

class DeckSearchBarPart : public QLineEdit
{
    Q_OBJECT
public:
    DeckSearchBarPart(const QString& deftext,
                      QWidget* parent = nullptr);

signals:
    void needSearchFor(const QString& text);

protected:
    void mousePressEvent(QMouseEvent *e) override;

private:
    QTimer *searchTimer;
};

class DeckSearchBar : public QWidget
{
    Q_OBJECT
public:
    DeckSearchBar(QWidget* parent = nullptr);

    QSize sizeHint() const override             { return QSize(); }
signals:
    void NeedTitleSearchFor(const QString& text);
    void NeedLanguageSearchFor(const QString& text);

public slots:
    void setLanguageLock(bool lock)             { //titleSearcher->setReadOnly(lock);
                                                  languageSearcher->setReadOnly(lock);
                                                  locked = lock;
                                                  update(); }

protected:
    void paintEvent(QPaintEvent *e);

private:
    QHBoxLayout *mainLayout;
    DeckSearchBarPart *titleSearcher;
    DeckSearchBarPart *languageSearcher;
    bool locked;

};

#endif // DECKSEARCHBAR_H
