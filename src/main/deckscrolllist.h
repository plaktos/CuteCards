#ifndef DECKSCROLLLIST_H
#define DECKSCROLLLIST_H

/*
 * DeckScrollList holds a list of Deck titles,
 * provides a way for the user to select one more multiple decks
 * and then send a signal with these indexes.
 * Should be contained within a DeckSearcher, which provides a SearchBar,
 * whose textChanged signal should be connected with DeckScrollList changeTextToSearchFor,
 * Apply QScrollArea to it after construction to make it scrollable.
*/

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QTimer>

class DeckScrollList : public QWidget
{
    Q_OBJECT
public:
    explicit DeckScrollList(QWidget *parent = nullptr);

signals:
    // Upon the user selecting decks a selectionChanged signal gets sent.
    void selectionChanged(QVector<int> indexes);

public slots:
    // changes the text to search for among the titles, and start the timer,
    // so as to avoid searching every time the SearchBar recieves an input.
    void changeTextToSearchFor(const QString& text)                     { textToSearchFor = text;
                                                                          searchTimer->start(300);}

    // Changes the deckTitleList, should be connected to DeckSearcher's DeckTitleListChanged signal,
    void setDeckTitleList(const QList<QString>& titles)                 { deckTitleList = titles;
                                                                          InitTitleLabels(); }

private:
    // Deletes previous Labels, and initializes new ones,
    // based on the titles in deckTitleList.
    void InitTitleLabels();

    //Hides all labels, called by doASearch(), before doing a search
    void HideAllTitleLabels();
    void doASearch();

    QVBoxLayout *mainLayout;

    QList<QString> deckTitleList;
    QList<QLabel *> deckTitleLabels;
    QTimer *searchTimer;
    QString textToSearchFor;


};

#endif // DECKSCROLLLIST_H
