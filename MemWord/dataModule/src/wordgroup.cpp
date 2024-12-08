#include"wordgroup.h"
#include"qdebug.h"

WordGroup::WordGroup() {
	this->wordgroupTag = NULL;
	this->note = NULL;
	this->sentenceReference = NULL;
	this->wordgroupMark = false;

	this->sentences;
	this->words;

	sentences.append(Sentence());
}

void WordGroup::display() {
	qDebug() << "wordgroupTag: " << wordgroupTag;
	qDebug() << "wordgroupMark" << wordgroupMark;
	qDebug() << "sentenceReference" << sentenceReference;
	qDebug() << "note" << note;

	for (auto i : words) {
		i.display();
	}
	for (auto i : sentences) {
		i.display();
	}
}
