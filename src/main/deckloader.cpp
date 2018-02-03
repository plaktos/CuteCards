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

#include "deckloader.h"

Deck
DeckLoader::fromDeckFile(const QString &filename){
    QJsonDocument doc = loadJsonDoc(filename);
    if(doc.isNull()){
        qDebug() << "Returning empty deck";
        return Deck();
    }
    return parseDeck(doc);
}

Deck
DeckLoader::fromCSVFile(const QString &filename){
    QFile csvfile(filename);
    if(!csvfile.open(QIODevice::ReadOnly)){
        qDebug() << "Couldn't open " << filename;
        qDebug() << "Returning empty deck";
        return Deck();
    }

    Deck retDeck;
    QTextStream in(&csvfile);
    in.setCodec("UTF-8");
    while(!in.atEnd()){
        QStringList wordsOnLine = in.readLine().split(',', QString::SkipEmptyParts);
        retDeck.addCard(Flashcard(wordsOnLine));
    }
    csvfile.close();

    if(retDeck.empty()){
        qDebug() << "CSV file has no words";
        qDebug() << "Returning empty deck";
        return retDeck;
    }

    int numOfWordsInACard = retDeck.at(0).size();
    for(int i = 0; i < retDeck.size(); ++i){
        if(retDeck.at(i).size() != numOfWordsInACard){
            qDebug() << "Invalid deck read from csv file";
            qDebug() << "Number of words not equal on all lines";
            qDebug() << "Returning empty deck";
            return Deck();
        }
    }

    retDeck.setNumOfLanguages(numOfWordsInACard);
    return retDeck;
}

bool
DeckLoader::validateDeck(const QJsonDocument& doc){
    //If the base is not an object
    if(!doc.isObject()){
        return false;
    }

    QJsonObject json = doc.object();
    //If there is no JSON object "Properties" or if there is no JSON Array "Words"
    if(!json["Properties"].isObject() || !json["Words"].isArray()){
        return false;
    }

    QJsonObject properties = json["Properties"].toObject();
    QJsonArray words = json["Words"].toArray();

    //If "Title" key's value is not a string or if the "Languages" key's value is not an array.
    if(!properties["Title"].isString() || !properties["Languages"].isArray() ||
            !words.count() > 0){
        return false;
    }

    QJsonArray lang_array = properties["Languages"].toArray();
    //Check if any of the elements in the Languages JSON array is not a string
    for(auto iter : lang_array){
        if(!iter.isString()){
            return false;
        }
    }
    //Check if any of the "Words" array contain anything other than a JSON string
    for(auto array : words){
        // If there is a non array element in there, return false
        if(!array.isArray()){
            return false;
        }
        //If there are only arrays, check inside them if anything is not a string
        //We have to count the number of strings to check against the languages
        //So there are no more words than languages and vice versa
        int num_words = 0;
        for(auto jval_word : array.toArray()){
            if(!jval_word.isString()){
                return false;
            }
            num_words++;
        }
        //If there are more or less words in curr array than there are languages, then fail
        if(num_words != lang_array.size()){
            return false;
        }
    }

    //If everything looks okay, return true
    return true;
}

Deck
DeckLoader::parseDeck(const QJsonDocument& doc){
    if(!validateDeck(doc)){
        qDebug() << "Error: Deck formatting invalid, can't create deck.";
        qDebug() << "Returning an empty Deck";
        return Deck();
    }
    QJsonObject json = doc.object();

    QJsonObject jo_properties = json["Properties"].toObject();
    QJsonArray jarr_words = json["Words"].toArray();

    QString deck_title = jo_properties["Title"].toString();
    QJsonArray jarr_languages = jo_properties["Languages"].toArray();

    QList<Flashcard> deck_cards;
    QStringList deck_languages;

    //Append all the strings in "Languages" to deck_languages
    for(auto jval_language : jarr_languages){
        deck_languages.append(jval_language.toString());
    }

    //Go through every JSON array in "Words"
    //Every element inside "Words" is an array (we confirm this with validateData())
    for(auto array : jarr_words){
        QStringList strings_from_array;

        //Go through every JSON string in the current array
        for(auto jval_word : array.toArray()){
            strings_from_array.append(jval_word.toString());
        }
        deck_cards.append(Flashcard(strings_from_array));
        strings_from_array.clear();
    }

    return Deck(deck_title, deck_languages, deck_cards);
}

const QJsonDocument
DeckLoader::loadJsonDoc(const QString& filename){
    QFile loadfile(filename);
    if(!loadfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        auto errStr = loadfile.errorString();
        auto error = loadfile.error();
        auto path = QDir::currentPath();
        qDebug() << "Error String: " << errStr
                 << "\tError: " << error;
        return QJsonDocument();
    }
    qDebug() << "File " << filename << " opened.";

    QJsonParseError p_error;
    QJsonDocument document = QJsonDocument::fromJson(loadfile.readAll(), &p_error);
    if(document.isNull()){
        qDebug() << "Json document " << filename << "is invalid";
        qDebug() << "Error String : " << p_error.errorString()
                 << "\tError: " << p_error.error;
        return document;
    }
    qDebug() << "Json document "<< filename <<" is valid.";
    loadfile.close();
    qDebug() << "Closed "<< filename;

    return document;
}
