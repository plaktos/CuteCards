//
//This file is part of CuteCards software.
//
//    CuteCards is Flashcard software developed in C++, with the use of the Qt Framework
//    Copyright (C) 2018 Peter Lakatos
//
//    CuteCards is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    CuteCards is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with CuteCards.  If not, see <http://www.gnu.org/licenses/>.
//

#include "examtab.h"

ExamTab::ExamTab(QWidget *parent)
    : QWidget(parent),
      deck(),
      mainBox(0),
      currCardIndex(0)
{
    mainBox = new ExamMainBox;

    QPushButton *changeDeckButton = new QPushButton("Change Deck");
    changeDeckButton->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(changeDeckButton);
    mainLayout->addWidget(mainBox);

    setLayout(mainLayout);
    setFocusPolicy(Qt::StrongFocus);

    //Connections with changeDeckButton
    connect(changeDeckButton, SIGNAL(released()),
            this, SLOT(changeDeck()));

    //Connections with mainBox
    connect(this, SIGNAL(deckChanged(QWeakPointer<Deck>)),
            mainBox, SLOT(setCurrentDeck(QWeakPointer<Deck>)));
    connect(this, SIGNAL(changeToNextCard(unsigned int)),
            mainBox, SLOT(NextCard(unsigned int)));
    connect(this, SIGNAL(toRevealCard()),
            mainBox, SLOT(RevealCard()));
}

void
ExamTab::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return){
        NextCard();
    }
    else if(event->key() == Qt::Key_Space){
        emit toRevealCard();
    }
    else{
        QWidget::keyPressEvent(event);
    }
}

void
ExamTab::NextCard(){
    if(currCardIndex > deck->size() - 1){
        //FinishExam();
    }
    else{
        emit changeToNextCard(currCardIndex);
        ++currCardIndex;
    }
}

void
ExamTab::changeDeck(){
    QString filename = QFileDialog::getOpenFileName(this,
                     "Open deck file", "./", "Decks(*.deck)");

    if(filename.isEmpty()){
        qDebug() << "No file specified";
        return;
    }
    QSharedPointer<Deck> newDeck(new Deck(DeckLoader::fromDeckFile(filename)));

    //We dont change current deck until we are sure deck was loaded successfully
    if(!newDeck.isNull()){
        deck.reset();
        deck = newDeck;
        currCardIndex = 0;
        emit deckChanged(deck.toWeakRef());
    }
}
