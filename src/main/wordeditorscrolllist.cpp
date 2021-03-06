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

#include "wordeditorscrolllist.h"

WordEditorScrollList::WordEditorScrollList(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QFormLayout;
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::MinimumExpanding,
                  QSizePolicy::MinimumExpanding);
}

QSize
WordEditorScrollList::sizeHint() const {
    return QSize(200,200);
}

void
WordEditorScrollList::clear(){
    for(auto lineedit : valueLines){
        delete lineedit;
    }
    for(auto label : labelLines){
        delete label;
    }

    valueLines.clear();
    labelLines.clear();
}

void
WordEditorScrollList::clearValues(){
    for(QLineEdit* lineedit : valueLines){
        lineedit->setText("");
    }
}

void
WordEditorScrollList::addEditingLineForLanguage(const QString &language){
    QLabel *langLabel = new QLabel(language);
    QLineEdit *langValue = new QLineEdit;
    mainLayout->addRow(langLabel, langValue);
    valueLines.append(langValue);
    labelLines.append(langLabel);
}

void
WordEditorScrollList::loadFromCard(const Flashcard &card){
    for(int i = 0; i < card.size(); ++i){
        valueLines[i]->setText(card.at(i));
    }
}

Flashcard
WordEditorScrollList::toCard(){
    QStringList enteredWords;
    for(auto lineedit : valueLines){
        enteredWords.append(lineedit->text());
    }
    for(auto word : enteredWords){
        if(word == "")
           return Flashcard();
    }
    return Flashcard(enteredWords);
}

QStringList
WordEditorScrollList::getLanguages(){
    QStringList languages;

    if(labelLines.isEmpty())
        return languages;

    for(auto label : labelLines){
        languages.append(label->text());
    }
    return languages;
}

