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

LowerBox::LowerBox(const QList<QString> list, QWidget *parent)
    : QWidget(parent),
      restWordsList(list)
{
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
    initRestWordLabels();
}

void
LowerBox::RevealWords(){
    for(auto label: restWordsLabels){
        label->setVisible(true);
    }
}

void
LowerBox::createRestWordLabel(const QString &string){
    QLabel *newLabel = new QLabel(string);

    restWordsFont.setPointSize((restWordsFont.pointSize() + 20)/restWordsList.size());
    newLabel->setFont(restWordsFont);
    newLabel->setAlignment(Qt::AlignCenter);
    newLabel->setVisible(false);
    mainLayout->addWidget(newLabel);
    restWordsLabels.append(newLabel);
}

void
LowerBox::initRestWordLabels(){
    for(auto word : restWordsList){
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
    keyWordFont.setPointSize(keyWordFont.pointSize() + 20);
    keyWordLabel->setFont(keyWordFont);
    keyWordLabel->setAlignment(Qt::AlignCenter);

    //Setup Layout
    mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addWidget(keyWordLabel);
    mainLayout->addStretch(1);
    mainLayout->addWidget(lowerBox);
    mainLayout->addStretch(1);
    mainLayout->setAlignment(Qt::AlignCenter);

    //Setup this
    setLayout(mainLayout);
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);
    setMinimumSize(EXAM_MAINBOX_MIN_WIDTH, EXAM_MAINBOX_MIN_HEIGHT);
}

void
ExamMainBox::NextCard(unsigned int currCardIndex){
    restWordsList.clear();
    for(auto word : deck.data()->withoutKey(currCardIndex))
        restWordsList.append(word);
    resetLowerBox();

    keyWordString = deck.data()->key(currCardIndex);
    keyWordLabel->setText(keyWordString);

    emit changeToNextCard(currCardIndex);
    update();
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
    mainLayout->insertWidget(mainLayout->count()-1, lowerBox);
    connect(this, SIGNAL(toRevealCard()),
            lowerBox, SLOT(RevealWords()));
}

