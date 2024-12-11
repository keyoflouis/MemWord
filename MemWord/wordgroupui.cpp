#include "wordgroupui.h"

#include"qstackedwidget.h"
#include"qcheckbox.h"
#include"qpushbutton.h"
#include"qtablewidget.h"
#include"qlayout.h"

void WordGroupUI:: initData(QList<WordGroupSchema> wordgroups) {
	for (WordGroupSchema& item : wordgroups) {
		QList<WordSchema> agroupof_word = findAGroupOfWords(item.wordgroupId);

		for (WordSchema& word : agroupof_word) {
			QList<TranslationSchema> agroupof_translation = findAWordTranslation(word.wordId);
			QList<PhraseSchema> agroupof_phrase = findAWordPhrase(word.wordId);
			wordgroups_phrases.append(agroupof_phrase);
			wordgroups_translations.append(agroupof_translation);
		}
		wordgroups_words.append(agroupof_word);
	}

}

void WordGroupUI::initWordGroups()
{
	widgetWordGroups = new QStackedWidget();
	for (page = 0; page < wordgroups_words.size();page++) {
		widgetWordGroups->addWidget(setUpWordGroupTable());
	}
	widgetWordGroups->setCurrentIndex(0);
}

QTableWidget* WordGroupUI::setUpWordGroupTable()
{
	QTableWidget* wordsview = new QTableWidget();
	int row = 0;

	wordsview->setColumnCount(3);
	wordsview->setRowCount(wordgroups_words[page].size());
	wordsview->setHorizontalHeaderLabels({ "word_context" ,"translation_context","word_mark" });

	for(WordSchema& word : wordgroups_words[page]) {

		QString showtranslation;
		for (QList<TranslationSchema>& item : wordgroups_translations) {
			for (TranslationSchema& i : item) {
				if (i.wordId == word.wordId) {
					showtranslation += (QString)i.type + " " + i.translationContext + "  ";
				}
			}
		}

		wordsview->setItem(row, 0, new QTableWidgetItem(word.wordContext));
		wordsview->setItem(row, 1, new QTableWidgetItem(" "));

		QCheckBox* checkword = new QCheckBox();
		wordsview->setCellWidget(row, 2, checkword);

		connect(checkword, &QCheckBox::stateChanged, this, [=](int state) {
			//wordsview->setRowHidden(row, state == Qt::Unchecked);
			QTableWidgetItem* thetran = wordsview->item(row, 1);
			if (state == Qt::Unchecked) {
				wordsview->item(row, 1)->setText("");
			}
			else
			{
				wordsview->item(row, 1)->setText(QString("%1").arg(showtranslation));
			}

			});

		row++;
	}
	

	return wordsview;
}

QVBoxLayout* WordGroupUI::refreshWordGroup()
{
	return nullptr;
}



WordGroupUI::WordGroupUI(QWidget *parent ,QList<WordGroupSchema> wordgroups )
	: QWidget(parent)
{
	ui.setupUi(this);
	initData(wordgroups);
	initWordGroups();
	page = 0;

	QVBoxLayout* wordgroupui_LayOut = new QVBoxLayout();

	QHBoxLayout* buts = new QHBoxLayout();
	QPushButton* nextGroup = new QPushButton();
	nextGroup->setText("next ");
	QPushButton* beforeGroup = new QPushButton();
	beforeGroup->setText("back");

	connect(nextGroup, &QPushButton::clicked, this, [&]() {
		if (page <widgetWordGroups->count()-1) {
			page++;
			widgetWordGroups->setCurrentIndex(page);
		}
		else
		{
			//nextGroup->setText("store");
		}
		});

	connect(beforeGroup, &QPushButton::clicked, this, [&]() {
		if (page>0) {
			page--;
			widgetWordGroups->setCurrentIndex(page);
		}
		else
		{
			this->close();
		}
		
		});

	buts->addWidget(beforeGroup);
	buts->addWidget(nextGroup);
	wordgroupui_LayOut->addWidget(this->widgetWordGroups);
	wordgroupui_LayOut->addItem(buts);

	setMinimumSize(800, 600);
	setLayout(wordgroupui_LayOut);
}

WordGroupUI::~WordGroupUI()
{
}
