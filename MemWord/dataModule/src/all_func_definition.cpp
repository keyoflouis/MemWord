#include"qpushbutton.h"
#include"qjsonarray.h"
#include"qlist.h"
#include"qfile.h"
#include"qbytearray.h"
#include"qjsondocument.h"
#include"qjsonobject.h"
#include"qjsonvalue.h"
#include"qsqldatabase.h"
#include"qsqlquery.h"
#include"qsqlerror.h"


#include"allclassheaders.h"
#include"all_func_definition.h"

QByteArray loadFile(QString path) {
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray fileText = file.readAll();

	return fileText;
}

void openDatabase(QSqlDatabase& db, const QString& dbPath) {
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(dbPath);
	if (!db.open()) {
		qDebug() << "can't open";
	}
}

void closeDatabase(QSqlDatabase& db) {
	if (db.isOpen()) {
		db.close();
	}
}

// file to book
// orgnize group 
// 
// recursively inite
Book initeBook(QString path) {

	QByteArray file = loadFile(path);
	QJsonParseError je;
	QJsonDocument file_json = QJsonDocument::fromJson(file, &je);
	QJsonArray file_array = file_json.array();


	Book book;
	book.bookName = "newBook";
	book.bookDescription = "book for test";
	int group_size = 20;


	WordGroup temp;
	for (const QJsonValue& item : file_array) {

		Word word;
		word.wordContext = item["word"].toString();

		QJsonArray translations = item["translations"].toArray();
		for (const QJsonValue& translation : translations) {
			Translation translationData;
			translationData.translationContext = translation["translation"].toString();
			translationData.type = translation["type"].toString();
			word.wordTranslation.append(translationData);
		}


		QJsonArray phrases = item["phrases"].toArray();
		for (const QJsonValue& phrase : phrases) {
			Phrase phraseData;
			phraseData.phraseContext = phrase["phrase"].toString();
			phraseData.phraseTranslation = phrase["translation"].toString();
			word.wordPhrase.append(phraseData);
		}


		temp.words.append(word);
		if (temp.words.size() == group_size) {
			book.wordGroups.append(temp);
			temp.words.clear();
		}
	}
	if (!temp.words.isEmpty()) {
		book.wordGroups.append(temp);
	}

	//book.display();

	return book;
}

void insertPhrase(const Phrase& phrase, int wordId) {
	QSqlQuery query;

	query.prepare("INSERT INTO Phrase (word_id,phrase_context,phrase_translation) VALUES (?,?,?)");
	query.addBindValue(wordId);
	query.addBindValue(phrase.phraseContext);
	query.addBindValue(phrase.phraseTranslation);

	if (!query.exec()) {
		qDebug() << "error insert phrase";
		query.exec("ROLLBACK;");
	}
}

void insertTranslation(const Translation& translation, int wordId) {
	QSqlQuery query;
	query.prepare("INSERT INTO Translation(word_id,type,translation_context) VALUES (?,?,?)");

	query.addBindValue(wordId);
	query.addBindValue(translation.type);
	query.addBindValue(translation.translationContext);

	if (!query.exec()) {
		qDebug() << "error insert translation";
		query.exec("ROLLBACK;");
	}
}

void insertWord(const Word& word, int wordgroupId) {
	QSqlQuery query;

	query.prepare("INSERT INTO Word (wordgroup_id,word_context,word_mark) VALUES(?,?,?)");
	query.addBindValue(wordgroupId);
	query.addBindValue(word.wordContext);
	query.addBindValue(word.wordMark);

	if (!query.exec()) {
		qDebug() << "error insertWord";

	}

	int wordId = query.lastInsertId().toInt();

	if (!query.exec("BEGIN TRANSACTION;")) {
		qDebug() << "error Transaction";
	}

	for (const Translation& tran : word.wordTranslation) {
		insertTranslation(tran, wordId);
	}
	for (const Phrase& phra : word.wordPhrase) {
		insertPhrase(phra, wordId);
	}

	if (!query.exec("COMMIT;")) {
		qDebug() << "error commit";
	}
}

