#include "writesentencewidget.h"

WriteSentenceWidget::WriteSentenceWidget(QWidget *parent , wordgroup_data& agroupuidata)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.wordlist->setColumnCount(2);
	ui.wordlist->setRowCount(agroupuidata.words.size());
	ui.wordlist->setHorizontalHeaderLabels({ "word_context" ,"translation_context"});

	int row = 0;
	for (word_data wd : agroupuidata.words) {
		QString showtranslation;
		for (auto tran : wd.trans) {
			if (tran.wordId == wd.word.wordId) {
				showtranslation += (QString)tran.type + " " + tran.translationContext + " ";
			}
		}

		ui.wordlist->setItem(row, 0, new QTableWidgetItem(wd.word.wordContext));
		ui.wordlist->setItem(row, 1, new QTableWidgetItem(showtranslation));

		row++;
	}

}

WriteSentenceWidget::~WriteSentenceWidget()
{
}
