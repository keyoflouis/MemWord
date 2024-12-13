#pragma once

#include <QWidget>
#include "ui_wordgroupui.h"
#include"orgschemadata.h"
#include"all_func_definition.h"

class WordGroupUI : public QWidget
{
	Q_OBJECT

public:
	WordGroupUI(QWidget *parent , QList<WordGroupSchema> wordgroups);
	~WordGroupUI();
public:
	QList<wordgroup_data> datas_wordgroupui;

private:
	void initeUIData(QList<WordGroupSchema> wordgroups);
private:
	Ui::WordGroupUI ui;
};
