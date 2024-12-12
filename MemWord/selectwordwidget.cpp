#include "selectwordwidget.h"

#include"qtablewidget.h"
#include"qcheckbox.h"



SelectWordWidget::SelectWordWidget(QWidget *parent , wordgroup_data& agroupuidata)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	ui.wordlist->setColumnCount(3);
	ui.wordlist->setRowCount(agroupuidata.words.size());
	ui.wordlist->setHorizontalHeaderLabels({ "word_context" ,"translation_context","word_mark" });

	int row = 0;
	for (word_data wd : agroupuidata.words) {
		QString showtranslation;
		for (auto tran : wd.trans) {
			if (tran.wordId == wd.word.wordId) {
				showtranslation += (QString)tran.type + " " + tran.translationContext + " ";
			}
		}

		ui.wordlist->setItem(row, 0,new QTableWidgetItem(wd.word.wordContext));
		ui.wordlist->setItem(row, 1, new QTableWidgetItem(" "));

		QCheckBox* checkword = new QCheckBox();
		ui.wordlist->setCellWidget(row, 2, checkword);

		connect(checkword, &QCheckBox::stateChanged, this, [=](int state) {
			if (state == Qt::Unchecked) {
				ui.wordlist->item(row, 1)->setText(" ");
			}
			else
			{
				ui.wordlist->item(row, 1)->setText(showtranslation);
			}

			});



		row++;
	}


}

SelectWordWidget::~SelectWordWidget()
{
}
