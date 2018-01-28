#ifndef DECKSCROLLLISTENTRY_H
#define DECKSCROLLLISTENTRY_H

#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>

class DeckScrollListEntry : public QWidget
{
    Q_OBJECT
public:
    explicit
    DeckScrollListEntry(const QString& title,
                        int index,
                        QWidget *parent = nullptr);

signals:
    void EditButtonPressed(const int &index);

private:
    void SendSignalEditButtonPressed()                      { emit EditButtonPressed(id); }
    QHBoxLayout *mainLayout;
    QLabel *titleLabel;
    QPushButton *editButton;
    int id;
};

#endif // DECKSCROLLLISTENTRY_H
