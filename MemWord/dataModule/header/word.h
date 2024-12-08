#pragma once
#include"qstring.h"
#include"qlist.h"

#include"translation.h"
#include"phrase.h"

class Word {
public:
	QString wordContext;

	QList<Translation> wordTranslation;
	QList<Phrase> wordPhrase;
	bool wordMark;

	Word();

	void display();
};
