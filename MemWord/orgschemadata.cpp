#include"orgschemadata.h"
#include"all_func_definition.h"

QList<wordgroup_data> convertTo(QList<WordGroupSchema> wordgroups) {
	QList<wordgroup_data> datas_wordgroupui;

	for (WordGroupSchema& item : wordgroups) {
		wordgroup_data agroup(item);
		datas_wordgroupui.append(agroup);
	}
	return datas_wordgroupui;
}

QList<WordGroupSchema> convertBack(QList<wordgroup_data> datas_wordgroupui) {
	return QList<WordGroupSchema>();
}

WordGroupSchema convertAGroupBack(wordgroup_data wdata) {

	WordGroupSchema wordgroup;
	wordgroup.bookId= wdata.bookId;
	wordgroup.note = wdata.note;
	wordgroup.sentenceReference = wdata.sentencReference;
	wordgroup.wordgroupId = wdata.wordgroupId;
	wordgroup.wordgroupMark = wdata.wordgroupMark;
	wordgroup.wordgroupTag = wdata.wordgroupTag;

	return wordgroup;
}



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
