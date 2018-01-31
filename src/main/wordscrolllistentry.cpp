#include "wordscrolllistentry.h"

WordScrollListEntryLabel::WordScrollListEntryLabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    QFont newfont(font());
    newfont.setPointSize(newfont.pointSize() + 4);
    setFont(newfont);
    setText(text);
    setSizePolicy(QSizePolicy::Fixed,
                  QSizePolicy::Fixed);
}

QSize
WordScrollListEntryLabel::sizeHint() const{
    return QSize(35,30);
}

WordScrollListEntryDeleteButton::WordScrollListEntryDeleteButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setSizePolicy(QSizePolicy::Fixed,
                  QSizePolicy::Fixed);
}

QSize
WordScrollListEntryDeleteButton::sizeHint() const {
    return QSize(20,20);
}

WordScrollListEntry::WordScrollListEntry(int index, QWidget *parent)
    : QWidget(parent),
      id(index)
{
    deleteButton = new WordScrollListEntryDeleteButton("D");

    mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(deleteButton);
    mainLayout->addSpacing(1);
    setLayout(mainLayout);

    connect(deleteButton, &WordScrollListEntryDeleteButton::pressed,
            [this](){
        emit DeleteButtonPressed(id);
    });
}

void
WordScrollListEntry::addWord(const QString &word){
    WordScrollListEntryLabel *label = new WordScrollListEntryLabel(word);
    mainLayout->insertWidget(mainLayout->count()-1, label);
    words.append(word);
}

void
WordScrollListEntry::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        emit selected(id);
    }
    else{
        QWidget::mousePressEvent(e);
    }
}
