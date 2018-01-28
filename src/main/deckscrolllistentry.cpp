#include "deckscrolllistentry.h"

DeckScrollListEntry::DeckScrollListEntry(const QString &title, int index, QWidget *parent)
    : QWidget(parent),
      id(index)
{
    // Setup members
    titleLabel = new QLabel(title);
    editButton = new QPushButton("E");
    editButton->setMaximumSize(20,15);

    // Setup Layout
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch(30);
    mainLayout->addWidget(editButton);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);

    // Connections
    connect(editButton, &QPushButton::pressed,
            this, &DeckScrollListEntry::SendSignalEditButtonPressed);
}
