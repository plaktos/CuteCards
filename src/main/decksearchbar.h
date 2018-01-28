#ifndef DECKSEARCHBAR_H
#define DECKSEARCHBAR_H

/*
 * To be implemented, currently just a QLineEdit
 *
*/

#include <QLineEdit>
#include<QMouseEvent>
#include<QFocusEvent>

class DeckSearchBar : public QLineEdit
{
public:
    DeckSearchBar(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;

private:

};

#endif // DECKSEARCHBAR_H
