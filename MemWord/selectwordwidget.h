#pragma once

#include <QWidget>
#include "ui_selectwordwidget.h"
#include"orgschemadata.h"


class SelectWordWidget : public QWidget
{
	Q_OBJECT
public:
	wordgroup_data agroupuidata;

public:
	SelectWordWidget(QWidget *parent , wordgroup_data agroupuidata);
	~SelectWordWidget();

public:
	void Refresh();
	void emiteRefreshData();
	void handleCheckBoxStateChange(int state, int row, const word_data& wd);

public slots:
	void onRefresh(wordgroup_data agroupuidata);

public:
signals:
	void refreshData(wordgroup_data agroupuidata);

private:
	Ui::SelectWordWidget ui;
};
