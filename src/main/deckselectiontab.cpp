#include "deckselectiontab.h"

DeckSelectionTab::DeckSelectionTab(QWidget* parent)
    : Tab(parent)
{
    // Setup member widgets
    availableDecksSearcher = new DeckSearcher;
    availableDecksSearcher->setBottomButtonText("Start");
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

    //connect(examDecksSearcher, &DeckSearcher::SelectionChanged,
    //        this, &DeckSelectionTab::setExamDecksSelectedIndexes);

    //connect(examDecksSearcher, &DeckSearcher::bottomButtonPressed,
    //        this, &DeckSelectionTab::StartExam);

    connect(availableDecksSearcher, &DeckSearcher::EditButtonPressedOnEntry,
            this, &DeckSelectionTab::SignalToEditAvailableDeckAt);

    connect(availableDecksSearcher, &DeckSearcher::SelectedStateChangedOnEntry,
            this, &DeckSelectionTab::changeSelectedAvailableDecksList);

    // Temporary
    connect(availableDecksSearcher, &DeckSearcher::bottomButtonPressed,
            this, &DeckSelectionTab::StartExam);

}

void
DeckSelectionTab::LoadAvailableDecks(){
    availableDecks.clear();
    availableDecksSelectionIndexes.clear();

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

    for(int i = 0; i < availableDecks.size(); ++i)
        availableDecksSelectionIndexes.push_back(Qt::Unchecked);

    emit AvailableDeckTitlesChanged(deckTitlesList);
}

void
DeckSelectionTab::StartExam(){
    currExamDeck = QSharedPointer<Deck>(new Deck);
    for(int i = 0; i < availableDecksSelectionIndexes.size(); ++i){
        if(availableDecksSelectionIndexes[i] == Qt::Checked)
            currExamDeck.data()->mergeDeck(availableDecks[i]);
    }
    emit ExamToStartWithDeck(currExamDeck.toWeakRef());
}

void
DeckSelectionTab::SignalToEditAvailableDeckAt(const int &index){
    emit ToEditDeck(availableDecks[index]);
}

void
DeckSelectionTab::changeSelectedAvailableDecksList(const int &index, Qt::CheckState state){
    availableDecksSelectionIndexes[index] = state;
}
