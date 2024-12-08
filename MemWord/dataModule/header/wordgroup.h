#pragma once

#include"qstring.h"


#include"word.h"
#include"sentence.h"

class WordGroup {
public:
	QString wordgroupTag;
	bool wordgroupMark;
	QString sentenceReference;
	QString note;

	QList<Word> words;
	QList<Sentence> sentences;

	WordGroup();

	void display();
};
