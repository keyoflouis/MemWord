#include "learnwordgroupwidget.h"
#include"selectwordwidget.h"
#include"writesentencewidget.h"

#include"qlayout.h"
#include"qstackedwidget.h"
#include"qpushbutton.h"

SelectWordWidget* initSelectUI(wordgroup_data& agroupuidata) {
	SelectWordWidget* selectui = new SelectWordWidget(nullptr, agroupuidata);
	return selectui;
}

WriteSentenceWidget* initeWriteSentenceUI(wordgroup_data& agroupuidata) {
	WriteSentenceWidget* writesentui = new WriteSentenceWidget(nullptr, agroupuidata);
	return writesentui;
}

LearnWordGroupWidget::LearnWordGroupWidget(QWidget *parent , wordgroup_data agroupuidata)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	QVBoxLayout* layout = new QVBoxLayout();
	QStackedWidget* aset = new QStackedWidget();

	aset->addWidget(initSelectUI(agroupuidata));
	aset->addWidget(initeWriteSentenceUI(agroupuidata));

	aset->setCurrentIndex(0);
	layout->addWidget(aset);


	QHBoxLayout* buts = new QHBoxLayout();

	QPushButton* nextPage = new QPushButton();
	QPushButton* beforePage = new QPushButton();
	nextPage->setText("next step");
	beforePage->setText("before step");
	buts->addWidget(beforePage);
	buts->addWidget(nextPage);
	layout->addItem(buts);
	
	connect(nextPage, &QPushButton::clicked, this, [=]() {
		
		qDebug() << "clicked";
		if (aset->currentIndex() == 1) {

		}
		else
		{
			aset->setCurrentIndex(1);
		}
		
		});
	connect(beforePage, &QPushButton::clicked, this, [=]() {

		qDebug() << "clicked";
		if (aset->currentIndex() == 0) {

		}
		else
		{
			aset->setCurrentIndex(0);
		}

		});

	setLayout(layout);

}

LearnWordGroupWidget::~LearnWordGroupWidget()
{
}