void insertSentence(const Sentence& sentence, int wordgroupId) {
	QSqlQuery query;

	query.prepare("INSERT INTO Sentence (wordgroup_id,sentence_context) VALUES(?,?)");
	query.addBindValue(wordgroupId);
	query.addBindValue(sentence.sentenceContext);
	if (!query.exec()) {
		qDebug() << "sentence insert error";
	}
}

void insertWordGroup(const WordGroup& wordgroup, int bookId) {
	QSqlQuery query;

	query.prepare("INSERT INTO WordGroup(book_id,wordgroup_tag,sentence_reference,wordgroup_mark,note) VALUES (?,?,?,?,?)");
	query.addBindValue(bookId);
	query.addBindValue(wordgroup.wordgroupTag);
	query.addBindValue(wordgroup.sentenceReference);
	query.addBindValue(wordgroup.wordgroupMark);
	query.addBindValue(wordgroup.note);

	if (!query.exec()) {
		qDebug() << "error WG";
	}
	int wordgroupId = query.lastInsertId().toInt();


	for (const Word& word : wordgroup.words) {
		insertWord(word, wordgroupId);
	}

	for (const Sentence& sentence : wordgroup.sentences) {
		insertSentence(sentence, wordgroupId);
	}


}

void insertBook(const Book& book) {
	QSqlQuery query;
	query.prepare("INSERT INTO Book(book_name,book_description) VALUES (?,?)");
	query.addBindValue(book.bookName);
	query.addBindValue(book.bookDescription);

	if (!query.exec()) {
		qDebug() << "error in insertBook " << query.lastError();
		return;
	}

	int bookId = query.lastInsertId().toInt();

	for (const WordGroup& wordgroup : book.wordGroups) {
		insertWordGroup(wordgroup, bookId);
	}

}

void deposit(const Book& book) {
	insertBook(book);
}

TranslationSchema loadTranslationSchema(int wordId, int translationid) {

	TranslationSchema translationschema;
	QSqlQuery query;

	query.prepare("SELECT * FROM Translation WHERE word_id = ? and translation_id =?");
	query.addBindValue(wordId);
	query.addBindValue(translationid);

	if (!query.exec()) {
		qDebug() << "error select translation ";

	}
	else
	{
		if (query.size() != 0) {
			translationschema.translationContext = query.value("translation_context").toString();
			translationschema.type = query.value("type").toString();
			translationschema.translationId = translationid;
			translationschema.wordId = wordId;
		}
	}

	return translationschema;
}

PhraseSchema loadPhraseSchema(int wordId, int phraseId) {

	PhraseSchema phrasechema;
	QSqlQuery query;
	query.prepare("SELECT * FROM Phrase WHERE phrase_id = ? and word_id =?");
	query.addBindValue(phraseId);
	query.addBindValue(wordId);

	if (!query.exec()) {
		qDebug() << "error select phrase ";
	}
	else
	{
		if (query.size() != 0) {
			phrasechema.phraseContext = query.value("phrase_context").toString();
			phrasechema.phraseTranslation = query.value("phrase_translation").toString();
			phrasechema.phraseId = phraseId;
			phrasechema.wordId = wordId;
		}
		else
		{

		}
	}



	return phrasechema;
}

WordSchema loadWordSchema(int wordgroupId, int wordId) {

	WordSchema wordschema;

	QSqlQuery query;
	query.prepare("SELECT * FROM Word WHERE wordgroup_id = ? and word_id = ?");
	query.addBindValue(wordgroupId);
	query.addBindValue(wordId);

	if (!query.exec()) {
		qDebug() << "error select word ";

	}
	else
	{
		if (query.size() != 0) {
			wordschema.wordContext = query.value("word_context").toString();
			wordschema.wordMark = query.value("word_mark").toBool();
			wordschema.wordgroupId = wordgroupId;
			wordschema.wordId = wordId;
		}
		else
		{

		}
	}


	return wordschema;
}

