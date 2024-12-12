#pragma once

#include <QWidget>
#include "ui_learnwordgroupwidget.h"
#include"all_func_definition.h"
#include"orgschemadata.h"


class LearnWordGroupWidget : public QWidget
{
	Q_OBJECT

public:
	LearnWordGroupWidget(QWidget *parent ,wordgroup_data  );
	~LearnWordGroupWidget();

private:
	Ui::LearnWordGroupWidget ui;
};
