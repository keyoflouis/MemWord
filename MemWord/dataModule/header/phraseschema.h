#pragma once
#include"qstring.h"

class PhraseSchema {
public:
	int wordId;
	int phraseId;

	QString phraseContext;
	QString phraseTranslation;

	PhraseSchema();
};