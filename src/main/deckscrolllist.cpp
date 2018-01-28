#include "deckscrolllist.h"

DeckScrollList::DeckScrollList(QWidget *parent) : QWidget(parent)
{

    // Timer for searching, we only search 300ms after an input.
    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);

    // Layout setup
    mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setContentsMargins(0,0,0,0);
    //mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setSizePolicy(sizePolicy);

    // Connections
    connect(searchTimer, &QTimer::timeout,
            this, &DeckScrollList::doASearch);
}

void
DeckScrollList::HideAllTitleLabels(){
    for(auto entry : scrollListEntries){
        entry->setHidden(true);
    }
}

void
DeckScrollList::doASearch(){
    if(!(textToSearchFor == "Search...")){
        HideAllTitleLabels();

        for(int i = 0; i < deckTitleList.size(); ++i){
            if(deckTitleList[i].contains(textToSearchFor)){
                scrollListEntries[i]->setHidden(false);
            }
        }
    }
}

void
DeckScrollList::InitTitleLabels(){
    for(auto entry : scrollListEntries){
        delete entry;
    }
    scrollListEntries.clear();

    for(int i = 0; i < deckTitleList.size(); ++i){
        DeckScrollListEntry *newEntry = new DeckScrollListEntry(deckTitleList.at(i), i);
        scrollListEntries.append(newEntry);
        mainLayout->insertWidget(mainLayout->count()-1,scrollListEntries[i]);
        connect(newEntry, &DeckScrollListEntry::EditButtonPressed,
                this, &DeckScrollList::EditButtonPressedOnEntry);

        connect(newEntry, &DeckScrollListEntry::SelectedStateChanged,
                this, &DeckScrollList::SelectedStateChangedOnEntry);
    }
}
