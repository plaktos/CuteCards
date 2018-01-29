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

#include "deckscrolllist.h"

DeckScrollList::DeckScrollList(QWidget *parent)
    : QWidget(parent),
      languageLockMode(false)
{

    // Layout setup
    mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::MinimumExpanding,
                  QSizePolicy::MinimumExpanding);
}

void
DeckScrollList::setHiddenForAllTitleLabels(bool flag){
    for(auto entry : scrollListEntries){
        entry->setHidden(flag);
    }
}

void
DeckScrollList::doATitleSearch(const QString& text){
    selectedEntries.clear();
    if(text == "Title..."){
        setHiddenForAllTitleLabels(false);
    }else{
        setHiddenForAllTitleLabels(true);
        for(auto entry : scrollListEntries){
            if(entry->getTitle().contains(text)){
                entry->setHidden(false);
            }
        }
    }
}

void
DeckScrollList::doALanguageSearch(const QString& text){
    selectedEntries.clear();
    if(text == "Language..."){
        setHiddenForAllTitleLabels(false);
    }else{
        setHiddenForAllTitleLabels(true);
        for(auto entry : scrollListEntries){
            for(auto language : entry->getLanguages()){
                if(language.contains(text)){
                    entry->setHidden(false);
                }
            }
        }
    }
}

void
DeckScrollList::clearEntries(){
    for(auto entry : scrollListEntries){
        delete entry;
    }
    scrollListEntries.clear();
}

void
DeckScrollList::lockLanguages(const QStringList &list){
    languageLockMode = true;
    setHiddenForAllTitleLabels(true);
    for(auto entry : scrollListEntries){
        if(entry->getLanguages() == list){
            entry->setHidden(false);
        }
    }
    emit languageLockModeChanged(true);
}

void
DeckScrollList::unlockLanguages(){
    languageLockMode = false;
    setHiddenForAllTitleLabels(false);
    emit languageLockModeChanged(false);
}

void
DeckScrollList::SelectedStateChangedOnEntry(const int &index, const Qt::CheckState &state){
    if(state == Qt::Unchecked){
        selectedEntries.remove(index);
    } else{
        selectedEntries[index] = state;
    }

    if(!languageLockMode){
        lockLanguages(scrollListEntries[index]->getLanguages());
    }
    else if(selectedEntries.size() == 0){
        unlockLanguages();
    }
}

void
DeckScrollList::addEntry(const Deck *d){
    DeckScrollListEntry *newEntry = new DeckScrollListEntry(scrollListEntries.size(),
                                                            d->getTitle(),
                                                            d->getLanguages());
    scrollListEntries.append(newEntry);
    mainLayout->insertWidget(mainLayout->count()-1,newEntry);
    connect(newEntry, &DeckScrollListEntry::EditButtonPressed,
            this, &DeckScrollList::EditButtonPressedOnEntry);
    connect(newEntry, &DeckScrollListEntry::SelectedStateChanged,
            this, &DeckScrollList::SelectedStateChangedOnEntry);
}
