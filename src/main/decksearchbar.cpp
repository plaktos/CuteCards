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

#include "decksearchbar.h"

DeckSearchBarPart::DeckSearchBarPart(const QString& deftext,
                                           QWidget *parent)
    : QLineEdit(parent)
{
    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);

    setPlaceholderText(deftext);

    connect(searchTimer, &QTimer::timeout,
            [this] () {
        emit needSearchFor(text());
    });

    connect(this, &DeckSearchBarPart::textChanged,
            [this] () {
        searchTimer->start(50);
    });
}

void
DeckSearchBarPart::mousePressEvent(QMouseEvent *e){
    if(!hasFocus()){
        setText("");
    }
}


DeckSearchBar::DeckSearchBar(QWidget *parent)
    : QWidget(parent),
      locked(false)
{
    titleSearcher = new DeckSearchBarPart("Title...");
    languageSearcher = new DeckSearchBarPart("Language...");
    titleSearcher->setAutoFillBackground(true);
    languageSearcher->setAutoFillBackground(true);

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(titleSearcher);
    mainLayout->addWidget(languageSearcher);
    mainLayout->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);
    setMaximumHeight(50);

    connect(titleSearcher, &DeckSearchBarPart::needSearchFor,
            this, &DeckSearchBar::NeedTitleSearchFor);
    connect(languageSearcher, &DeckSearchBarPart::needSearchFor,
            this, &DeckSearchBar::NeedLanguageSearchFor);
}

void
DeckSearchBar::paintEvent(QPaintEvent *e){
    QPalette pal(titleSearcher->palette());
    if(locked){
        pal.setColor(QPalette::Base, Qt::gray);
        languageSearcher->setPalette(pal);
    }
    else{
        pal.setColor(QPalette::Base, Qt::white);
        languageSearcher->setPalette(pal);

    }
    QWidget::paintEvent(e);
}

