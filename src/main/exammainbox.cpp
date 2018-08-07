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

ExamLowerBox::ExamLowerBox(const QStringList& restwords,
                           QWidget *parent)
    : QWidget(parent)
{

    // Setup layout
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);

    // Initialize labels based on QStringList passed in constructor.
    initRestWordLabels(restwords);
}

void
ExamLowerBox::RevealWords(){
    for(auto &label: restWordsLabels){
        label->setHidden(false);
    }
}

void
ExamLowerBox::createRestWordLabel(const QString &string){
    QLabel *newLabel = new QLabel(string);

    newLabel->setAlignment(Qt::AlignCenter);
    newLabel->setMaximumHeight(100);
    newLabel->setMinimumHeight(100);
    newLabel->setHidden(true);

    QFont font(newLabel->font());
    int minSize = 8;
    font.setPointSize(minSize + (width()/(string.count()+1)/6));
    newLabel->setFont(font);

    mainLayout->insertWidget(mainLayout->count()-1,newLabel);
    restWordsLabels.append(newLabel);
}

void
ExamLowerBox::initRestWordLabels(const QStringList& restwords){
    for(auto word : restwords){
        createRestWordLabel(word);
    }
}

ExamMainBox::ExamMainBox(QWidget *parent)
    : QFrame(parent),
      lowerBox(nullptr)
{
    //Setup keyWordLabel
    keyWordLabel = new QLabel;
    keyWordLabel->setAlignment(Qt::AlignCenter);
    keyWordLabel->setMaximumHeight(height()/2);
    keyWordLabel->setMinimumHeight(height()/2);

    //Setup Layout
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(keyWordLabel);
    mainLayout->addStretch(1);
    mainLayout->setAlignment(Qt::AlignCenter);

    //Setup this
    setLayout(mainLayout);
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);
    setMaximumSize(sizeHint());
    setFrameShape(QFrame::Box);
    setLineWidth(5);
}

void
ExamMainBox::RevealCard(){
    emit toRevealCard();
    update();
}

void
ExamMainBox::resetLowerBox(){
    lowerBox.reset(new ExamLowerBox(restWordsList));
    lowerBox->setMaximumHeight(height()/2);

    mainLayout->insertWidget(mainLayout->count()-1 ,lowerBox.get());
    connect(this, SIGNAL(toRevealCard()),
            lowerBox.get(), SLOT(RevealWords()));
}

void
ExamMainBox::setKeyWord(const QString &key){
    keyWordString = key;
    keyWordLabel->setText(key);
    QFont font;
    int minSize = 8;
    font.setPointSize(minSize + (width()/(key.count()+1)/2));
    keyWordLabel->setFont(font);
}

