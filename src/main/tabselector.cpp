#include "tabselector.h"

TabSelector::TabSelector(QWidget *parent)
    : QWidget(parent)
{
    //Change to custom buttons later
    deckSelectionTabButton = new QPushButton("New Exam");
    deckEditorTabButton = new QPushButton("Editor");
    statisticsTabButton = new QPushButton("Statistics");
    deckSelectionTabButton->resize(CENTRAL_TABSELECTOR_BUTTONS_HINT_WIDTH, deckSelectionTabButton->height());
    deckEditorTabButton->resize(CENTRAL_TABSELECTOR_BUTTONS_HINT_WIDTH, deckEditorTabButton->height());
    statisticsTabButton->resize(CENTRAL_TABSELECTOR_BUTTONS_HINT_WIDTH, statisticsTabButton->height());

    mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(deckSelectionTabButton);
    mainLayout->addWidget(deckEditorTabButton);
    mainLayout->addWidget(statisticsTabButton);
    mainLayout->setSpacing(25);

    setBackgroundRole(QPalette::Shadow);

    setLayout(mainLayout);

    connect(deckSelectionTabButton, SIGNAL(pressed()),
            this, SIGNAL(DeckSelectionTabSelected()));
    connect(deckEditorTabButton, SIGNAL(pressed()),
            this, SIGNAL(DeckEditorTabSelected()));
    connect(statisticsTabButton, SIGNAL(pressed()),
            this, SIGNAL(StatisticsTabSelected()));
}
