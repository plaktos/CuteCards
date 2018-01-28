#include "deckscrolllist.h"

DeckScrollList::DeckScrollList(QWidget *parent) : QWidget(parent)
{

    // Timer for searching, we only search 300ms after an input.
    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);

    // Layout setup
    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);

    // Connections
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
        QLabel *titleLabel = new QLabel(deckTitleList.at(i));
        titleLabel->setBackgroundRole(QPalette::Light);
        deckTitleLabels.append(titleLabel);
        mainLayout->insertWidget(mainLayout->count()-1,deckTitleLabels[i]);
    }
}
