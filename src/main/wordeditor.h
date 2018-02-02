#ifndef WORDEDITOR_H
#define WORDEDITOR_H

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QSize>
#include<QScrollArea>
#include<QDialog>

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
    void AddLanguageButtonPressed();

public slots:
    void changeToSaveButton()                   { alternatingButton->setText("Save");
                                                  saveMode = true; }
    void setLanguageEditMode(bool flag);

private:
    QHBoxLayout *mainLayout;
    WordEditorButtonBarButton *newCardButton;
    WordEditorButtonBarButton *alternatingButton;
    WordEditorButtonBarButton *addLanguageButton;
    WordEditorButtonBarButton *finishedLanguageAddingButton;

    bool saveMode;
    bool languageEditMode;
};

class AddLanguageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit
    AddLanguageDialog(QWidget *parent);

    QSize sizeHint() const override;
    const QString& getLanguage()            { return enteredLanguage; }

private:
    QGridLayout *mainLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit *langLineEdit;
    QString enteredLanguage;
};

class WordEditor : public QWidget
{
    Q_OBJECT
public:
    explicit WordEditor(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void setFlashcard(int index, const Flashcard& card);
    void InitWithDeck(const Deck& deck);
    QStringList getLanguages()              { return scrollList->getLanguages(); }
signals:
    void addCardPressedWithCard(const Flashcard& card);
    void saveCardPressedWithCard(int index,
                                 const Flashcard& card);

    void cardLoaded();
    void changedLanguageEditMode(bool flag);

public slots:
    void PromptToAddLanguageToScrollList();

private:
    QVBoxLayout *mainLayout;

    WordEditorScrollList *scrollList;
    WordEditorButtonBar *bottomButtonBar;

    int loadedCardIndex;
};

#endif // WORDEDITOR_H
