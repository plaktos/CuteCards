#include "wordsearcherbar.h"

WordSearcherBar::WordSearcherBar(QWidget *parent)
    : QLineEdit(parent)
{
    searchTimer = new QTimer;
    searchTimer->setSingleShot(true);

    setPlaceholderText("Search...");

    connect(searchTimer, &QTimer::timeout,
            [this] () {
        emit needSearchFor(text());
    });

    connect(this, &WordSearcherBar::textChanged,
            [this] () {
        searchTimer->start(50);
    });
}

void
WordSearcherBar::mousePressEvent(QMouseEvent *e){
    if(!hasFocus()){
        setText("");
    }
}
