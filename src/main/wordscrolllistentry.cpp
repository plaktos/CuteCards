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

#include "wordscrolllistentry.h"

WordScrollListEntryLabel::WordScrollListEntryLabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    QFont newfont(font());
    newfont.setPointSize(newfont.pointSize() + 4);
    setFont(newfont);
    setText(text);
    setSizePolicy(QSizePolicy::Fixed,
                  QSizePolicy::Fixed);
}

QSize
WordScrollListEntryLabel::sizeHint() const{
    return QSize(60,30);
}

WordScrollListEntryDeleteButton::WordScrollListEntryDeleteButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setSizePolicy(QSizePolicy::Fixed,
                  QSizePolicy::Fixed);
}

QSize
WordScrollListEntryDeleteButton::sizeHint() const {
    return QSize(20,20);
}

WordScrollListEntry::WordScrollListEntry(int index, QWidget *parent)
    : QWidget(parent),
      id(index)
{
    deleteButton = new WordScrollListEntryDeleteButton("D");

    mainLayout = new QHBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(deleteButton);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);

    connect(deleteButton, &WordScrollListEntryDeleteButton::pressed,
            [this](){
        emit DeleteButtonPressed(id);
    });
}

void
WordScrollListEntry::addWord(const QString &word){
    WordScrollListEntryLabel *label = new WordScrollListEntryLabel(word);
    mainLayout->insertWidget(mainLayout->count()-1, label);
    words.append(word);
}

void
WordScrollListEntry::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        emit selected(id);
    }
    else{
        QWidget::mousePressEvent(e);
    }
}
