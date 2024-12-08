#include "wordgroupui.h"

#include"qpushbutton.h"
#include"qtablewidget.h"
#include"qlayout.h"

WordGroupUI::WordGroupUI(QWidget *parent ,QList<WordGroupSchema> wordgroups )
	: QWidget(parent)
{
	ui.setupUi(this);

	//QList<QList<WordSchema>> wordgroups_words;
	//QList<QList<TranslationSchema>> wordgroups_translations;
	//QList<QList<PhraseSchema>> wordgroups_phrases;
	//
	//for (WordGroupSchema &item:wordgroups) {
	//	QList<WordSchema> agroupof_word = findAGroupOfWords(item.wordgroupId); // a group of word
	//	for (WordSchema & word : agroupof_word) {
	//		QList<TranslationSchema> agroupof_translation = findAWordTranslation(word.wordId);
	//		QList<PhraseSchema> agroupof_phrase = findAWordPhrase(word.wordId);
	//		wordgroups_phrases.append(agroupof_phrase);
	//		wordgroups_translations.append(agroupof_translation);
	//	}
	//	wordgroups_words.append(agroupof_word);
	//}
	//
	//
	//
	//QVBoxLayout* wordgroupuiLayOut = new QVBoxLayout();
	//QTableWidget* wordsview = new QTableWidget();
	//
	//
	//int page = 0;
	//
	//int row = 0;
	//wordgroups_words[page];
	//wordsview->setHorizontalHeaderLabels({ "word_context" ,"translation_context","word_mark"});
	//
	//for(WordSchema& word : wordgroups_words[page]) {
	//	word.wordId;
	//	word.wordContext;
	//	word.wordgroupId;
	//	word.wordMark;
	//
	//	QString showtranslation;
	//	for (QList<TranslationSchema>& item :wordgroups_translations) {
	//		for (TranslationSchema& i : item) {
	//			if (i.wordId == word.wordId) {
	//				showtranslation += i.translationContext + "  ";
	//			}
	//		}
	//	}
	//
	//	wordsview->setItem(row, 0, new QTableWidgetItem(word.wordContext));
	//	wordsview->setItem(row, 1, new QTableWidgetItem(showtranslation));
	//	wordsview->setItem(row, 2, new QTableWidgetItem(word.wordMark));
	//	row++;
	//}
	//
	//
	//
	//
	//QHBoxLayout* buts = new QHBoxLayout();
	//QPushButton* nextGroup = new QPushButton();
	//QPushButton* beforeGroup = new QPushButton();
	//
	//connect(nextGroup, &QPushButton::clicked, this, [=]() {
	//	
	//	});
	//connect(beforeGroup, &QPushButton::clicked, this, [=]() {
	//
	//	});
	//
	//wordgroupuiLayOut->addWidget(wordsview);
	//setLayout(wordgroupuiLayOut);
}

WordGroupUI::~WordGroupUI()
{
}