SentenceSchema loadSentenceSchema(int wordgroupId, int sentenceId) {

	SentenceSchema sentenceschema;
	QSqlQuery query;

	query.prepare("SELECT * FROM Sentence WHERE wordgroup_id = ? and sentence_id = ?");
	query.addBindValue(wordgroupId);
	query.addBindValue(sentenceId);

	if (!query.exec()) {
		qDebug() << "error select sentence ";
	}
	else
	{
		if (query.size() != 0) {
			sentenceschema.sentenceContext = query.value("sentence_context").toString();
			sentenceschema.sentenceId = sentenceId;
			sentenceschema.wordgroupId = wordgroupId;
		}
		else
		{

		}
	}



	return sentenceschema;
}

WordGroupSchema loadWordGroupSchema(int bookId, int wordgroupId) {

	WordGroupSchema wordgroupschema;
	QSqlQuery query;
	query.prepare("SELECT * FROM WordGroup WHERE book_id = ? AND wordgroup_id = ?");
	query.addBindValue(bookId);
	query.addBindValue(wordgroupId);

	if (!query.exec()) {
		qDebug() << "error select wordgroup";
	}
	else
	{
		if (query.size() != 0) {
			wordgroupschema.bookId = bookId;
			wordgroupschema.wordgroupId = wordgroupId;

			wordgroupschema.note = query.value("note").toString();
			wordgroupschema.sentenceReference = query.value("sentence_reference").toString();
			wordgroupschema.wordgroupTag = query.value("wordgroup_tag").toString();
			wordgroupschema.wordgroupMark = query.value("wordgroup_mark").toBool();

		}
		else
		{
			qDebug() << "no wordgroup_id :" << wordgroupId << " and book_id" << bookId;
		}
	}



	return wordgroupschema;
}

BookSchema loadBookSchema(QString bookname) {

	BookSchema bookschema;

	QSqlQuery query;
	query.prepare("SELECT * FROM Book WHERE book_name = ?");
	query.addBindValue(bookname);

	if (!query.exec()) {
		qDebug() << "error select book";
	}
	else
	{
		if (query.size() != 0) {
			bookschema.bookId = query.value("book_id").toInt();
			bookschema.bookName = query.value("book_name").toString();
			bookschema.bookDescription = query.value("book_description").toString();
		}
		else
		{
			qDebug() << "no book :" << bookname;
		}
	}


	return bookschema;
}

QList<SentenceSchema> findAGroupOfSentences(int wordgroupId) {
	QList<SentenceSchema> sentencelist;
	QSqlQuery query;

	query.prepare("SELECT * FROM Sentence WHERE wordgroup_id = ? ");
	query.addBindValue(wordgroupId);

	if (!query.exec()) {
		qDebug() << "error select sentence ";
	}
	else
	{
		while (query.next())
		{
			SentenceSchema sentencechema;
			sentencechema.sentenceContext = query.value("sentence_context").toString();
			sentencechema.sentenceId = query.value("sentence_id").toInt();
			sentencechema.wordgroupId = wordgroupId;
			sentencelist.append(sentencechema);
		}

	}

	return sentencelist;
}

QList<WordSchema> findAGroupOfWords(int wordgroupId) {

	QList<WordSchema> wordlist;

	QSqlQuery query;

	query.prepare("SELECT * FROM Word WHERE wordgroup_id = ?");
	query.addBindValue(wordgroupId);

	if (!query.exec()) {
		qDebug() << "findAGroupOfWords";
	}
	else
	{
		while (query.next())
		{
			WordSchema word;
			word.wordContext = query.value("word_context").toString();
			word.wordMark = query.value("word_mark").toBool();
			word.wordId = query.value("word_id").toInt();
			word.wordgroupId = wordgroupId;
			wordlist.append(word);
		}
	}


	return wordlist;
}

QList<PhraseSchema> findAWordPhrase(int wordId) {

	QList<PhraseSchema> phraselist;

	QSqlQuery query;
	query.prepare("SELECT * FROM Phrase WHERE word_id = ?");
	query.addBindValue(wordId);

	if (!query.exec()) {
		qDebug() << "error findAWordPhrase" << query.lastError();
	}
	else
	{
		while (query.next())
		{
			PhraseSchema phrase;
			phrase.phraseId = query.value("phrase_id").toInt();
			phrase.phraseContext = query.value("phrase_context").toString();
			phrase.phraseTranslation = query.value("phrase_translation").toString();
			phrase.wordId = wordId;
			phraselist.append(phrase);
		}
	}

	return phraselist;
}

