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

#include "deckscrolllistentry.h"

DeckScrollListEntry::DeckScrollListEntry(const QString &title, int index, QWidget *parent)
    : QWidget(parent),
      id(index)
{
    // Setup members
    selectedCheckBox = new QCheckBox;
    titleLabel = new QLabel(title);
    editButton = new QPushButton("E");
    editButton->setMaximumSize(20,15);

    // Setup Layout
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(selectedCheckBox);
    mainLayout->addStretch(10);
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch(30);
    mainLayout->addWidget(editButton);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    setSizePolicy(sizePolicy);

    // Connections
    connect(editButton, &QPushButton::pressed,
            this, &DeckScrollListEntry::SendSignalEditButtonPressed);

    connect(selectedCheckBox, &QCheckBox::stateChanged,
            this, &DeckScrollListEntry::SendSignalSelectedStateChanged);
}

void
DeckScrollListEntry::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        selectedCheckBox->setChecked(!selectedCheckBox->isChecked());
    }
    else{
        QWidget::mousePressEvent(e);
    }
}
