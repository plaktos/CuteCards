#ifndef CONSTDEFINES_H
#define CONSTDEFINES_H

//MainWindow variables
const static unsigned int MAINWINDOW_HINT_WIDTH = 800;
const static unsigned int MAINWINDOW_HINT_HEIGHT = 600;

//TabSelector variables
const static unsigned int CENTRAL_TABSELECTOR_HINT_WIDTH = MAINWINDOW_HINT_WIDTH;
const static unsigned int CENTRAL_TABSELECTOR_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT/8;
const static unsigned int CENTRAL_TABSELECTOR_BUTTONS_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/5;

//Exam tab variables
const static unsigned int EXAMTAB_HINT_WIDTH = MAINWINDOW_HINT_WIDTH;
const static unsigned int EXAMTAB_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT;

/*********** //ExamTab - MainBox */
const static unsigned int EXAM_MAINBOX_HINT_WIDTH = MAINWINDOW_HINT_WIDTH/2;
const static unsigned int EXAM_MAINBOX_HINT_HEIGHT = EXAM_MAINBOX_HINT_WIDTH;
const static unsigned int EXAM_MAINBOX_MIN_WIDTH = EXAM_MAINBOX_HINT_WIDTH/2;
const static unsigned int EXAM_MAINBOX_MIN_HEIGHT = EXAM_MAINBOX_MIN_WIDTH;

/*********** //ExamTab - LowerBox */
const static unsigned int EXAM_LOWERBOX_HINT_WIDTH = EXAM_MAINBOX_HINT_WIDTH;
const static unsigned int EXAM_LOWERBOX_HINT_HEIGHT = EXAM_MAINBOX_HINT_HEIGHT/3;

//Deck selection tab variables
const static unsigned int DECKSELECTIONTAB_HINT_WIDTH = MAINWINDOW_HINT_WIDTH;
const static unsigned int DECKSELECTIONTAB_HINT_HEIGHT = MAINWINDOW_HINT_HEIGHT;

#endif // CONSTDEFINES_H
