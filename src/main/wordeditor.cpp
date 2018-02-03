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

#include "wordeditor.h"

AddLanguageDialog::AddLanguageDialog(QWidget *parent)
    : QDialog(parent),
      enteredLanguage("")
{
    langLineEdit = new QLineEdit;
    langLineEdit->setPlaceholderText("Language...");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("CANCEL");

    mainLayout = new QGridLayout;
    mainLayout->addWidget(langLineEdit, 0,0,1,2);
    mainLayout->addWidget(okButton, 1,0,1,1);
    mainLayout->addWidget(cancelButton, 1,1,1,1);

    setLayout(mainLayout);
    setMinimumSize(200,100);

    connect(okButton, &QPushButton::pressed,
            this, &AddLanguageDialog::accept);
    connect(cancelButton, &QPushButton::pressed,
            this, &AddLanguageDialog::reject);
    connect(langLineEdit, &QLineEdit::textChanged,
            [this](){
        enteredLanguage = langLineEdit->text();
    });
}

QSize
AddLanguageDialog::sizeHint() const{
    return QSize(200,100);
}

WordEditor::WordEditor(QWidget *parent)
    : QWidget(parent),
      loadedCardIndex(-1)
{
    scrollList = new WordEditorScrollList(this);
    bottomButtonBar = new WordEditorButtonBar;

    QScrollArea *scrollListArea = new QScrollArea;
    //scrollListArea->setMaximumSize(300,300);
    scrollListArea->setWidget(scrollList);
    QPalette scrollListAreaPalette(scrollListArea->palette());
    scrollListAreaPalette.setColor(QPalette::Background, Qt::gray);
    scrollListArea->setPalette(scrollListAreaPalette);
    scrollListArea->setAutoFillBackground(true);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scrollListArea);
    mainLayout->addWidget(bottomButtonBar);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Fixed,
                  QSizePolicy::Fixed);


    connect(this, &WordEditor::cardLoaded,
            bottomButtonBar, &WordEditorButtonBar::changeToSaveButton);

    connect(bottomButtonBar, &WordEditorButtonBar::NewCardButtonPressed,
            scrollList, &WordEditorScrollList::clearValues);

    connect(bottomButtonBar, &WordEditorButtonBar::AddButtonPressed,
            [this](){
        emit addCardPressedWithCard(scrollList->toCard());
        scrollList->clearValues();
    });

    connect(bottomButtonBar, &WordEditorButtonBar::SaveButtonPressed,
            [this](){
        emit saveCardPressedWithCard(loadedCardIndex, scrollList->toCard());
        scrollList->clearValues();
    });

    connect(this, &WordEditor::changedLanguageEditMode,
            bottomButtonBar, &WordEditorButtonBar::setLanguageEditMode);

    connect(bottomButtonBar, &WordEditorButtonBar::AddLanguageButtonPressed,
            this, &WordEditor::PromptToAddLanguageToScrollList);

    connect(bottomButtonBar, &WordEditorButtonBar::FinishedLanguageAddingButtonPressed,
            [this](){
        if(!(scrollList->getLanguages().size() < 2)){
            bottomButtonBar->setLanguageEditMode(false);
        }
    });
}

QSize
WordEditor::sizeHint() const{
    return QSize(250,300);
}

void
WordEditor::InitWithDeck(const Deck &deck){
    scrollList->clear();
    if(!deck.empty()){
        emit changedLanguageEditMode(false);
        for(auto lang : deck.getLanguages()){
            scrollList->addEditingLineForLanguage(lang);
        }
    }
    else
        emit changedLanguageEditMode(true);
}

void
WordEditor::setFlashcard(int index, const Flashcard &card){
    loadedCardIndex = index;
    scrollList->loadFromCard(card);
    emit cardLoaded();
}

void
WordEditor::PromptToAddLanguageToScrollList(){
    AddLanguageDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        QString lang = dialog.getLanguage();
        if(lang.size() > 1){
            scrollList->addEditingLineForLanguage(lang);
        }
    }
}
