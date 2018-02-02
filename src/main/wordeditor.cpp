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
    newCardButton = new WordEditorButtonBarButton("New Word");
    alternatingButton = new WordEditorButtonBarButton("Add Word");
    addLanguageButton = new WordEditorButtonBarButton("Add language");
    finishedLanguageAddingButton = new WordEditorButtonBarButton("Finished");

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(addLanguageButton);
    mainLayout->addWidget(finishedLanguageAddingButton);
    mainLayout->addWidget(newCardButton);
    mainLayout->addWidget(alternatingButton);

    setLayout(mainLayout);

    connect(addLanguageButton, &QPushButton::pressed,
            this, &WordEditorButtonBar::AddLanguageButtonPressed);

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

    connect(finishedLanguageAddingButton, &WordEditorButtonBarButton::pressed,
            [this](){
        setLanguageEditMode(false);
    });
}

void
WordEditorButtonBar::setLanguageEditMode(bool flag){
    if(flag){
        newCardButton->setHidden(true);
        alternatingButton->setHidden(true);
        addLanguageButton->setHidden(false);
        finishedLanguageAddingButton->setHidden(false);
    }
    else{
        newCardButton->setHidden(false);
        alternatingButton->setHidden(false);
        addLanguageButton->setHidden(true);
        finishedLanguageAddingButton->setHidden(true);
    }
}

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
