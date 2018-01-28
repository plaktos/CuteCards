#ifndef TABSELECTOR_H
#define TABSELECTOR_H

#include <QWidget>
#include<QSize>
#include<QHBoxLayout>
#include<QPushButton>

#include "constdefines.h"

class TabSelector : public QWidget
{
    Q_OBJECT
public:
    explicit
    TabSelector(QWidget *parent = nullptr);

    QSize
    sizeHint() const override                   { return QSize(CENTRAL_TABSELECTOR_HINT_WIDTH,
                                                               CENTRAL_TABSELECTOR_HINT_HEIGHT); }

signals:
    void DeckSelectionTabSelected();
    void DeckEditorTabSelected();
    void StatisticsTabSelected();

public slots:

private:
    QHBoxLayout *mainLayout;

    QPushButton *deckSelectionTabButton;
    QPushButton *deckEditorTabButton;
    QPushButton *statisticsTabButton;

};

#endif // TABSELECTOR_H
