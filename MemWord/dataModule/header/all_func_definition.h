#include"allclassheaders.h"

// file to book
////////////////////////////////////////////////////////////////////////
Book initeBook(QString path);

void insertPhrase(const Phrase& phrase, int wordId);

void insertTranslation(const Translation& translation, int wordId);

void insertWord(const Word& word, int wordgroupId);

void insertSentence(const Sentence& sentence, int wordgroupId);

void insertWordGroup(const WordGroup& wordgroup, int bookId);

void insertBook(const Book& book);

void deposit(const Book& book);


// database
/////////////////////////////////////////////////////////////////////

QByteArray loadFile(QString path);

void openDatabase(QSqlDatabase& db, const QString& dbPath);

void closeDatabase(QSqlDatabase& db);


// get data from database
//////////////////////////////////////////////////

TranslationSchema loadTranslationSchema(int wordId, int translationid);

PhraseSchema loadPhraseSchema(int wordId, int phraseId);

WordSchema loadWordSchema(int wordgroupId, int wordId);

SentenceSchema loadSentenceSchema(int wordgroupId, int sentenceId);

WordGroupSchema loadWordGroupSchema(int bookId, int wordgroupId);

BookSchema loadBookSchema(QString bookname);

QList<SentenceSchema> findAGroupOfSentences(int wordgroupId);

QList<WordSchema> findAGroupOfWords(int wordgroupId);

QList<WordGroupSchema> findAllWordGroup(int bookId);

QList<WordGroupSchema> findUnlearned(int bookId, int numb);

QList<BookSchema> allBook();



/// modify data
///////////////////////////////

bool modifyAllWordsofAWordGroup();

bool modifyAllSentencesofAWordGroup();

