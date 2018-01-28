#include "decksearcher.h"

DeckSearcher::DeckSearcher(QWidget *parent)
    : QWidget(parent)
{

    // Initialize members
    deckSearchBar = new DeckSearchBar;
    deckScrollList = new DeckScrollList;
    bottomButton = new QPushButton;

    // Add QScrollArea to deckScrollList
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(deckScrollList);
    scrollArea->setBackgroundRole(QPalette::Midlight);

    // Setup layout
    mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addWidget(deckSearchBar);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(bottomButton);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);


    // Connections
    connect(deckSearchBar, &DeckSearchBar::textChanged,
            deckScrollList, &DeckScrollList::changeTextToSearchFor);

    connect(this, &DeckSearcher::DeckTitleListChanged,
            deckScrollList, &DeckScrollList::setDeckTitleList);

    connect(bottomButton, &QPushButton::pressed,
            this, &DeckSearcher::bottomButtonPressed);

    connect(deckScrollList, &DeckScrollList::selectionChanged,
            this, &DeckSearcher::changeSelection);
}
