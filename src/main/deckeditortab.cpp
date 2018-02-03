#include "deckeditortab.h"

DeckOptionsPanel::DeckOptionsPanel(QWidget *parent)
    : QFrame(parent)
{
    titleLineEdit = new QLineEdit;
    titleLineEdit->setPlaceholderText("Title...");

    importCSVButton = new QPushButton("Import CSV");
    exportCSVButton = new QPushButton("Export CSV");

    mainLayout = new QGridLayout;
    mainLayout->addWidget(titleLineEdit, 0,0, 1,2);
    mainLayout->addWidget(exportCSVButton, 1,0, 1,1);
    mainLayout->addWidget(importCSVButton, 1,1, 1,1);

    setLayout(mainLayout);

    connect(importCSVButton, &QPushButton::pressed,
            this, &DeckOptionsPanel::ImportCSVButtonPressed);
    connect(exportCSVButton, &QPushButton::pressed,
            this, &DeckOptionsPanel::ExportCSVButtonPressed);
}

DeckEditorTab::DeckEditorTab(QWidget *parent)
    : QWidget(parent)
{
    wordSearcher = new WordSearcher(this);
    wordEditor = new WordEditor;
    deckOptionsPanel = new DeckOptionsPanel;
    deckEditorSaveBar = new DeckEditorSaveBar;

    mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(5,10,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(wordEditor, 2,0,1,1);
    mainLayout->addWidget(deckOptionsPanel, 1,0,1,1);
    mainLayout->addWidget(wordSearcher, 0,1,4,1);
    mainLayout->addWidget(deckEditorSaveBar, 0,3,4,1);

    setLayout(mainLayout);

    connect(deckEditorSaveBar, &DeckEditorSaveBar::saveButtonPressed,
            this, &DeckEditorTab::saveDeck);
    connect(deckEditorSaveBar, &DeckEditorSaveBar::cancelButtonPressed,
            this, &DeckEditorTab::finishedDeckEditing);

    connect(wordEditor, &WordEditor::addCardPressedWithCard,
            this, &DeckEditorTab::addFlashcardToWorkingDeck);

    connect(wordEditor, &WordEditor::saveCardPressedWithCard,
            this, &DeckEditorTab::saveFlashcardToWorkingDeck);

    connect(wordSearcher, &WordSearcher::ToDeleteEntryAt,
            this, &DeckEditorTab::deleteFlashcardFromWorkingDeckAt);

    connect(wordSearcher, &WordSearcher::ToEditFlashcardAt,
            this, &DeckEditorTab::LoadFlashcardAtIntoWordEditor);

    connect(this, &DeckEditorTab::workingDeckChanged,
            wordSearcher, &WordSearcher::refreshListWithDeck);

    connect(deckOptionsPanel, &DeckOptionsPanel::ImportCSVButtonPressed,
            this, &DeckEditorTab::importDeckFromCSV);
    connect(deckOptionsPanel, &DeckOptionsPanel::ExportCSVButtonPressed,
            this, &DeckEditorTab::exportDeckToCSV);
}

void
DeckEditorTab::loadDeck(const Deck &deck){
    workingDeck = deck;
    wordEditor->InitWithDeck(workingDeck);
    emit workingDeckChanged(workingDeck);
}

void
DeckEditorTab::importDeckFromCSV(){
    QString filename = QFileDialog::getOpenFileName(this, "Open .CSV",
                                                    "./", "CSV(*.csv)");
    workingDeck = DeckLoader::fromCSVFile(filename);
    for(int i = 0; i < workingDeck.getNumOfLanguages(); ++i){
        wordEditor->PromptToAddLanguageToScrollList();
    }
    wordEditor->setLanguageEditMode(false);
    emit workingDeckChanged(workingDeck);
}

void
DeckEditorTab::exportDeckToCSV(){

}

void
DeckEditorTab::LoadFlashcardAtIntoWordEditor(int index){
    wordEditor->setFlashcard(index,workingDeck[index]);
}

void
DeckEditorTab::addFlashcardToWorkingDeck(const Flashcard &card){
    if(!card.empty()){
        workingDeck.addCard(card);
        emit workingDeckChanged(workingDeck);
    }
}

void
DeckEditorTab::saveFlashcardToWorkingDeck(const int &index, const Flashcard &card){
    if(!card.empty()){
            workingDeck[index] = card;
            emit workingDeckChanged(workingDeck);
    }
}


void
DeckEditorTab::deleteFlashcardFromWorkingDeckAt(const int &index)
{
    workingDeck.removeAt(index);
    emit workingDeckChanged(workingDeck);
}

void
DeckEditorTab::saveDeck(){
    if(!(deckOptionsPanel->getTitle() == "")){
        workingDeck.setTitle(deckOptionsPanel->getTitle());
        workingDeck.setLanguages(wordEditor->getLanguages());
        QString filename = QFileDialog::getSaveFileName(this, "Save as .deck",
                                                        "./res", "Decks (*.deck)");
        QFile deckfile(filename);
        if(!deckfile.open(QIODevice::WriteOnly)){
            qWarning("Couldn't open file for writing.");
            return;
        }

        QJsonDocument json(workingDeck.ToJsonObject());
        deckfile.write(json.toJson());
        deckfile.close();
        emit finishedDeckEditing();
    }
}
