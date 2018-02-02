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

/* Decks store Flashcards inside a QList<Flashcard>
 * A Deck has a KeyIndex, which holds which language is the current key.
 * The word with the key is the one that is shown first, and the rest are shown
 * after user interaction.
 *
 * A Flashcard in a deck must have an equal number of words to the languages in the deck.
 * So for any given Deck;   Deck::at(n).size() == Deck::languages.size()
 *
 * A key can be set with setKey(n) where n < languages.size()
 * The method key(n) returns the key word of the corresponding Flashcard.
 * The method withoutKey() returns a QStringList without the key word.
*/

#include<QJsonObject>
#include<QJsonArray>

#include "flashcard.h"

struct Deck{

    Deck()
        : title("Empty Deck"),
          languages{"empty"},
          cards(),
          keyIndex(0) {}

    Deck(const QString& str_title,
         const QStringList list_langs,
         const QList<Flashcard>& card_list)
            : title(str_title),
            languages(list_langs),
            cards(card_list),
            keyIndex(1) {}

    inline
    Flashcard& operator[](int i)                    { return cards[i]; }

    inline
    const Flashcard& at(int i) const                { return cards.at(i); }

    inline
    QList<Flashcard> getCards() const               { return cards; }


    bool operator<(const Deck &rhs) const           { return getTitle() < rhs.getTitle() ?
                                                      true :false; }

    inline
    bool operator==(const Deck& other) const        { return (title == other.title) &&
                                                             (languages == other.languages) &&
                                                             (cards == other.cards) &&
                                                             ( keyIndex == other.keyIndex) ?
                                                             true : false; }

    inline
    bool operator !=(const Deck& other) const       { return !(this->operator==(other)); }


    inline
    bool empty() const                              { return cards.size() > 0 ? false : true;}

    inline
    void addCard(const Flashcard& card)             { cards.append(card); }

    void
    mergeDeck(const Deck& other)                    { cards += other.getCards(); }

    inline
    void removeAt(int i)                            { cards.removeAt(i); }

    inline
    QString getTitle() const                        { return title; }

    inline
    void setTitle(const QString& text)              { title = text; }

    inline
    QStringList getLanguages() const                { return languages; }

    void setLanguages(const QStringList& langs)     { languages = langs; }

    inline
    size_t size() const                             { return cards.size(); }

    inline
    QString key(unsigned int n) const               { return cards.at(n).at(keyIndex); }

    inline
    int getKeyIndex() const                         { return keyIndex; }

    inline
    QString keyLanguage() const                     {return languages[keyIndex];}

    inline
    void setKey(unsigned int i)                     { if(!(i > languages.size()-1)){
                                                        keyIndex = i;} }

    QStringList withoutKey(unsigned int n)          { QStringList retlist;
                                                      for(int i = 0; i < cards[n].size(); ++i){
                                                          if(!(i == keyIndex))
                                                              retlist.append(cards[n].at(i)); }
                                                      return retlist; }

    QJsonObject ToJsonObject() const
    {
        QJsonObject root;
        QJsonObject properties;
        QJsonArray wordArray;
        QJsonArray languageArray;
        for(auto lang : languages){
            languageArray.append(lang);
        }
        for(auto card : cards){
            QJsonArray currCardArray;
            for(auto word : card){
                currCardArray.append(word);
            }
            wordArray.append(currCardArray);
        }
        properties["Languages"] = languageArray;
        properties["Title"] = title;
        root["Properties"] = properties;
        root["Words"] = wordArray;
        return root;
    }

private:
    QString title;
    QStringList languages;
    QList<Flashcard> cards;
    unsigned int keyIndex;
};

#endif // DECK_H
