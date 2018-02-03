INCLUDEPATH += ../src/test
INCLUDEPATH += ../src/main

SOURCES += \
        ../src/test/tst_main.cpp \
        ../src/test/tst_deckloader.cpp \

HEADERS += \
        ../src/test/tst_deckloader.h \

DEFINES += SRCDIR=\\\"$$PWD/\\\"


HEADERS += \
        ../src/main/mainwindow.h \
        ../src/main/examtab.h \
        ../src/main/exammainbox.h \
        ../src/main/flashcard.h \
        ../src/main/deckloader.h \
        ../src/main/deck.h \
        ../src/main/deckselectiontab.h \
        ../src/main/decksearcher.h \
        ../src/main/centralwidget.h \
        ../src/main/tabselector.h \
        ../src/main/decksearchbar.h \
        ../src/main/deckscrolllist.h \
        ../src/main/deckscrolllistentry.h \
        ../src/main/deckeditortab.h \
        ../src/main/wordsearcher.h \
        ../src/main/wordeditor.h \
        ../src/main/deckeditorsavebar.h \
        ../src/main/wordscrolllist.h \
        ../src/main/wordscrolllistentry.h \
        ../src/main/wordsearcherbar.h \
        ../src/main/wordeditorscrolllist.h \
        ../src/main/keylanguageselector.h \
        ../src/main/deckoptionspanel.h \
        ../src/main/wordeditorbuttonbar.h \

LIBS += \
        ../obj/main/mainwindow.o \
        ../obj/main/examtab.o \
        ../obj/main/exammainbox.o \
        ../obj/main/deckloader.o \
        ../obj/main/deckselectiontab.o \
        ../obj/main/decksearcher.o \
        ../obj/main/centralwidget.o \
        ../obj/main/tabselector.o \
        ../obj/main/decksearchbar.o \
        ../obj/main/deckscrolllist.o \
        ../obj/main/deckscrolllistentry.o \
        ../obj/main/deckeditortab.o \
        ../obj/main/wordsearcher.o \
        ../obj/main/wordeditor.o \
        ../obj/main/deckeditorsavebar.o\
        ../obj/main/wordscrolllist.o \
        ../obj/main/wordscrolllistentry.o \
        ../obj/main/wordsearcherbar.o \
        ../obj/main/wordeditorscrolllist.o \
        ../obj/main/keylanguageselector.o \
        ../obj/main/deck.o \
        ../obj/main/deckoptionspanel.o \
        ../obj/main/wordeditorbuttonbar.o \
