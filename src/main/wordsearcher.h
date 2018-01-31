#ifndef WORDSEARCHER_H
#define WORDSEARCHER_H

#include <QWidget>
#include<QVBoxLayout>
#include<QScrollArea>

#include"deck.h"
#include"wordscrolllist.h"
#include "wordsearcherbar.h"

class WordSearcher : public QWidget
{
    Q_OBJECT
public:
    explicit
    WordSearcher(QWidget *parent = nullptr);

signals:
    void ToEditFlashcardAt(int index);
    void ToDeleteEntryAt(int index);
    void ToUnlockWordScrollList();

public slots:
    void refreshListWithDeck(const Deck& deck);

private:
    QVBoxLayout *mainLayout;
    WordSearcherBar *searchBar;
    WordScrollList *wordScrollList;

};

#endif // WORDSEARCHER_H
