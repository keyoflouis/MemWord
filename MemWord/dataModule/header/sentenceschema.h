#pragma once
#include"qstring.h"

class SentenceSchema {
public:
	int wordgroupId;
	int sentenceId;

	QString sentenceContext;

	SentenceSchema();
};