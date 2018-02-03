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

#include "deck.h"

Deck::Deck()
        : title("Empty Deck"),
          languages{"empty"}, numOfLanguages(0),
          cards(),
          keyIndex(0) {}

Deck::Deck(const QString& str_title,
         const QStringList list_langs,
         const QList<Flashcard>& card_list)
            : title(str_title),
            languages(list_langs), numOfLanguages(list_langs.size()),
            cards(card_list),
            keyIndex(0) {}


QStringList
Deck::withoutKey(unsigned int n) const {
    QStringList retlist;
    for(int i = 0; i < cards[n].size(); ++i){
        if(!(i == keyIndex))
            retlist.append(cards[n].at(i));
    }
    return retlist;
}

QJsonObject
Deck::ToJsonObject() const{
    QJsonObject root;
    QJsonObject properties;
    QJsonArray wordArray;
    QJsonArray languageArray;

    // Append all languages(QString) to a JSON array
    for(auto lang : languages){
        languageArray.append(lang);
    }

    // For every flashcard in the deck,
    // for every word in the flashcard append it to a JSON array.
    // then append the JSON array that got created during this iteration,
    // to the JSON array containing the flashcards
    for(auto card : cards){
        QJsonArray currCardArray;
        for(auto word : card){
            currCardArray.append(word);
        }
        wordArray.append(currCardArray);
    }

    // Add the key "Languages" to the JSON object properties with the value of
    // the array containing the languages
    properties["Languages"] = languageArray;
    properties["Title"] = title;

    // Add the two JSON objects to the root.
    root["Properties"] = properties;
    root["Words"] = wordArray;

    // return the root JSON Object
    return root;
}
