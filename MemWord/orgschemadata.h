#pragma once
#include"all_func_definition.h"


class word_data {
public:
	WordSchema word;
	QList<TranslationSchema> trans;
	QList<PhraseSchema> phases;

	word_data(WordSchema);
};


class wordgroup_data
{
public:
	QList<word_data> words;
	QList<SentenceSchema> sentences;

public:
	wordgroup_data() = default;
	wordgroup_data(WordGroupSchema group);
	~wordgroup_data();

private:

};

