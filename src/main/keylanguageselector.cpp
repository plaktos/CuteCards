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

#include "keylanguageselector.h"

KeyLanguageSelector::KeyLanguageSelector(QWidget *parent)
    : QWidget(parent),
      langLabelFont(QLabel().font())
{
    langLabelFont.setPointSize(langLabelFont.pointSize() + 4);

    mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addSpacing(1);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);

    setPalette(pal);
    setAutoFillBackground(true);
    setLayout(mainLayout);
}

void
KeyLanguageSelector::clear(){
    for(auto label : langLabels)
        delete label;
    for(auto rbutt : radioButtons)
        delete rbutt;

    langLabels.clear();
    radioButtons.clear();
}

void
KeyLanguageSelector::addLanguage(const QString &lang){
    QLabel *langLabel = new QLabel(lang);
    QRadioButton *langButton = new QRadioButton;

    langLabel->setFont(langLabelFont);

    langLabels.append(langLabel);
    radioButtons.append(langButton);
    mainLayout->addWidget(langLabel);
    mainLayout->addWidget(langButton);

    if(radioButtons.size() == 1)
        langButton->setChecked(true);
}

int
KeyLanguageSelector::getKeyLanguageIndex(){
    for(int i = 0; i < radioButtons.size(); ++i){
        if(radioButtons[i]->isChecked() == true)
            return i;
    }
    return 0;
}
