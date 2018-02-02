#ifndef DECKEDITORTAB_H
#define DECKEDITORTAB_H

#include <QWidget>
#include<QList>
#include<QFileDialog>
#include<QJsonDocument>
#include<QGridLayout>
#include<QLineEdit>

#include "deck.h"
#include "wordsearcher.h"
#include "wordeditor.h"
#include "deckeditorsavebar.h"

class DeckEditorTab : public QWidget
{
    Q_OBJECT
public:
    explicit DeckEditorTab(QWidget *parent = nullptr);

    void loadDeck(const Deck& deck);
signals:
    void finishedDeckEditing();
    void workingDeckChanged(const Deck& newdeck);

public slots:
    void saveDeck();
    void LoadFlashcardAtIntoWordEditor(int index);
    void addFlashcardToWorkingDeck(const Flashcard& card);
    void saveFlashcardToWorkingDeck(const int &index,
                               const Flashcard& card);
    void deleteFlashcardFromWorkingDeckAt(const int &index);

private:
    void InitWordEditorLanguageList();

    QGridLayout *mainLayout;

    QLineEdit *deckTitleEditor;
    WordSearcher *wordSearcher;
    WordEditor *wordEditor;
    DeckEditorSaveBar *deckEditorSaveBar;
    Deck workingDeck;

};

#endif // DECKEDITORTAB_H
