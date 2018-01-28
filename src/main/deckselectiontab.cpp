#include "deckselectiontab.h"

DeckSelectionTab::DeckSelectionTab(QWidget* parent)
    : Tab(parent)
{
    // Setup member widgets
    availableDecksSearcher = new DeckSearcher;
    availableDecksSearcher->setBottomButtonText("Edit");
    //examDecksSearcher = new DeckSearcher;
    //examDecksSearcher->setBottomButtonText("Start");

    // Setup layout
    mainLayout = new QHBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addWidget(availableDecksSearcher);
    mainLayout->addStretch(25);
    //mainLayout->addWidget(examDecksSearcher);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);

    // Connections
    connect(this, &DeckSelectionTab::AvailableDeckTitlesChanged,
            availableDecksSearcher, &DeckSearcher::setDeckTitleList);

    connect(availableDecksSearcher, &DeckSearcher::SelectionChanged,
            this, &DeckSelectionTab::setAvailableDecksSelectedIndexes);

    //connect(examDecksSearcher, &DeckSearcher::SelectionChanged,
    //        this, &DeckSelectionTab::setExamDecksSelectedIndexes);

    //connect(examDecksSearcher, &DeckSearcher::bottomButtonPressed,
    //        this, &DeckSelectionTab::StartExam);

}

void
DeckSelectionTab::LoadAvailableDecks(){
    availableDecks.clear();

    QDir resDir("./res");
    QStringList entries = resDir.entryList(QStringList{"*.deck"});
    for(int i = 0; i < entries.size(); ++i){
        QString path = QString("res/") + entries[i];
        Deck deck = DeckLoader::fromDeckFile(path);
        if(!deck.empty()){
            availableDecks.append(deck);
        }
    }

    QStringList deckTitlesList;
    for(auto &deck : availableDecks){
        deckTitlesList.append(deck.getTitle());
    }
    emit AvailableDeckTitlesChanged(deckTitlesList);
}

void
DeckSelectionTab::StartExam(){
    currExamDeck = QSharedPointer<Deck>(new Deck);
    for(int i = 0; i < examDecksSelectionIndexes.size(); ++i){
        currExamDeck.data()->mergeDeck(examDecks[examDecksSelectionIndexes[i]]);
    }
    emit ExamToStartWithDeck(currExamDeck.toWeakRef());
}
