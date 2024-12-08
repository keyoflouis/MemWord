#include"word.h"
#include"qdebug.h"

 Word::Word() {
	this->wordContext = NULL;
	this->wordMark = NULL;
}

 void Word::display() {
	qDebug() << "wordContext" << wordContext;
	qDebug() << "wordMark" << wordMark;

	for (auto i : wordTranslation) {
		i.display();
	}

	for (auto i : wordPhrase) {
		i.display();
	}
}
