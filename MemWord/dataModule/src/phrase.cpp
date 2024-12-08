#include"phrase.h"
#include"qdebug.h"

 Phrase::Phrase() {
	this->phraseContext = NULL;
	this->phraseTranslation = NULL;
}

void Phrase::display() {
	qDebug() << "phraseContext" << this->phraseContext;
	qDebug() << "phraseTranslation" << this->phraseTranslation;
}
