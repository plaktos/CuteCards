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

#ifndef FLASHCARD_H
#define FLASHCARD_H

/*
 *  A Flashcard stores words in its member QStringList
 * Flashcards get created when reading a .deck file and are stored in a Deck object.
*/


#include <QStringList>

struct Flashcard{

    Flashcard()
        : num_words(0),
          words()                                        { }

    Flashcard(const std::initializer_list<QString>& wlist)
        : num_words(wlist.size()),
          words()                                       { for(auto elem : wlist) { words.append(elem); } }

    Flashcard(const QStringList &wlist)
        : num_words(wlist.size()),
          words(wlist) {}

    QStringList::const_iterator begin()                 { return words.begin(); }
    QStringList::const_iterator end()                 { return words.end(); }

    inline
    bool operator==(const Flashcard& other) const       { return (num_words == other.num_words) &&
                                                                 (words == other.words) ?
                                                                 true : false; }
    inline
    Flashcard& operator=(const Flashcard& rhs)           { num_words = rhs.num_words;
                                                          words = rhs.words;
                                                          return *this;}

    inline
    bool operator !=(const Flashcard& other) const      { return !(this->operator==(other)); }

    inline
    QString operator[](const int i)  const              { return words.at(i); }

    inline
    int size() const                                    { return words.size(); }

    inline
    bool empty() const                                  { return words.size() == 0 ? true : false;}

    inline
    QString at(const int i) const                       { return this->operator[](i); }

    inline
    QStringList getWords()                               { return words; }


private:

    int num_words;
    QStringList words;
};

#endif // FLASHCARD_H
