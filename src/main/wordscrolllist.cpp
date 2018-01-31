#include "wordscrolllist.h"

WordScrollList::WordScrollList(QWidget *parent)
    : QWidget(parent),
      locked(false)
{
    mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addSpacing(1);

    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);
}

void
WordScrollList::clear(){
    for(auto &entry : entries){
        delete entry;
    }

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
    WordScrollListEntry *entry = new WordScrollListEntry(entries.size());
    for(int i = 0; i < card.size(); ++i){
        entry->addWord(card.at(i));
    }
    entries.append(entry);
    mainLayout->insertWidget(mainLayout->count()-1, entry);
    connect(entry, &WordScrollListEntry::selected,
            this, &WordScrollList::EntrySelectedAt);
    connect(entry, &WordScrollListEntry::DeleteButtonPressed,
            this, &WordScrollList::DeleteButtonPressedForEntryAt);
}

void
WordScrollList::mousePressEvent(QMouseEvent *e){
    if(!locked)
        QWidget::mousePressEvent(e);
}
