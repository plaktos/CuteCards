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

#ifndef KEYLANGUAGESELECTOR_H
#define KEYLANGUAGESELECTOR_H

/*
 * Provides a panel for the user to select which language
 * should be the key language.
 * getKeyLanguageIndex returns the index of the selected language
*/

#include <QWidget>
#include<QRadioButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QFont>

class KeyLanguageSelector : public QWidget
{
    Q_OBJECT
public:
    explicit KeyLanguageSelector(QWidget *parent = nullptr);

    void addLanguage(const QString& lang);
    void clear();

    int getKeyLanguageIndex();
signals:

public slots:

private:
    QHBoxLayout *mainLayout;
    QVector<QLabel *> langLabels;
    QVector<QRadioButton *> radioButtons;
    QFont langLabelFont;
};

#endif // KEYLANGUAGESELECTOR_H
