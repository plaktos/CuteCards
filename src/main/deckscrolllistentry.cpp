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

#include "deckscrolllistentry.h"

DeckScrollListEntry::DeckScrollListEntry(int index,
                                         const QString &title,
                                         const QStringList &langs,
                                         QWidget *parent)
    : QWidget(parent),
      id(index),selected(false),
      languages(langs)
{
    // Setup members
    selectedCheckBox = new QCheckBox(this);
    selectedCheckBox->setVisible(false);
    titleLabel = new DeckLabel(title);

    languageLabel = new DeckLabel;
    QString languageLabelText;
    QFont languageLabelFont(languageLabel->font());
    languageLabelFont.setPointSizeF(languageLabelFont.pointSizeF()-1.8);
    languageLabelText.append(langs[0]);
    for(int i = 1; i < langs.size(); ++i){
        languageLabelText.append(QString(",") + langs[i]);
    }
    languageLabel->setText(languageLabelText);
    languageLabel->setFont(languageLabelFont);

    editButton = new QPushButton("E");
    editButton->setMaximumSize(20,15);

    // Setup Layout
    mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(editButton);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(languageLabel);

    // Setup this
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Fixed);
    setAutoFillBackground(true);

    // Connections
    connect(editButton, &QPushButton::pressed,
            this, &DeckScrollListEntry::SendSignalEditButtonPressed);

    connect(selectedCheckBox, &QCheckBox::stateChanged,
            [this](){
        selected = selectedCheckBox->isChecked();
        emit SelectedStateChanged(id,selected);
    });
}

void
DeckScrollListEntry::paintEvent(QPaintEvent *event){
    QPalette pal(palette());
    if(selected){
        pal.setColor(QPalette::WindowText, Qt::green);
        setPalette(pal);
    }
    else{
        pal.setColor(QPalette::WindowText, Qt::black);
        setPalette(pal);

    }
    update();
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
