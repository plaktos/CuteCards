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

#ifndef DECKSCROLLLISTENTRY_H
#define DECKSCROLLLISTENTRY_H

/* DeckScrollListEntry widgets refer to corresponding
 * decks, and provide a way for the user to interact
 * with the decks.
*/

#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
#include<QCheckBox>
#include<QSize>
#include<QSizePolicy>
#include<QPaintEvent>
#include<QPainter>
#include<QMouseEvent>

class DeckLabel : public QLabel
{
    Q_OBJECT
public:
    explicit
    DeckLabel(QWidget *parent = nullptr)
        : QLabel(parent)                                    { setSizePolicy(QSizePolicy::Minimum,
                                                                            QSizePolicy::Expanding);
                                                              setMaximumWidth(120);}

    explicit
    DeckLabel(const QString& label,
              QWidget *parent = nullptr)
        : QLabel(label, parent)                             { setSizePolicy(QSizePolicy::Minimum,
                                                                            QSizePolicy::Expanding);
                                                              setMaximumWidth(120);}

    QSize sizeHint() const override                         { return QSize(120,20); }
    QSize minimumSizeHint() const override                  { return QSize(120,20); }
};

class DeckScrollListEntry : public QWidget
{
    Q_OBJECT
public:
    explicit
    DeckScrollListEntry(int index,
                        const QString& title,
                        const QStringList &langs,
                        QWidget *parent = nullptr);

    QSize sizeHint() const override                         { return QSize(300,35); }
    QSize minimumSizeHint() const override                  { return QSize(300,35); }

    // Used to determine whether the this widget,
    // that refers to a deck is selected
    bool isSelected()                                       { return selectedCheckBox->isChecked(); }

    QString getTitle()                                      { return titleLabel->text(); }
    QStringList getLanguages()                              { return languages; }

signals:
    void EditButtonPressed(const int &index);

    // Send a signal if the selection regarding this widget has changed
    void SelectedStateChanged(const int &index, const Qt::CheckState& state);

protected:
    // Overriding the mouse press event. If the user clicks on the widget,
    // it gets selected
    void mousePressEvent(QMouseEvent * e) override;

private:
    // Send an edit button pressed signal with the id of this widget.
    // this gets forwarded to CentralWidget, and start DeckEditor mode with
    // the deck this widget corresponds to.
    void SendSignalEditButtonPressed()                      { emit EditButtonPressed(id); }

    // Send a state change signal with the id of this widget,
    // this gets forwarded to DeckSelectionTab, where we
    // store the selection state for every DeckScrolLListEntry.
    void SendSignalSelectedStateChanged()                   { emit SelectedStateChanged(id, selectedCheckBox->checkState()); }
    QHBoxLayout *mainLayout;
    int id;

    QCheckBox *selectedCheckBox;
    DeckLabel *titleLabel;
    DeckLabel *languageLabel;
    QPushButton *editButton;
    QStringList languages;
};

#endif // DECKSCROLLLISTENTRY_H
