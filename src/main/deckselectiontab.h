#ifndef DECKSELECTIONTAB_H
#define DECKSELECTIONTAB_H

#include <QWidget>
#include<QVector>
#include<QDir>
#include<QStringList>
#include<QMap>

#include "tab.h"
#include "windowdefines.h"
#include "decksearcher.h"
#include "deckloader.h"

const static unsigned int DECKSELECTIONTAB_HINT_WIDTH = MAINWINDOW_HINT_WIDTH;
const static unsigned int DECKSELECTIONTAB_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT;

class DeckSelectionTab : public Tab
{
    Q_OBJECT
public:
    explicit DeckSelectionTab(QWidget *parent = nullptr);

    QSize sizeHint() const override                                     { return QSize(DECKSELECTIONTAB_HINT_WIDTH,
                                                                                       DECKSELECTIONTAB_HINT_HEIGHT); }

signals:
    // Send out a signal requesting an exam to start with the deck created from
    // the availableDeckSelectionIndexes
    void ExamToStartWithDeck(const QWeakPointer<Deck>& deck);

    // Send out a signal with the new titles of the decks
    void AvailableDeckTitlesChanged(const QStringList &titles);

    void ToEditDeck(const Deck& deck);

public slots:

    inline
    void changeSelectedAvailableDecksList(const int &index,
                                          Qt::CheckState state);

    //inline
    //void chaneSelectedExamDecksList(const int &index,
    //                                Qt::CheckState state);

    void SignalToEditAvailableDeckAt(const int &index);

    void LoadAvailableDecks();

    // Connected to the signal of examDecksSearcher's bottom button.
    // Creates a new deck from the selectionIndexes
    // and emits the ExamToStartWithDeck signal
    void StartExam();

protected:

private:
    QHBoxLayout *mainLayout;

    DeckSearcher *availableDecksSearcher;
    DeckSearcher *examDecksSearcher;

    QList<Deck> availableDecks;
    QList<Deck> examDecks;
    QVector<Qt::CheckState> availableDecksSelectionIndexes;
    QVector<Qt::CheckState> examDecksSelectionIndexes;

    QSharedPointer<Deck> currExamDeck;

};

#endif // DECKSELECTIONTAB_H
