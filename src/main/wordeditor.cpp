#include "wordeditor.h"

WordEditorButtonBarButton::WordEditorButtonBarButton(const QString &text, QWidget *parent)
    : QPushButton(text,parent)
{
    QSizePolicy(QSizePolicy::Fixed,
                QSizePolicy::Fixed);
}

QSize
WordEditorButtonBarButton::sizeHint() const {
    return QSize(50,35);
}

WordEditorButtonBar::WordEditorButtonBar(QWidget *parent)
    : QWidget(parent),
      saveMode(false)
{
    newCardButton = new WordEditorButtonBarButton("New");
    alternatingButton = new WordEditorButtonBarButton("Add");

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(newCardButton);
    mainLayout->addWidget(alternatingButton);

    setLayout(mainLayout);

    connect(newCardButton, &QPushButton::pressed,
            this, &WordEditorButtonBar::NewCardButtonPressed);
    connect(newCardButton, &QPushButton::pressed,
            [this] (){
       alternatingButton->setText("Add");
       saveMode = false;
    });

    connect(alternatingButton, &QPushButton::pressed,
            [this] () {
        if(saveMode)
            emit SaveButtonPressed();
        else
            emit AddButtonPressed();
    });

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
    });

    connect(bottomButtonBar, &WordEditorButtonBar::SaveButtonPressed,
            [this](){
        emit saveCardPressedWithCard(loadedCardIndex, scrollList->toCard());
    });
}

QSize
WordEditor::sizeHint() const{
    return QSize(250,300);
}

void
WordEditor::InitWithDeck(const Deck &deck){
    scrollList->clear();
    for(auto lang : deck.getLanguages()){
        scrollList->addEditingLineForLanguage(lang);
    }
}

void
WordEditor::setFlashcard(int index, const Flashcard &card){
    loadedCardIndex = index;
    scrollList->loadFromCard(card);
    emit cardLoaded();
}
