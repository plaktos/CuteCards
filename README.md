# What is this?

This project is meant to develop a Flashcard program using Qt5.10,
it reads .deck files from the res folder, which are JSON documents formatted
in a specific way.

# How do I format the .deck file

There will be an inbuilt .deck editor, that supports to/from CSV conversion.

Here is an example, taken from *test_pos.deck*, see below, for explanation
```
{
    "Properties": {
        "Title" : "Test deck (positive)",
		"Languages" : ["english","chinese","pinyin"]
    },
    "Words": [
		["apple","苹果","ping2 guo3"],
		["table","桌子","zhuo1 zi0"],
		["fire","火","huo3"]
    ]
}
```

Every .deck file should contain exactly 2 objects (aside from the root).
These are with the respective keys `Properties` and `Words`.
The JSON Object `Properties` contains information about the deck itself.
The JSON Object `Words` contains the actual JSON Array.
Inside this JSON Array are more arrays, each one corresponding to a word.
These get turned into Flashcard objects, which are read into a Deck.

Flashcards are designed this way, to provide support for languages that require more than 2 words.
Such as chinese.

# How do I build this?

## Get the Qt sources

You need the original Qt libraries to build this project.
Get the Qt sources at: [Sources](http://download.qt.io/official_releases/qt/5.10/5.10.0/single/)
alternatively get the Qt Editor: [Qt Editor](https://www.qt.io/download-qt-installer)

## To build

Open the CuteCards.pro file in **Qt Editor**.
Configure and then build it.

## Qmake

Or you can choose to build the project with **qmake**
You may have to change the variables `QMAKESPEC` and `PATH`. See [qmake Variables](http://doc.qt.io/qt-5/qmake-variable-reference.html) for details.

`qmake -makefile <PATH_TO_PRO_FILE>/CuteCards.pro`

# License

This project made public under the terms of GNU GPL, see LICENSE for details.
More at [gnu.org/licenses/gpl-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)
