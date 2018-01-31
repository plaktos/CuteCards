#ifndef DECKEDITORSAVEBAR_H
#define DECKEDITORSAVEBAR_H

#include <QWidget>
#include<QHBoxLayout>
#include<QPushButton>

class DeckEditorSaveBarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit
    DeckEditorSaveBarButton(const QString& text,
                            QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class DeckEditorSaveBar : public QWidget
{
    Q_OBJECT
public:
    explicit DeckEditorSaveBar(QWidget *parent = nullptr);

signals:
    void saveButtonPressed();
    void cancelButtonPressed();

public slots:

private:
    QVBoxLayout *mainLayout;
    DeckEditorSaveBarButton *saveButton;
    DeckEditorSaveBarButton *cancelButton;
};

#endif // DECKEDITORSAVEBAR_H
