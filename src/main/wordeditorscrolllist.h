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

#ifndef WORDEDITORSCROLLLIST_H
#define WORDEDITORSCROLLLIST_H

/*
 * WordEditorScrollList provides a form layout
 * of language - word, for the user to alter
 * the words in the deck loaded into DeckEditor.
*/

#include <QWidget>
#include<QFormLayout>
#include<QString>
#include<QLabel>
#include<QLineEdit>
#include<QVector>

#include"flashcard.h"

class WordEditorScrollList : public QWidget
{
    Q_OBJECT
public:
    explicit WordEditorScrollList(QWidget *parent = nullptr);

    // Clears the languages and the word lines
    void clear();

    // Clears the words in the word lines
    void clearValues();

    // adds a new language - word pair
    void addEditingLineForLanguage(const QString& language);

    // loads the words from the card into the word lines
    void loadFromCard(const Flashcard& card);

    // return a Flashcard constructed from the values in the word lines.
    Flashcard toCard();

    QStringList getLanguages();
    QSize sizeHint() const override;

private:
    QFormLayout *mainLayout;

    QVector<QLineEdit *> valueLines;
    QVector<QLabel *> labelLines;
};

#endif // WORDEDITORSCROLLLIST_H
