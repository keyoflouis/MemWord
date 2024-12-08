#pragma once

#include <QWidget>
#include "ui_wordgroupui.h"

#include"all_func_definition.h"

class WordGroupUI : public QWidget
{
	Q_OBJECT

public:
	WordGroupUI(QWidget *parent , QList<WordGroupSchema> wordgroups);
	~WordGroupUI();

private:
	Ui::WordGroupUI ui;
};
