#include"orgschemadata.h"
#include"all_func_definition.h"

wordgroup_data::wordgroup_data(WordGroupSchema group)
{
	this->note = group.note;
	this->wordgroupMark = group.wordgroupMark;
	this->sentencReference = group.sentenceReference;
	this->wordgroupTag = group.wordgroupTag;
	this->bookId = group.bookId;
	this->wordgroupId = group.wordgroupId;

	this->sentences = findAGroupOfSentences(group.wordgroupId);
	QList<WordSchema> temp_words = findAGroupOfWords(group.wordgroupId);

	for (WordSchema word : temp_words) {
		word_data temp(word);
		this->words.append(temp);
	}
}

wordgroup_data::wordgroup_data(const wordgroup_data& other)
{
	this->bookId = other.bookId;
	this->note = other.note;

	this->wordgroupId = other.wordgroupId;
	this->sentences = other.sentences;
	this->sentencReference = other.sentencReference;

	this->wordgroupMark = other.wordgroupMark;

	this->wordgroupTag = other.wordgroupTag;
	this->words = other.words;

}

wordgroup_data::~wordgroup_data()
{
}

void wordgroup_data::updateAndDeposite()
{


}





word_data::word_data(WordSchema word)
{
	this->word = word;
	this->phases = findAWordPhrase(word.wordId);
	this->trans = findAWordTranslation(word.wordId);
}
