#ifndef TABSELECTOR_H
#define TABSELECTOR_H

/*
 * Simple widget holding buttons corresponding to tabs,
 * sends out signals if they are pressed.
 *
 * Later will be customized for custom gui.
*/

#include <QWidget>
#include<QSize>
#include<QHBoxLayout>
#include<QPushButton>

#include "windowdefines.h"

//TabSelector variables
const static unsigned int CENTRAL_TABSELECTOR_HINT_WIDTH = MAINWINDOW_HINT_WIDTH;
const static unsigned int CENTRAL_TABSELECTOR_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT/8;
const static unsigned int CENTRAL_TABSELECTOR_BUTTONS_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/5;

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
