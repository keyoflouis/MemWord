#include"sentence.h"
#include"qdebug.h"

Sentence::Sentence() {
	this->sentenceContext = "write your para";
}

void Sentence::display() {
	qDebug() << "sentenceContext:" << sentenceContext;
}
