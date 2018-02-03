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

#ifndef DECKEDITORSAVEBAR_H
#define DECKEDITORSAVEBAR_H

/*
 * Contains:
 *      - DeckEditorSaveBar
 *      - DeckEditorSaveBarButton
 *
 * DeckEditor save bar is the bar replacing TabSelector, when the user
 * enters the Deck Editor tab.
 * Contains a save and a cancel button.
 * These send out the respective signals:
 *      - saveButtonPressed()
 *      - cancelButtonPressed()
 *
 * DeckEditorSaveBarButton inherits from QPushButton,
 * so it can override sizeHint and call setSizePolicy in the ctor.
*/

#include <QWidget>
#include<QHBoxLayout>
#include<QPushButton>

class DeckEditorSaveBarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit
    DeckEditorSaveBarButton(const QString& text,
                            QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class DeckEditorSaveBar : public QWidget
{
    Q_OBJECT
public:
    explicit DeckEditorSaveBar(QWidget *parent = nullptr);

signals:
    void saveButtonPressed();
    void cancelButtonPressed();

public slots:

private:
    QVBoxLayout *mainLayout;
    DeckEditorSaveBarButton *saveButton;
    DeckEditorSaveBarButton *cancelButton;
};

#endif // DECKEDITORSAVEBAR_H
