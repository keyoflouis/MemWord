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
	SelectWordWidget* the_select_ui = initSelectUI(agroupuidata);
	WriteSentenceWidget* the_write_ui = initeWriteSentenceUI(agroupuidata);

	aset->addWidget(the_select_ui);
	aset->addWidget(the_write_ui);
	aset->setCurrentIndex(0);

	connect(the_select_ui, &SelectWordWidget::refreshData, the_write_ui, &WriteSentenceWidget::onRefresh);
	connect(the_write_ui, &WriteSentenceWidget::refreshData, the_select_ui, &SelectWordWidget::onRefresh);

	QHBoxLayout* buts = new QHBoxLayout();
	QPushButton* store = new QPushButton();
	QPushButton* nextPage = new QPushButton();
	QPushButton* beforePage = new QPushButton();
	store->setText("store");

	nextPage->setText("next step");
	beforePage->setText("before step");
	buts->addWidget(beforePage);
	buts->addWidget(nextPage);

	layout->addWidget(store);
	layout->addWidget(aset);
	layout->addItem(buts);
	
	connect(nextPage, &QPushButton::clicked, this, [=]() {
		
		qDebug() << "clicked";
		if (aset->currentIndex() == 1) {

		}
		else
		{
			the_select_ui->emiteRefreshData();
			aset->setCurrentIndex(1);
		}
		
		});
	connect(beforePage, &QPushButton::clicked, this, [=]() {

		qDebug() << "clicked";
		if (aset->currentIndex() == 0) {

		}
		else
		{
			the_write_ui->emiterefreshData();
			aset->setCurrentIndex(0);
		}

		});

	connect(store, &QPushButton::clicked, this, [=] {
		WordGroupSchema dep = convertAGroupBack(the_select_ui->agroupuidata);
		updateAGroup(dep);
		for (auto &i: the_select_ui->agroupuidata.sentences) {
			updateASentence(i);
		}
		for (auto& word_data : the_select_ui->agroupuidata.words) {
			updateAWord(word_data.word);
		}

		});


	setLayout(layout);

}

LearnWordGroupWidget::~LearnWordGroupWidget()
{
}
