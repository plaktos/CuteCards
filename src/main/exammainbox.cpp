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

#include "exammainbox.h"

LowerBox::LowerBox(const QStringList& restwords,
                   QWidget *parent)
    : QWidget(parent)
{
    //Setup members
    restWordsFont.setPointSize(restWordsFont.pointSize() + 12);

    // Setup layout
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);

    // Setup this
    setLayout(mainLayout);

    // Initialize labels based on QStringList passed in constructor.
    initRestWordLabels(restwords);
}

void
LowerBox::RevealWords(){
    for(auto &label: restWordsLabels){
        label->setVisible(true);
    }
}

void
LowerBox::createRestWordLabel(const QString &string){
    QLabel *newLabel = new QLabel(string);

    newLabel->setFont(restWordsFont);
    newLabel->setAlignment(Qt::AlignCenter);
    newLabel->setVisible(false);

    mainLayout->addWidget(newLabel);
    restWordsLabels.append(newLabel);
}

void
LowerBox::initRestWordLabels(const QStringList& restwords){
    for(auto word : restwords){
        createRestWordLabel(word);
    }
}

ExamMainBox::ExamMainBox(QWidget *parent)
    : QWidget(parent),
      lowerBox(nullptr)
{
    //Setup keyWordLabel
    keyWordLabel = new QLabel("");
    QFont keyWordFont(keyWordLabel->font());
    keyWordFont.setPointSize(keyWordFont.pointSize() + 18);
    keyWordLabel->setFont(keyWordFont);
    keyWordLabel->setAlignment(Qt::AlignCenter);

    //Setup Layout
    mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addWidget(keyWordLabel);
    mainLayout->addStretch(1);
    mainLayout->addStretch(1);
    mainLayout->setAlignment(Qt::AlignCenter);

    //Setup this
    setLayout(mainLayout);
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);
    setMinimumSize(EXAM_MAINBOX_MIN_WIDTH, EXAM_MAINBOX_MIN_HEIGHT);
}

void
ExamMainBox::RevealCard(){
    emit toRevealCard();
    update();
}

void
ExamMainBox::resetLowerBox(){
    if(!(lowerBox == nullptr))
        delete lowerBox;
    lowerBox = new LowerBox(restWordsList);
    // Insert into layout at end - 1, (before the stretch)
    mainLayout->insertWidget(mainLayout->count()-1, lowerBox);
    connect(this, SIGNAL(toRevealCard()),
            lowerBox, SLOT(RevealWords()));
}

