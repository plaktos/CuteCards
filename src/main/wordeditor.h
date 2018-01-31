#ifndef WORDEDITOR_H
#define WORDEDITOR_H

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QSize>
#include<QScrollArea>

#include"deck.h"
#include"wordeditorscrolllist.h"

class WordEditorButtonBarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit
    WordEditorButtonBarButton(const QString& text,
                              QWidget *parent = nullptr);

    QSize sizeHint() const override;

};

class WordEditorButtonBar : public QWidget
{
    Q_OBJECT
public:
    explicit
    WordEditorButtonBar(QWidget* parent = nullptr);

    bool isInSaveMode()                         { return saveMode; }
signals:
    void NewCardButtonPressed();
    void SaveButtonPressed();
    void AddButtonPressed();

public slots:
    void changeToSaveButton()                   { alternatingButton->setText("Save");
                                                  saveMode = true; }

private:
    QHBoxLayout *mainLayout;
    QPushButton *newCardButton;
    QPushButton *alternatingButton;

    bool saveMode;
};

class WordEditor : public QWidget
{
    Q_OBJECT
public:
    explicit WordEditor(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void setFlashcard(int index, const Flashcard& card);
    void InitWithDeck(const Deck& deck);
signals:
    void addCardPressedWithCard(const Flashcard& card);
    void saveCardPressedWithCard(int index,
                                 const Flashcard& card);

    void cardLoaded();

public slots:

private:
    QVBoxLayout *mainLayout;

    WordEditorScrollList *scrollList;
    WordEditorButtonBar *bottomButtonBar;

    int loadedCardIndex;
};

#endif // WORDEDITOR_H
