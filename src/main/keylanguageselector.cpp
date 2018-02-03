#include "keylanguageselector.h"

KeyLanguageSelector::KeyLanguageSelector(QWidget *parent)
    : QWidget(parent),
      langLabelFont(QLabel().font())
{
    langLabelFont.setPointSize(langLabelFont.pointSize() + 4);

    mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addSpacing(1);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);

    setPalette(pal);
    setAutoFillBackground(true);
    setLayout(mainLayout);
}

void
KeyLanguageSelector::clear(){
    for(auto label : langLabels)
        delete label;
    for(auto rbutt : radioButtons)
        delete rbutt;

    langLabels.clear();
    radioButtons.clear();
}

void
KeyLanguageSelector::addLanguage(const QString &lang){
    QLabel *langLabel = new QLabel(lang);
    QRadioButton *langButton = new QRadioButton;

    langLabel->setFont(langLabelFont);

    langLabels.append(langLabel);
    radioButtons.append(langButton);
    mainLayout->addWidget(langLabel);
    mainLayout->addWidget(langButton);

    if(radioButtons.size() == 1)
        langButton->setChecked(true);
}

int
KeyLanguageSelector::getKeyLanguageIndex(){
    for(int i = 0; i < radioButtons.size(); ++i){
        if(radioButtons[i]->isChecked() == true)
            return i;
    }
}
