#pragma once

#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include "ui_memword.h"

class MemWord : public QMainWindow
{
    Q_OBJECT

public:
    MemWord(QWidget *parent = nullptr);
    ~MemWord();

    QGridLayout* fileTabLayOut;
    QGridLayout* bookTabLayOut;

    QGridLayout* reFreshFileTab();
    QGridLayout* reFreshBookTab();

private:
    Ui::MemWordClass ui;
};
