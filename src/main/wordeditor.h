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

#ifndef WORDEDITOR_H
#define WORDEDITOR_H

/*
 * WordEditor is a widget on the Deck Editor tab.
 * Provides a way for the user to alter the Flashcards
 * found in the deck.
 * The user can create new ones or modify existing cards in the deck.
 * Contains a WordEditorScrollList and a WordEditorButtonBar
 * WordEditorScrollList contains a list of languages,
 * that are found in the deck and a QLineEdit where the user can,
 * enter or alter words for the corresponding language.
 *
 * AddLanguageDialog is a dialog that prompts the user for
 * a language, which then gets added to the WordEditor.
 * These dialogs are instated and their values are used in
 * WordEditor::PromptPromptToAddLanguageToScrollList
 *
*/

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QSize>
#include<QScrollArea>
#include<QDialog>

#include"deck.h"
#include"wordeditorscrolllist.h"
#include"wordeditorbuttonbar.h"

class AddLanguageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit
    AddLanguageDialog(QWidget *parent);

    QSize sizeHint() const override;
    const QString& getLanguage()            { return enteredLanguage; }

private:
    QGridLayout *mainLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit *langLineEdit;
    QString enteredLanguage;
};

class WordEditor : public QWidget
{
    Q_OBJECT
public:
    explicit WordEditor(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void setFlashcard(int index, const Flashcard& card);
    void InitWithDeck(const Deck& deck);
    QStringList getLanguages()              { return scrollList->getLanguages(); }
    void setLanguageEditMode(bool flag)     { bottomButtonBar->setLanguageEditMode(flag); }
signals:
    void addCardPressedWithCard(const Flashcard& card);
    void saveCardPressedWithCard(int index,
                                 const Flashcard& card);

    void cardLoaded();
    void changedLanguageEditMode(bool flag);

public slots:
    void PromptToAddLanguageToScrollList();

private:
    QVBoxLayout *mainLayout;

    WordEditorScrollList *scrollList;
    WordEditorButtonBar *bottomButtonBar;

    int loadedCardIndex;
};

#endif // WORDEDITOR_H
