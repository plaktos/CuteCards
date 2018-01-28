#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{

    // Create the tabs
    tabSelector = new TabSelector;
    examTab = new ExamTab;
    deckSelectionTab = new DeckSelectionTab;
    //deckEditorTab = new DeckEditorTab;
    //statisticsTab = new StatisticsTab;

    // Hide all tabs initially
    deckSelectionTab->setHidden(true);
    examTab->setHidden(true);
    //deckEditorTab->setHidden(true);
    //statisticsTab->setHidden(true);

    // Initialize the Layout and add the widgets
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabSelector);
    mainLayout->addWidget(examTab);
    mainLayout->addWidget(deckSelectionTab);
    //mainLayout->addWidget(deckEditorTab);
    //mainLayout->addWidget(statisticsTab);

    // Setup this
    setLayout(mainLayout);


    //Connections with tabSelector
    connect(tabSelector, SIGNAL(DeckSelectionTabSelected()),
            this, SLOT(changeToDeckSelectionTab()));
    connect(tabSelector, SIGNAL(DeckEditorTabSelected()),
            this, SLOT(changeToDeckEditorTab()));
    connect(tabSelector, SIGNAL(StatisticsTabSelected()),
            this, SLOT(changeToStatisticsTab()));

    //Connections between tabs
    connect(deckSelectionTab, &DeckSelectionTab::ExamToStartWithDeck,
            this, &CentralWidget::StartExamWithDeck);

    //connect(deckSelectionTab, &DeckSelectionTab::ToEditDeck,
    //        deckEditorTab, &DeckEditor::EditDeck);

    //Start off with Deck Selection.
    //Change later to a welcome tab
    changeToDeckSelectionTab();
}

void
CentralWidget::HideAllTabs(){
    examTab->setHidden(true);
    deckSelectionTab->setHidden(true);
    //deckEditorTab->setHidden(true);
    //statisticsTab->setHidden(true);
}

void
CentralWidget::changeToDeckSelectionTab(){

    //If exam is running, abort it

    if(deckSelectionTab->isHidden()){
        HideAllTabs();
        deckSelectionTab->setHidden(false);
        //Upon changing to Deck selection we load the available decks.
        // Change later to a button to reload.
        deckSelectionTab->LoadAvailableDecks();
    }
}

void
CentralWidget::StartExamWithDeck(const QWeakPointer<Deck> &d){

    //If exam is running, abort it
    HideAllTabs();
    examTab->setHidden(false);
    examTab->StartExamWithDeck(d);
}

void
CentralWidget::changeToDeckEditorTab(){

    //If exam is running, abort it
    /*
    if(deckEditorTab->isHidden()){
        HideAllTabs();
        deckEditorTab->setHidden(false);
    }
    */
}

void
CentralWidget::changeToStatisticsTab(){

    //If exam is running, abort it
    /*
    if(statisticsTab->isHidden()){
        HideAllTabs();
        statisticsTab->setHidden(false)
    }
    */
}
