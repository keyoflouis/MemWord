#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_memword.h"

class MemWord : public QMainWindow
{
    Q_OBJECT

public:
    MemWord(QWidget *parent = nullptr);
    ~MemWord();

private:
    Ui::MemWordClass ui;
};
