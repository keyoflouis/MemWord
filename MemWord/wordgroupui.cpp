#include "wordgroupui.h"
#include "learnwordgroupwidget.h"

#include"qpushbutton.h"
#include"qtablewidget.h"
#include"qlayout.h"
#include"qstackedwidget.h"

void WordGroupUI::initeUIData(QList<WordGroupSchema> wordgroups)
{
	datas_wordgroupui;

	for (WordGroupSchema& item : wordgroups) {
		wordgroup_data agroup(item);
		datas_wordgroupui.append(agroup);
	}
}



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
	QHBoxLayout* buts = new QHBoxLayout();

	QPushButton* nextGroup = new QPushButton();
	QPushButton* beforeGroup = new QPushButton();
	nextGroup->setText("Next Group");
	beforeGroup->setText("before Group");
	buts->addWidget(beforeGroup);
	buts->addWidget(nextGroup);



	QStackedWidget* sub_wordgroupUI = new QStackedWidget();
	for (auto i:this->datas_wordgroupui) {
		sub_wordgroupUI->addWidget(initeLearnWordGroupWidget(i));
	}
	sub_wordgroupUI->setCurrentIndex(0);



	connect(nextGroup, &QPushButton::clicked, this, [=]() {
		if (sub_wordgroupUI->currentIndex() < sub_wordgroupUI->count()-1) {
			sub_wordgroupUI->setCurrentIndex(sub_wordgroupUI->currentIndex() + 1);
		}


		});
	connect(beforeGroup, &QPushButton::clicked, this, [=]() {
		if (sub_wordgroupUI->currentIndex() >0) {
			sub_wordgroupUI->setCurrentIndex(sub_wordgroupUI->currentIndex() - 1);
		}

		});

	layout->addItem(buts);
	layout->addWidget(sub_wordgroupUI);
	setLayout(layout);
}

WordGroupUI::~WordGroupUI()
{
}

