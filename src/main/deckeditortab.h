#ifndef DECKEDITORTAB_H
#define DECKEDITORTAB_H

#include <QWidget>
#include<QFrame>
#include<QList>
#include<QFileDialog>
#include<QJsonDocument>
#include<QGridLayout>
#include<QLineEdit>

#include "deck.h"
#include "deckloader.h"
#include "wordsearcher.h"
#include "wordeditor.h"
#include "deckeditorsavebar.h"

class DeckOptionsPanel : public QFrame
{
    Q_OBJECT
public:
    explicit
    DeckOptionsPanel(QWidget* parent = nullptr);

    QString getTitle() const                   { return titleLineEdit->text(); }

signals:
    void ImportCSVButtonPressed();
    void ExportCSVButtonPressed();


private:
    QGridLayout *mainLayout;

    QLineEdit *titleLineEdit;
    QPushButton *importCSVButton;
    QPushButton *exportCSVButton;
};

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
    void importDeckFromCSV();
    void exportDeckToCSV();
    void LoadFlashcardAtIntoWordEditor(int index);
    void addFlashcardToWorkingDeck(const Flashcard& card);
    void saveFlashcardToWorkingDeck(const int &index,
                               const Flashcard& card);
    void deleteFlashcardFromWorkingDeckAt(const int &index);

private:
    void InitWordEditorLanguageList();

    QGridLayout *mainLayout;

    WordSearcher *wordSearcher;
    WordEditor *wordEditor;
    DeckOptionsPanel *deckOptionsPanel;
    DeckEditorSaveBar *deckEditorSaveBar;
    Deck workingDeck;

};

#endif // DECKEDITORTAB_H
