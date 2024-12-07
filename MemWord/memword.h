#pragma once

#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include "ui_memword.h"
#include"qsqlquery.h"
#include"qsqldatabase.h"
#include"qsqlerror.h"

class MemWord : public QMainWindow
{
    Q_OBJECT

public:
    MemWord(QWidget *parent = nullptr);
    ~MemWord();

    QString dbpath = "C:\\Users\\28063\\Desktop\\Mem_version3\\MemWord\\DB\\MemWord.db";
    QSqlDatabase database;

    QGridLayout* fileTabLayOut;
    QGridLayout* bookTabLayOut;

    QGridLayout* reFreshFileTab();
    QGridLayout* reFreshBookTab();

private:
    Ui::MemWordClass ui;
};
