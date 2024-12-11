#pragma once

#include <QWidget>
#include "ui_wordgroupui.h"
#include"all_func_definition.h"

#include"qtablewidget.h"
#include"qlayout.h"
#include"qstackedwidget.h"

class WordGroupUI : public QWidget
{
	Q_OBJECT

public:
	WordGroupUI(QWidget *parent , QList<WordGroupSchema> wordgroups);
	~WordGroupUI();

public:
	
	void initData(QList<WordGroupSchema> wordgroups);
	void initWordGroups();

	QTableWidget* setUpWordGroupTable();
	QVBoxLayout* refreshWordGroup();

public:
	int page = 0;
	QStackedWidget* widgetWordGroups ;

	QList<QList<WordSchema>> wordgroups_words;

	QList<QList<TranslationSchema>> wordgroups_translations;
	QList<QList<PhraseSchema>> wordgroups_phrases;

private:
	Ui::WordGroupUI ui;
};
