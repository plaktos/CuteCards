#ifndef WORDSEARCHERBAR_H
#define WORDSEARCHERBAR_H

#include <QWidget>
#include<QLineEdit>
#include<QTimer>

class WordSearcherBar : public QLineEdit
{
    Q_OBJECT
public:
    WordSearcherBar(QWidget* parent = nullptr);

signals:
    void needSearchFor(const QString& text);

protected:
    void mousePressEvent(QMouseEvent *e) override;

private:
    QTimer *searchTimer;

};

#endif // WORDSEARCHERBAR_H
