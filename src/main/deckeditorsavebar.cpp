#include "deckeditorsavebar.h"

DeckEditorSaveBarButton::DeckEditorSaveBarButton(const QString& text,
                                                 QWidget *parent)
    : QPushButton(text, parent)
{
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize
DeckEditorSaveBarButton::sizeHint() const {
    return QSize(50,50);
}

DeckEditorSaveBar::DeckEditorSaveBar(QWidget *parent)
    : QWidget(parent)
{
    saveButton = new DeckEditorSaveBarButton("\342\234\224");
    cancelButton = new DeckEditorSaveBarButton("\342\234\225");

    mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);
    mainLayout->addStretch(1);

    setLayout(mainLayout);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);
    setPalette(pal);
    setAutoFillBackground(true);

    connect(saveButton, &DeckEditorSaveBarButton::pressed,
            this, &DeckEditorSaveBar::saveButtonPressed);
    connect(cancelButton, &DeckEditorSaveBarButton::pressed,
            this, &DeckEditorSaveBar::cancelButtonPressed);
}
