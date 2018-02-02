#ifndef KEYLANGUAGESELECTOR_H
#define KEYLANGUAGESELECTOR_H

#include <QWidget>
#include<QRadioButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QFont>

class KeyLanguageSelector : public QWidget
{
    Q_OBJECT
public:
    explicit KeyLanguageSelector(QWidget *parent = nullptr);

    void addLanguage(const QString& lang);
    void clear();

    int getKeyLanguageIndex();
signals:

public slots:

private:
    QHBoxLayout *mainLayout;
    QVector<QLabel *> langLabels;
    QVector<QRadioButton *> radioButtons;
    QFont langLabelFont;
};

#endif // KEYLANGUAGESELECTOR_H
