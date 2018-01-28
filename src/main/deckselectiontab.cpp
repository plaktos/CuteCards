#include "deckselectiontab.h"

DeckSelectionTab::DeckSelectionTab(QWidget* parent)
    : Tab(parent)
{
    mainLayout = new QHBoxLayout;

    availableDecksSearcher = new DeckSearcher;
    availableDecksSearcher->setBottomButtonText("Edit");

    examDecksSearcher = new DeckSearcher;
    examDecksSearcher->setBottomButtonText("Start");

    mainLayout->addWidget(availableDecksSearcher);
    mainLayout->addStretch(50);
    mainLayout->addWidget(examDecksSearcher);

    setLayout(mainLayout);

    connect(this, &DeckSelectionTab::AvailableDeckTitlesChanged,
            availableDecksSearcher, &DeckSearcher::setDeckTitleList);

    connect(availableDecksSearcher, &DeckSearcher::SelectionChanged,
            this, &DeckSelectionTab::setAvailableDecksSelectedIndexes);

    connect(examDecksSearcher, &DeckSearcher::SelectionChanged,
            this, &DeckSelectionTab::setExamDecksSelectedIndexes);

    connect(examDecksSearcher, &DeckSearcher::bottomButtonPressed,
            this, &DeckSelectionTab::StartExam);

}

void
DeckSelectionTab::LoadAvailableDecks(){
    QDir resDir("res");
    QStringList entries = resDir.entryList(QStringList{"*.deck"});
    for(auto name : entries){
        availableDecks.append(DeckLoader::fromDeckFile(name));
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
