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

#ifndef WORDEDITORBUTTONBAR_H
#define WORDEDITORBUTTONBAR_H

/*
 * Contains:
 *      - WordEditorButtonBarButton
 *      - WordEditorButtonBar
 *
 * WordEditorButtonBarButton is a customization of QPushButton
 * for overriding sizeHint
 *
 * WordEditorButtonBar provides a set of buttons with which
 * the user can alter the words in WordEditorScrollList,
 * the signals are handled in a WordEditor object.
*/
#include <QWidget>
#include<QHBoxLayout>
#include<QPushButton>

class WordEditorButtonBarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit
    WordEditorButtonBarButton(const QString& text,
                              QWidget *parent = nullptr);

    QSize sizeHint() const override;

};

class WordEditorButtonBar : public QWidget
{
    Q_OBJECT
public:
    explicit
    WordEditorButtonBar(QWidget* parent = nullptr);

signals:
    void NewCardButtonPressed();
    void SaveButtonPressed();
    void AddButtonPressed();
    void AddLanguageButtonPressed();
    void FinishedLanguageAddingButtonPressed();

public slots:
    // Change to save mode
    void changeToSaveButton()                   { alternatingButton->setText("Save");
                                                  saveMode = true; }

    // Change between LanguageEditMode and WordEditMode
    void setLanguageEditMode(bool flag);

private:
    QHBoxLayout *mainLayout;
    WordEditorButtonBarButton *newCardButton;
    WordEditorButtonBarButton *alternatingButton;
    WordEditorButtonBarButton *addLanguageButton;
    WordEditorButtonBarButton *finishedLanguageAddingButton;

    // The button bar is in save mode if the user is editing an
    // existing word in the deck.
    // if the user clicks the New button, saveMode is turned off,
    // and the user can add a new word to the deck
    bool saveMode;

    // If an empty deck is loaded then the user must first specify the languages
    // for the deck
    // this is what language edit mode represents.
    bool languageEditMode;
};

#endif // WORDEDITORBUTTONBAR_H
