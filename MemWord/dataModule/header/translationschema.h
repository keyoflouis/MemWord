#pragma once

#include"qstring.h"

class TranslationSchema {
public:
	int wordId;
	int translationId;

	QString type;
	QString translationContext;

	TranslationSchema();
};