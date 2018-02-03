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

#ifndef DECKLOADER_H
#define DECKLOADER_H

/*
 * Loads .deck files with fromDeckFile(filepath)
 * .deck files get validated both as a valid JSON document,
 * and as a valid .deck file.
 *
 * Usage:   DeckLoader::fromDeckFile(path to file)
*/

#include<QList>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonArray>
#include<QDebug>
#include<QDir>

#include "flashcard.h"
#include "deck.h"

class DeckLoader{

public:
    DeckLoader(){}

    //Returns loaded and parsed decks from the argument filename
    static
    Deck fromDeckFile(const QString& filename);

    static
    Deck fromCSVFile(const QString& filename);

private:
    //Makes sure .deck file is formatted properly
    //Called by parseDeck before parsing.
    static
    bool validateDeck(const QJsonDocument& doc);

    //Parses the deck in .data and returns a Deck
    static
    Deck parseDeck(const QJsonDocument& doc);

    //Loads and returns a QJsonDocument, that is sure to have proper JSON syntax
    static
    const QJsonDocument loadJsonDoc(const QString& filename);

};

#endif // DECKLOADER_H
