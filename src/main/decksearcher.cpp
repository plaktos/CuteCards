#include "decksearcher.h"

DeckSearcher::DeckSearcher(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout;

    deckSearchBar = new DeckSearchBar;
    deckScrollList = new DeckScrollList;
    bottomButton = new QPushButton;

    mainLayout->addStretch(1);
    mainLayout->addWidget(deckSearchBar);
    mainLayout->addWidget(deckScrollList);
    mainLayout->addWidget(bottomButton);
    mainLayout->addStretch(1);

    setLayout(mainLayout);

    connect(deckSearchBar, &DeckSearchBar::textChanged,
            deckScrollList, &DeckScrollList::changeTextToSearchFor);

    connect(this, &DeckSearcher::DeckTitleListChanged,
            deckScrollList, &DeckScrollList::setDeckTitleList);

    connect(bottomButton, &QPushButton::pressed,
            this, &DeckSearcher::bottomButtonPressed);

    connect(deckScrollList, &DeckScrollList::selectionChanged,
            this, &DeckSearcher::changeSelection);
}
