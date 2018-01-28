#ifndef DECKSCROLLLISTENTRY_H
#define DECKSCROLLLISTENTRY_H

#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
#include<QCheckBox>
#include<QSize>
#include<QSizePolicy>
#include<QPaintEvent>
#include<QPainter>
#include<QMouseEvent>

const static unsigned int DECKSCROLLISTENTRY_HINT_WIDTH = 100;
const static unsigned int DECKSCROLLISTENTRY_HINT_HEIGHT = 20;

class DeckScrollListEntry : public QWidget
{
    Q_OBJECT
public:
    explicit
    DeckScrollListEntry(const QString& title,
                        int index,
                        QWidget *parent = nullptr);

    QSize sizeHint() const override                         { return QSize(DECKSCROLLISTENTRY_HINT_WIDTH,
                                                                           DECKSCROLLISTENTRY_HINT_HEIGHT); }

    bool isSelected()                                       { return selectedCheckBox->isChecked(); }

signals:
    void EditButtonPressed(const int &index);
    void SelectedStateChanged(const int &index, const Qt::CheckState& state);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent * e) override;

private:
    void SendSignalEditButtonPressed()                      { emit EditButtonPressed(id); }
    void SendSignalSelectedStateChanged()                   { emit SelectedStateChanged(id, selectedCheckBox->checkState()); }
    QHBoxLayout *mainLayout;

    QCheckBox *selectedCheckBox;
    QLabel *titleLabel;
    QPushButton *editButton;
    int id;
};

#endif // DECKSCROLLLISTENTRY_H
