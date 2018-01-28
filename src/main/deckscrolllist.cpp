#include "deckscrolllist.h"

DeckScrollList::DeckScrollList(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;

    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);

    setLayout(mainLayout);

    connect(searchTimer, &QTimer::timeout,
            this, &DeckScrollList::doASearch);
}

void
DeckScrollList::HideAllTitleLabels(){
    for(int i = 0; i < deckTitleLabels.size(); ++i){
        deckTitleLabels.at(i)->setHidden(true);
    }
}

void
DeckScrollList::doASearch(){
    HideAllTitleLabels();

    QString regex = QString("\b") + QString(textToSearchFor);

    for(int i = 0; i < deckTitleList.size(); ++i){
        if(deckTitleList[i].contains(regex)){
            deckTitleLabels[i]->setHidden(false);
        }
    }
}

void
DeckScrollList::InitTitleLabels(){
    for(auto label : deckTitleLabels){
        delete label;
    }
    deckTitleLabels.clear();

    for(int i = 0; i < deckTitleList.size(); ++i){
        deckTitleLabels.append(new QLabel(deckTitleList.at(i)));
        mainLayout->addWidget(deckTitleLabels[i]);
    }
}
