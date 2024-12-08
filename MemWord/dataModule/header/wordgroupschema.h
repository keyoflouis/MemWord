#pragma once


#include"qstring.h"

class WordGroupSchema {
public:
	int bookId;
	int wordgroupId;

	QString wordgroupTag;
	QString sentenceReference;
	bool wordgroupMark;
	QString note;

	WordGroupSchema();
};