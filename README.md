# What is this?

This project is meant to develop a Flashcard manager using Qt5.10.
It takes .deck files which are JSON documents formatted in a specific way.
These can be created by hand in the Deck Editor or imported from CSV with minor modifications

# Current state

**Release-v0.1.1:**
  * Load decks from ./decks
  * Create decks in Deck Editor by hand
  * Create decks from CSV files
  * Select decks in the Deck Selector
  * Start an exam with the decks selected in Deck Selector
  * Select the key language (this determines which word is shown first)
  * Hotkeys:
     - Right arrow - Next card
     - Up arrow - Reveal card
  
**To do:**
  * Export to CSV
  * Decks with same languages but different order be compatible
  * Statistics tab
  * Making the UI more pretty
  * Finish the layout
  
Release versions come with pre-packaged decks, this is a list of decks in the latest version

**Available decks:**
  * HSK 1-6

# How can I use this

You can either build from source or download one of the [releases](https://github.com/plaktos/CuteCards/releases).

# How do I build this?

## Get the Qt sources

You need the original Qt libraries to build this project.

* Get the Qt sources at: [Sources](http://download.qt.io/official_releases/qt/5.10/5.10.0/single/)
* Or get the Qt Editor: [Qt Editor](https://www.qt.io/download-qt-installer)

## To build

Open the CuteCards.pro file in Qt Editor.
Configure and then build it.

## Qmake

Or you can choose to build the project with qmake
You may have to change the variables `QMAKESPEC` and `PATH`. See [qmake Variables](http://doc.qt.io/qt-5/qmake-variable-reference.html) for details.

`qmake -makefile <PATH_TO_PRO_FILE>/CuteCards.pro`

`make`

# Deck sources

List of sources for the pre-packaged .deck files:
  * HSK 1-6 converted, with minor modifications from csv files: [gigacool/hanyu-shuiping-kaoshi](https://github.com/gigacool/hanyu-shuiping-kaoshi)

# License

This project made public under the terms of GNU GPL, see LICENSE for details.
More at [gnu.org/licenses/gpl-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)
