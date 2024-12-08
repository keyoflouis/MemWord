#pragma once

#include <QWidget>
#include "all_func_definition.h"
#include "ui_bookui.h"
#include"qlayout.h"
class BookUI : public QWidget
{
	Q_OBJECT

public:
	BookUI(QWidget *parent,BookSchema bookschema );
	~BookUI();



private:
	Ui::BookUI ui;
};
