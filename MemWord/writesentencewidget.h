#pragma once

#include <QWidget>
#include "ui_writesentencewidget.h"
#include"orgschemadata.h"


class WriteSentenceWidget : public QWidget
{
	Q_OBJECT
public:
	wordgroup_data agroupuidata;
public:
	WriteSentenceWidget(QWidget *parent , wordgroup_data agroupuidata);
	~WriteSentenceWidget();
	void refresh();

public slots:
	void onRefresh(wordgroup_data agroupuidata);

private:
	Ui::WriteSentenceWidget ui;
};
