#ifndef WORDSCROLLLISTENTRY_H
#define WORDSCROLLLISTENTRY_H

#include <QWidget>
#include<QCheckBox>
#include<QHBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QFont>
#include<QMouseEvent>

class WordScrollListEntryLabel : public QLabel
{
    Q_OBJECT
public:
    explicit
    WordScrollListEntryLabel(const QString &text,
                             QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class WordScrollListEntryDeleteButton : public QPushButton
{
    Q_OBJECT
public:
    explicit
    WordScrollListEntryDeleteButton(const QString &text,
                                    QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class WordScrollListEntry : public QWidget
{
    Q_OBJECT
public:
    explicit
    WordScrollListEntry(int index,
                        QWidget *parent = nullptr);

    void addWord(const QString& word);
    QStringList getWords()                      { return words; }
    QSize sizeHint() const override             { return QSize(300,30); }
signals:
    void selected(int id);
    void DeleteButtonPressed(int id);

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QHBoxLayout *mainLayout;
    int id;
    QStringList words;
    WordScrollListEntryDeleteButton *deleteButton;

};

#endif // WORDSCROLLLISTENTRY_H
