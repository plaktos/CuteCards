#include "wordeditorbuttonbar.h"

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

    // If the new card button is pressed then the user,
    // can add a new word to the deck, to represent this
    // the alternatingButton is set to text Add as opposed to Save
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
            this, &WordEditorButtonBar::FinishedLanguageAddingButtonPressed);
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
