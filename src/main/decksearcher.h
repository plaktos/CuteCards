#ifndef DECKSEARCHER_H
#define DECKSEARCHER_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>

#include "decksearchbar.h"
#include "deckscrolllist.h"
#include "deck.h"

const static unsigned int DECKSEARCHER_HINT_WIDTH = 200;
const static unsigned int DECKSEARCHER_HINT_HEIGHT = 500;

class DeckSearcher : public QWidget
{
    Q_OBJECT
public:
    explicit DeckSearcher(QWidget *parent = nullptr);

    QSize sizeHint() const override                             { return QSize(DECKSEARCHER_HINT_WIDTH,
                                                                               DECKSEARCHER_HINT_HEIGHT); }

    void setBottomButtonText(const QString &text)               { bottomButton->setText(text); }

    QVector<int> selection()                                      { return selectionIndexes; }

signals:
    void bottomButtonPressed();
    void DeckTitleListChanged(const QList<QString> &titles);
    void SelectionChanged(const QVector<int> &indexes);

public slots:
    void setDeckTitleList(const QList<QString> &titles)         { emit DeckTitleListChanged(titles); }

    void changeSelection(const QVector<int> &indexes)           { selectionIndexes = indexes;
                                                                  emit SelectionChanged(indexes); }

private:
    QVBoxLayout *mainLayout;

    DeckSearchBar *deckSearchBar;
    DeckScrollList *deckScrollList;
    QPushButton *bottomButton;

    QVector<int> selectionIndexes;
};

#endif // DECKSEARCHER_H
