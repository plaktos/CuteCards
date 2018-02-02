#include "deckeditortab.h"

DeckEditorTab::DeckEditorTab(QWidget *parent)
    : QWidget(parent)
{
    wordSearcher = new WordSearcher(this);
    wordEditor = new WordEditor;
    deckEditorSaveBar = new DeckEditorSaveBar;
    deckTitleEditor = new QLineEdit;
    deckTitleEditor->setMaximumWidth(250);

    mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(wordEditor, 0,0,1,1);
    mainLayout->addWidget(deckTitleEditor, 1,0,1,1);
    mainLayout->addWidget(wordSearcher, 0,1,3,1);
    mainLayout->addWidget(deckEditorSaveBar, 0,3,3,1);

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
}

void
DeckEditorTab::loadDeck(const Deck &deck){
    workingDeck = deck;
    deckTitleEditor->setPlaceholderText(deck.getTitle());
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
    if(!(deckTitleEditor->text() == "")){
        workingDeck.setTitle(deckTitleEditor->text());
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
