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

#ifndef DECK_H
#define DECK_H

#include "flashcard.h"


struct Deck{

    Deck()
        : title("Empty Deck"),
          languages{"empty"},
          cards(),
          keyIndex(0) {}

    Deck(const QString& str_title,
         const QList<QString> list_langs,
         const QList<Flashcard>& card_list)
            : title(str_title),
            languages(list_langs),
            cards(card_list),
            keyIndex(1) {}

    inline
    const Flashcard operator[](int i) const         { return cards.at(i); }

    inline
    bool operator==(const Deck& other) const        { return (title == other.title) && (languages == other.languages) &&
                                                             (cards == other.cards) ?
                                                             true : false; }

    inline
    bool operator !=(const Deck& other) const       { return !(this->operator==(other)); }


    inline
    bool empty() const                              { return cards.size() > 0 ? false : true;}

    inline
    QString getTitle() const                        { return title; }

    inline
    QList<QString> getLanguages() const             { return languages; }

    inline
    size_t size() const                             { return cards.size(); }

    inline
    QString key(unsigned int n) const               { return cards.at(n).at(keyIndex); }

    inline
    QString keyLanguage() const                     {return languages[keyIndex];}

    inline
    void setKey(unsigned int i)                     { if(!(i > languages.size()-1)){
                                                        keyIndex = i;}
                                                      }

    QList<QString> withoutKey(unsigned int n)       { QList<QString> retlist;
                                                      for(int i = 0; i < cards[n].size(); ++i){
                                                          if(!(i == keyIndex))
                                                              retlist.append(cards[n].at(i)); }
                                                      return retlist; }

private:
    QString title;
    QList<QString> languages;
    QList<Flashcard> cards;
    unsigned int keyIndex;
};

#endif // DECK_H
