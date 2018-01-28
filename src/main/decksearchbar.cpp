#include "decksearchbar.h"

DeckSearchBar::DeckSearchBar(QWidget *parent)
    : QLineEdit(parent)
{
    setText("Search...");
}

void
DeckSearchBar::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        setText("");
    }
    else{
        QLineEdit::mousePressEvent(e);
    }
}

void
DeckSearchBar::focusOutEvent(QFocusEvent *e){
    setText("Search...");
    QLineEdit::focusOutEvent(e);
}
