#pragma once

#include <QWidget>
#include "ui_wordwidget.h"

class wordWidget : public QWidget
{
	Q_OBJECT

public:
	wordWidget(QWidget *parent = nullptr);
	~wordWidget();

private:
	Ui::wordWidget ui;
};
