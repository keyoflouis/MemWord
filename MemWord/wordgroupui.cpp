#include "wordgroupui.h"
#include "learnwordgroupwidget.h"

#include"qpushbutton.h"
#include"qtablewidget.h"
#include"qlayout.h"
#include"qstackedwidget.h"


// create sub widget
LearnWordGroupWidget* initeLearnWordGroupWidget(wordgroup_data agroupuidata) {

	LearnWordGroupWidget* sub_widget = new LearnWordGroupWidget(nullptr ,agroupuidata);

	return sub_widget;
}


WordGroupUI::WordGroupUI(QWidget *parent ,QList<WordGroupSchema> wordgroups )
	: QWidget(parent)
{
	ui.setupUi(this);
	initeUIData(wordgroups);

	QVBoxLayout* layout = new QVBoxLayout();
	QPushButton* nextGroup = new QPushButton();
	nextGroup->setText("Next Group");

	QStackedWidget* sub_wordgroupUI = new QStackedWidget();
	for (auto i:this->datas_wordgroupui) {
		sub_wordgroupUI->addWidget(initeLearnWordGroupWidget(i));
	}
	sub_wordgroupUI->setCurrentIndex(0);

	layout->addWidget(nextGroup);
	layout->addWidget(sub_wordgroupUI);
	setLayout(layout);
}

WordGroupUI::~WordGroupUI()
{
}

void WordGroupUI::initeUIData(QList<WordGroupSchema> wordgroups)
{
	datas_wordgroupui;

	for (WordGroupSchema& item : wordgroups) {
		wordgroup_data agroup(item);
		datas_wordgroupui.append(agroup);
	}
}
