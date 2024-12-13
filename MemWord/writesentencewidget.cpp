#include "writesentencewidget.h"

WriteSentenceWidget::WriteSentenceWidget(QWidget *parent , wordgroup_data agroupuidata)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.wordlist->setColumnCount(2);
	ui.wordlist->setRowCount(agroupuidata.words.size());
	ui.wordlist->setHorizontalHeaderLabels({ "word_context" ,"translation_context" });


	this->agroupuidata = agroupuidata;
	this->refresh();

}

WriteSentenceWidget::~WriteSentenceWidget()
{
}

void WriteSentenceWidget::onRefresh(wordgroup_data agroupuidata) {
	this->agroupuidata = agroupuidata;
	this->refresh();
}

void WriteSentenceWidget::refresh()
{
	ui.wordlist->clear();


	ui.note->setText(agroupuidata.note);
	ui.referencelist ->setText(agroupuidata.sentencReference);
	connect(ui.note, &QTextEdit::textChanged, this, [=]() {
		agroupuidata.note = ui.note->toPlainText();
		});
	connect(ui.referencelist, &QTextEdit::textChanged, this, [=]() {
		agroupuidata.sentencReference = ui.referencelist->toPlainText();
		});


	if (ui.writesentence->layout()!=nullptr) {
		QLayout* old = ui.writesentence->layout();
		QLayoutItem* item;

		while ((item = old->takeAt(0))!=nullptr )
		{
			delete item->widget();
			delete item;
		}
		delete old;
	}


	QVBoxLayout* sentenceLayout = new QVBoxLayout();
	for (int i = 0; i < agroupuidata.sentences.size(); ++i) {
		QTextEdit* item = new QTextEdit();
		item->setText(agroupuidata.sentences[i].sentenceContext);
		sentenceLayout->addWidget(item);

		connect(item, &QTextEdit::textChanged, this, [=]() {
			agroupuidata.sentences[i].sentenceContext = (item->toPlainText());
			});

	}
	
	ui.writesentence->setLayout(sentenceLayout);


	int row = 0;
	for (word_data wd : agroupuidata.words) {
		QString showtranslation;
		for (auto tran : wd.trans) {
			if (tran.wordId == wd.word.wordId) {
				showtranslation += (QString)tran.type + " " + tran.translationContext + " ";
			}
		}
		if (wd.word.wordMark == false) {
			ui.wordlist->setItem(row, 0, new QTableWidgetItem(wd.word.wordContext));
			ui.wordlist->setItem(row, 1, new QTableWidgetItem(showtranslation));
			row++;
		}
		
	}


}

void WriteSentenceWidget::emiterefreshData()
{
	emit refreshData(agroupuidata);
}
