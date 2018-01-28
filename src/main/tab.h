#ifndef TAB_H
#define TAB_H

#include <QSize>
#include<QWidget>

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit
    Tab(QWidget *parent = nullptr)
        : QWidget(parent) {}

    virtual ~Tab() {}

    virtual
    QSize sizeHint() const = 0;

private:

};

#endif // TAB_H
