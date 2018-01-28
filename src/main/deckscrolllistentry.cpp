#include "deckscrolllistentry.h"

DeckScrollListEntry::DeckScrollListEntry(const QString &title, int index, QWidget *parent)
    : QWidget(parent),
      id(index)
{
    // Setup members
    selectedCheckBox = new QCheckBox;
    titleLabel = new QLabel(title);
    editButton = new QPushButton("E");
    editButton->setMaximumSize(20,15);

    // Setup Layout
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(selectedCheckBox);
    mainLayout->addStretch(10);
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch(30);
    mainLayout->addWidget(editButton);
    mainLayout->addStretch(1);

    // Setup this
    setLayout(mainLayout);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    setSizePolicy(sizePolicy);

    // Connections
    connect(editButton, &QPushButton::pressed,
            this, &DeckScrollListEntry::SendSignalEditButtonPressed);

    connect(selectedCheckBox, &QCheckBox::stateChanged,
            this, &DeckScrollListEntry::SendSignalSelectedStateChanged);
}

void
DeckScrollListEntry::paintEvent(QPaintEvent *e){
    //QPainter painter(this);
    //painter.setPen(QPen(Qt::black,4));
    //painter.drawRect(x(), y(),
    //                 width(), height());
    QWidget::paintEvent(e);
}

void
DeckScrollListEntry::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        selectedCheckBox->setChecked(!selectedCheckBox->isChecked());
    }
    else{
        QWidget::mousePressEvent(e);
    }
}
