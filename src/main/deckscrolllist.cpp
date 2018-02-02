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
      languageLockMode(false), selectionActive(false),
      emptyTitleSearch(true)
{

    // Layout setup
    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
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
DeckScrollList::setHiddenForEntryAt(int index, bool flag){
    scrollListEntries[index]->setHidden(flag);
}

void
DeckScrollList::setHiddenForAllEntry(bool flag){
    for(auto &entry : scrollListEntries){
        entry->setHidden(flag);
    }
}

void
DeckScrollList::doATitleSearch(const QString& text){
    if(!(text == "")){
        emptyTitleSearch = false;
        // If language lock mode is active we only search in the
        // ones that are already shown, and we set the ones,
        // that dont match the title to not be shown
        if(languageLockMode){
            for(int i = 0; i < scrollListEntries.size(); ++i){
                if(searchedEntries[i] == true){
                    if(!(scrollListEntries[i]->getTitle().contains(text, Qt::CaseInsensitive)))
                        searchedEntries[i] = false;
                }
            }
        }
        // If language lock mode is off we search in all of the entries
        else{
            for(int i = 0; i < scrollListEntries.size(); ++i){
                if(scrollListEntries[i]->getTitle().contains(text, Qt::CaseInsensitive))
                    searchedEntries[i] = true;
                else
                    searchedEntries[i] = false;
            }
        }
    }
    else{
        emptyTitleSearch = true;
        for(int i = 0; i < scrollListEntries.size(); ++i){
            searchedEntries[i] = true;
        }
    }
    refreshEntries();
}

void
DeckScrollList::doALanguageSearch(const QString& text){
    if(!(text == "")){
        for(int i = 0; i < scrollListEntries.size(); ++i){
            for(QString &lang : scrollListEntries[i]->getLanguages()){
                if(lang.contains(text, Qt::CaseInsensitive))
                    searchedEntries[i] = true;
                else
                    searchedEntries[i] = false;
            }
        }
    }
    else{
        for(auto entry : scrollListEntries)
            entry->setHidden(false);
    }
    refreshEntries();
}

void
DeckScrollList::setSelectedForEntryAt(int index, bool flag){
    selectedEntries[index] = flag;

    QMap<int, bool>::const_iterator begin = selectedEntries.constBegin();
    QMap<int, bool>::const_iterator end = selectedEntries.constEnd();

    selectionActive = false;
    while(begin != end){
        if(begin.value() == true){
            selectionActive = true;
            if(!languageLockMode){
                lockLanguages(scrollListEntries[index]->getLanguages());
                emit languagesLockedFromDeckAt(index);
            }
            break;
        }
        ++begin;
    }
    if(!selectionActive){
        unlockLanguages();
        emit languageLockModeCleared();
    }
    refreshEntries();
}

void
DeckScrollList::refreshEntries(){
    setHiddenForAllEntry(true);

    // If there are selections we have to check if the flag for the entry's index
    // is set to true in both searchedEntries and selectedEntries
    if(selectionActive){
        for(int i = 0; i < scrollListEntries.size(); ++i){
            // if selected entries contains the index and it is true
            //(the second argument is the default value in case index is not in selectedEntries.
            if(selectedEntries.value(i, false) ||
               (!emptyTitleSearch && searchedEntries[i] == true && languageMatchedEntries.value(i,false))||
               (emptyTitleSearch && languageMatchedEntries.value(i, false)))
                    scrollListEntries[i]->setHidden(false);
        }
    }
    // if there are no selections we just check if the flag for the
    // corresponding index in searchedEntries is set to true
    //
    else{
        for(int i = 0; i < scrollListEntries.size(); ++i){
            if(searchedEntries[i] == true){
                scrollListEntries[i]->setHidden(false);
            }
        }
    }
    resize(sizeHint());
}

QVector<int>
DeckScrollList::getSelectedEntries(){
    QVector<int> indexes;
    QMap<int, bool>::const_iterator begin = selectedEntries.constBegin();
    QMap<int, bool>::const_iterator end = selectedEntries.constEnd();
    while(begin != end){
        indexes.push_back(begin.key());
        ++begin;
    }
    return indexes;
}

void
DeckScrollList::clearEntries(){
    for(auto entry : scrollListEntries){
        delete entry;
    }
    scrollListEntries.clear();
    selectedEntries.clear();
    searchedEntries.clear();
    languageMatchedEntries.clear();
    selectionActive = false;
    unlockLanguages();
}

void
DeckScrollList::lockLanguages(const QStringList &list){
    languageLockMode = true;
    for(int i = 0; i < scrollListEntries.size(); ++i){
        if(scrollListEntries[i]->getLanguages() == list)
            languageMatchedEntries[i] = true;
        else
            languageMatchedEntries[i] = false;
    }
    emit languageLockModeChanged(true);
}

void
DeckScrollList::unlockLanguages(){
    languageLockMode = false;
    languageMatchedEntries.clear();
    emit languageLockModeChanged(false);
}

void
DeckScrollList::addEntry(const Deck *d){
    DeckScrollListEntry *newEntry = new DeckScrollListEntry(scrollListEntries.size(),
                                                            d->getTitle(),
                                                            d->getLanguages());
    searchedEntries[scrollListEntries.size()] = true;
    scrollListEntries.append(newEntry);
    mainLayout->insertWidget(mainLayout->count()-1,newEntry);
    connect(newEntry, &DeckScrollListEntry::EditButtonPressed,
            this, &DeckScrollList::EditButtonPressedOnEntry);
    connect(newEntry, &DeckScrollListEntry::SelectedStateChanged,
            this, &DeckScrollList::setSelectedForEntryAt);
}
