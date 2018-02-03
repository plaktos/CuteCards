#include "deckoptionspanel.h"


DeckOptionsPanel::DeckOptionsPanel(QWidget *parent)
    : QFrame(parent)
{
    titleLineEdit = new QLineEdit;
    titleLineEdit->setPlaceholderText("Title...");

    importCSVButton = new QPushButton("Import CSV");
    exportCSVButton = new QPushButton("Export CSV");

    mainLayout = new QGridLayout;
    mainLayout->addWidget(titleLineEdit, 0,0, 1,2);
    mainLayout->addWidget(exportCSVButton, 1,0, 1,1);
    mainLayout->addWidget(importCSVButton, 1,1, 1,1);

    setLayout(mainLayout);

    connect(importCSVButton, &QPushButton::pressed,
            this, &DeckOptionsPanel::ImportCSVButtonPressed);
    connect(exportCSVButton, &QPushButton::pressed,
            this, &DeckOptionsPanel::ExportCSVButtonPressed);
}
