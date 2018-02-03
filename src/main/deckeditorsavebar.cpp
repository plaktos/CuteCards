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

#include "deckeditorsavebar.h"

DeckEditorSaveBarButton::DeckEditorSaveBarButton(const QString& text,
                                                 QWidget *parent)
    : QPushButton(text, parent)
{
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize
DeckEditorSaveBarButton::sizeHint() const {
    return QSize(50,50);
}

DeckEditorSaveBar::DeckEditorSaveBar(QWidget *parent)
    : QWidget(parent)
{
    saveButton = new DeckEditorSaveBarButton("\342\234\224");
    cancelButton = new DeckEditorSaveBarButton("\342\234\225");

    mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);
    mainLayout->addStretch(1);

    setLayout(mainLayout);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);
    setPalette(pal);
    setAutoFillBackground(true);

    connect(saveButton, &DeckEditorSaveBarButton::pressed,
            this, &DeckEditorSaveBar::saveButtonPressed);
    connect(cancelButton, &DeckEditorSaveBarButton::pressed,
            this, &DeckEditorSaveBar::cancelButtonPressed);
}
