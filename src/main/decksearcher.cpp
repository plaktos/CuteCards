#include "decksearcher.h"

DeckSearcher::DeckSearcher(QWidget *parent)
    : QWidget(parent)
{

    // Initialize members
    deckSearchBar = new DeckSearchBar;
    deckScrollList = new DeckScrollList;
    bottomButton = new QPushButton;

    // Add QScrollArea to deckScrollList
    DeckScrollArea *scrollArea = new DeckScrollArea;
    scrollArea->setWidget(deckScrollList);
    scrollArea->setBackgroundRole(QPalette::Midlight);
    scrollArea->setSizePolicy(deckScrollList->sizePolicy());

    // Setup layout
    mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
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

    connect(deckScrollList, &DeckScrollList::EditButtonPressedOnEntry,
            this, &DeckSearcher::EditButtonPressedOnEntry);
}