QList<TranslationSchema> findAWordTranslation(int wordId) {
	QList<TranslationSchema> translationlist;

	QSqlQuery query;
	query.prepare("SELECT * FROM Translation WHERE word_id =?");
	query.addBindValue(wordId);

	if (!query.exec()) {
		qDebug() << "findAWordTranslation" << query.lastError();
	}
	else
	{
		while (query.next())
		{
			TranslationSchema translation;
			translation.translationId = query.value("translation_id").toInt();
			translation.translationContext = query.value("translation_context").toString();
			translation.type = query.value("type").toString();
			translation.wordId = wordId;
			translationlist.append(translation);
		}
	}
	return translationlist;
}


QList<WordGroupSchema> findAllWordGroup(int bookId) {
	QList<WordGroupSchema> group;
	QSqlQuery query;
	query.prepare("SELECT * FROM WordGroup WHERE book_id = ?;");
	query.addBindValue(bookId);

	if (!query.exec()) {
		qDebug() << "findAllWordGroup";
	}
	else {
		while (query.next())
		{
			WordGroupSchema wds;
			wds.wordgroupId = query.value("wordgroup_id").toInt();
			wds.bookId = query.value("book_id").toInt();
			wds.note = query.value("note").toString();
			wds.sentenceReference = query.value("sentence_reference").toString();
			wds.wordgroupTag = query.value("wordgroup_tag").toString();
			wds.wordgroupMark = query.value("wordgroup_mark").toBool();
			group.append(wds);
		}
	}

	return group;
}

QList<WordGroupSchema> findUnlearned(int bookId, int numb) {

	QList<WordGroupSchema> group = findAllWordGroup(bookId);
	QList<WordGroupSchema> re_group;
	for (const WordGroupSchema& item : group) {
		if (!item.wordgroupMark && numb != 0) {
			numb--;
			re_group.append(item);
		}
	}

	return re_group;
}

QList<BookSchema> allBook() {
	QSqlQuery query;
	query.prepare("SELECT * FROM Book");

	if (!query.exec()) {
		qDebug() << "erro allBook";
	}

	QList<BookSchema> books;
	while (query.next())
	{
		BookSchema book;
		book.bookId = query.value("book_id").toInt();
		book.bookName = query.value("book_name").toString();
		book.bookDescription = query.value("book_description").toString();
		books.append(book);
	}

	return books;
}




////////////////////////////
void updateAWord(WordSchema word) {
	QSqlQuery query;
	query.prepare("UPDATE Word SET word_context = ? ,word_mark = ? WHERE wordgroup_id = ? and word_id = ?");

	query.addBindValue(word.wordContext);
	query.addBindValue(word.wordMark);
	query.addBindValue(word.wordgroupId);
	query.addBindValue(word.wordId);

	if (!query.exec()) {
		qDebug() << "error updateAWord";
	}

}

void updateASentence(SentenceSchema sent) {
	QSqlQuery query;
	query.prepare("UPDATE Sentence SET sentence_context = ? WHERE sentence_id = ? and wordgroup_id = ?");

	query.addBindValue(sent.sentenceContext);
	query.addBindValue(sent.sentenceId);
	query.addBindValue(sent.wordgroupId);

	if (!query.exec()) {
		qDebug() << "error updateASentence";
	}
}

void updateAGroup(WordGroupSchema wordgroup) {
	QSqlQuery query;

	query.prepare("UPDATE WordGroup SET wordgroup_tag = ? ,sentence_reference = ? ,wordgroup_mark = ? ,note = ? WHERE wordgroup_id = ? and book_id = ?");
	query.addBindValue(wordgroup.wordgroupTag);
	query.addBindValue(wordgroup.sentenceReference);
	query.addBindValue(wordgroup.wordgroupMark);
	query.addBindValue(wordgroup.note);
	query.addBindValue(wordgroup.wordgroupId);
	query.addBindValue(wordgroup.bookId);

	if (!query.exec()) {
		qDebug() << "error updateAGroup";
	}

}