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
 * Search bar for the DeckSearcher in Deck Selection tab.
 * Consists of two DeckSearchBarPart, one for title and one for language
 * searches. Sends signals NeedTitleSearchFor and NeedLanguageSearchFor
*/

#include<QWidget>
#include<QHBoxLayout>
#include <QLineEdit>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QFocusEvent>
#include<QTimer>

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

signals:
    void NeedTitleSearchFor(const QString& text);
    void NeedLanguageSearchFor(const QString& text);

public slots:
    void setLanguageLock(bool lock)             { languageSearcher->setReadOnly(lock);
                                                  locked = lock;
                                                  update(); }

protected:
    // overridden paintEvent, if the language search bar is locked,
    // it gets a dark grey background.
    void paintEvent(QPaintEvent *e) override;

private:
    QHBoxLayout *mainLayout;
    DeckSearchBarPart *titleSearcher;
    DeckSearchBarPart *languageSearcher;
    bool locked;

};

#endif // DECKSEARCHBAR_H
