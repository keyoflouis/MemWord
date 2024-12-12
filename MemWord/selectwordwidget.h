#pragma once

#include <QWidget>
#include "ui_selectwordwidget.h"
#include"orgschemadata.h"


class SelectWordWidget : public QWidget
{
	Q_OBJECT

public:
	SelectWordWidget(QWidget *parent , wordgroup_data& agroupuidata);
	~SelectWordWidget();

private:
	Ui::SelectWordWidget ui;
};
