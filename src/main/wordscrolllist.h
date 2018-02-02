#ifndef WORDSCROLLLIST_H
#define WORDSCROLLLIST_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPaintEvent>

#include "flashcard.h"
#include"wordscrolllistentry.h"

class WordScrollList : public QWidget
{
    Q_OBJECT
public:
    explicit WordScrollList(QWidget *parent = nullptr);

    void clear();
    void addEntry(const Flashcard& card);

signals:
    void EntrySelectedAt(int index);
    void DeleteButtonPressedForEntryAt(int index);

public slots:
    void searchFor(const QString& text);

private:

    QVBoxLayout *mainLayout;
    QList<WordScrollListEntry *> entries;
};

#endif // WORDSCROLLLIST_H
