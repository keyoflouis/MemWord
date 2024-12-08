#pragma once

#include"qstring.h"

class WordSchema {
public:
	int wordgroupId;
	int wordId;

	QString wordContext;
	bool wordMark;

	WordSchema();
};
