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

#include "tabselector.h"

TabSelector::TabSelector(QWidget *parent)
    : QWidget(parent)
{
    //Change to custom buttons later
    deckSelectionTabButton = new TabButton("New");
    deckEditorTabButton = new TabButton("Editor");
    statisticsTabButton = new TabButton("Stats");
    deckSelectionTabButton->setFocusPolicy(Qt::NoFocus);
    deckEditorTabButton->setFocusPolicy(Qt::NoFocus);
    statisticsTabButton->setFocusPolicy(Qt::NoFocus);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(5);
    mainLayout->addStretch(1);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(deckSelectionTabButton);
    mainLayout->addWidget(deckEditorTabButton);
    mainLayout->addWidget(statisticsTabButton);
    mainLayout->addStretch(1);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);

    setLayout(mainLayout);
    setPalette(pal);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    connect(deckSelectionTabButton, SIGNAL(pressed()),
            this, SIGNAL(DeckSelectionTabSelected()));
    connect(deckEditorTabButton, SIGNAL(pressed()),
            this, SIGNAL(DeckEditorTabSelected()));
    connect(statisticsTabButton, SIGNAL(pressed()),
            this, SIGNAL(StatisticsTabSelected()));
}
