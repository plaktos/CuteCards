#include "deckeditortab.h"

DeckEditorTab::DeckEditorTab(QWidget *parent)
    : QWidget(parent)
{
    wordSearcher = new WordSearcher(this);
    wordEditor = new WordEditor;
    deckEditorSaveBar = new DeckEditorSaveBar;

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(wordEditor, 0, Qt::AlignTop);
    mainLayout->addWidget(wordSearcher);
    mainLayout->addWidget(deckEditorSaveBar);

    setLayout(mainLayout);

    connect(deckEditorSaveBar, &DeckEditorSaveBar::saveButtonPressed,
            this, &DeckEditorTab::saveDeck);
    connect(deckEditorSaveBar, &DeckEditorSaveBar::cancelButtonPressed,
            this, &DeckEditorTab::cancelDeckEditing);

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
}

void
DeckEditorTab::loadDeck(const Deck &deck){
    workingDeck = deck;
    wordEditor->InitWithDeck(workingDeck);
    emit workingDeckChanged(workingDeck);
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
}
