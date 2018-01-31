#include "wordeditorscrolllist.h"

WordEditorScrollList::WordEditorScrollList(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QFormLayout;
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::MinimumExpanding,
                  QSizePolicy::MinimumExpanding);
}

QSize
WordEditorScrollList::sizeHint() const {
    return QSize(200,200);
}

void
WordEditorScrollList::clear(){
    for(auto lineedit : valueLines){
        delete lineedit;
    }
    for(auto label : labelLines){
        delete label;
    }

    valueLines.clear();
    labelLines.clear();
}

void
WordEditorScrollList::clearValues(){
    for(QLineEdit* lineedit : valueLines){
        lineedit->setText("");
    }
}

void
WordEditorScrollList::addEditingLineForLanguage(const QString &language){
    QLabel *langLabel = new QLabel(language);
    QLineEdit *langValue = new QLineEdit;
    mainLayout->addRow(langLabel, langValue);
    valueLines.append(langValue);
    labelLines.append(langLabel);
}

void
WordEditorScrollList::loadFromCard(const Flashcard &card){
    for(int i = 0; i < card.size(); ++i){
        valueLines[i]->setText(card.at(i));
    }
}

Flashcard
WordEditorScrollList::toCard(){
    QStringList enteredWords;
    for(QLineEdit* lineedit : valueLines){
        enteredWords.append(lineedit->text());
    }
    for(auto word : enteredWords){
        if(word == "")
           return Flashcard();
    }
    return Flashcard(enteredWords);
}

