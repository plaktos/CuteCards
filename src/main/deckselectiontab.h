#ifndef DECKSELECTIONTAB_H
#define DECKSELECTIONTAB_H

#include <QWidget>
#include<QVector>
#include<QDir>
#include<QStringList>

#include "tab.h"
#include "constdefines.h"
#include "decksearcher.h"
#include "deckloader.h"

class DeckSelectionTab : public Tab
{
    Q_OBJECT
public:
    explicit DeckSelectionTab(QWidget *parent = nullptr);

    QSize sizeHint() const override                                     { return QSize(DECKSELECTIONTAB_HINT_WIDTH,
                                                                                       DECKSELECTIONTAB_HINT_HEIGHT); }

signals:
    void ExamToStartWithDeck(const QWeakPointer<Deck>& deck);
    void AvailableDeckTitlesChanged(const QStringList &titles);

public slots:
    inline
    void setAvailableDecksSelectedIndexes(const QVector<int> &indexes)  { availableDecksSelectionIndexes = indexes; }
    inline
    void setExamDecksSelectedIndexes(const QVector<int> &indexes)       { examDecksSelectionIndexes = indexes; }
    void LoadAvailableDecks();

protected:

private:
    void StartExam();

    QHBoxLayout *mainLayout;

    DeckSearcher *availableDecksSearcher;
    DeckSearcher *examDecksSearcher;

    QList<Deck> availableDecks;
    QList<Deck> examDecks;
    QVector<int> availableDecksSelectionIndexes;
    QVector<int> examDecksSelectionIndexes;

    QSharedPointer<Deck> currExamDeck;

};

#endif // DECKSELECTIONTAB_H
