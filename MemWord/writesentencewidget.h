#pragma once

#include <QWidget>
#include "ui_writesentencewidget.h"
#include"orgschemadata.h"


class WriteSentenceWidget : public QWidget
{
	Q_OBJECT

public:
	WriteSentenceWidget(QWidget *parent , wordgroup_data& agroupuidata);
	~WriteSentenceWidget();

private:
	Ui::WriteSentenceWidget ui;
};
