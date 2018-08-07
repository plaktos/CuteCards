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

#include "wordscrolllist.h"

WordScrollList::WordScrollList(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addSpacing(1);

    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);
}

WordScrollList::~WordScrollList(){
    clear();
}

void
WordScrollList::clear(){
    entries.clear();
}

void
WordScrollList::searchFor(const QString &text){
    if(text == ""){
        for(auto &entry : entries){
            entry->setHidden(false);
        }
    }
    else{
        for(auto &entry : entries){
            for(auto word : entry->getWords()){
                if(word.contains(text))
                    entry->setHidden(false);
                else
                    entry->setHidden(true);
            }
        }
    }
}

void
WordScrollList::addEntry(const Flashcard &card){
    std::unique_ptr<WordScrollListEntry> entry= std::make_unique<WordScrollListEntry>(entries.size());
    for(int i = 0; i < card.size(); ++i){
        entry->addWord(card.at(i));
    }
    mainLayout->insertWidget(mainLayout->count()-1, entry.get());
    connect(entry.get(), &WordScrollListEntry::selected,
            this, &WordScrollList::EntrySelectedAt);
    connect(entry.get(), &WordScrollListEntry::DeleteButtonPressed,
            this, &WordScrollList::DeleteButtonPressedForEntryAt);
    entries.push_back(std::move(entry));
}
