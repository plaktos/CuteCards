#ifndef WORDEDITORSCROLLLIST_H
#define WORDEDITORSCROLLLIST_H

#include <QWidget>
#include<QFormLayout>
#include<QString>
#include<QLabel>
#include<QLineEdit>
#include<QVector>

#include"flashcard.h"

class WordEditorScrollList : public QWidget
{
    Q_OBJECT
public:
    explicit WordEditorScrollList(QWidget *parent = nullptr);

    void clear();
    void clearValues();
    void addEditingLineForLanguage(const QString& language);
    void loadFromCard(const Flashcard& card);

    Flashcard toCard();
    QSize sizeHint() const override;

signals:

public slots:

private:
    QFormLayout *mainLayout;

    QVector<QLineEdit *> valueLines;
    QVector<QLabel *> labelLines;
};

#endif // WORDEDITORSCROLLLIST_H
