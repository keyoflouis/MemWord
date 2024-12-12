#include"orgschemadata.h"

wordgroup_data::wordgroup_data(WordGroupSchema group)
{
	this->sentences;
	this->sentences = findAGroupOfSentences(group.wordgroupId);
	QList<WordSchema> temp_words = findAGroupOfWords(group.wordgroupId);

	for (WordSchema word : temp_words) {
		word_data temp(word);
		this->words.append(temp);
	}
}

wordgroup_data::~wordgroup_data()
{
}





word_data::word_data(WordSchema word)
{
	this->word = word;
	this->phases = findAWordPhrase(word.wordId);
	this->trans = findAWordTranslation(word.wordId);
}
