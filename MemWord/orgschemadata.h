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
	QString note;
	bool wordgroupMark;
	QString sentencReference;
	QString wordgroupTag;
	int bookId;
	int wordgroupId;

public:
	wordgroup_data() = default;
	wordgroup_data(WordGroupSchema group);
	wordgroup_data(const wordgroup_data& other);
	~wordgroup_data();

	void updateAndDeposite();

private:

};

