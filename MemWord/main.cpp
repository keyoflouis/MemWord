#include"qsqlquery.h"
#include"qsqldatabase.h"
#include"qjsonarray.h"
#include "memword.h"
#include <QtWidgets/QApplication>
#include"qlist.h"
#include"qfile.h"
#include"qbytearray.h"
#include"qjsondocument.h"
#include"qjsonobject.h"
#include"qjsonvalue.h"
#include"qsqlerror.h"
//  data in logic
class Translation {
public:
    QString type;
    QString translationContext;

    Translation() {
        this->type = NULL;
        this->translationContext = NULL;
    }
    void display() {
        qDebug() << "type" << this->type;
        qDebug() << "translationContext" << translationContext;
    }
};

class Phrase {
public:
    QString phraseContext;
    QString phraseTranslation;

    Phrase() {
        this->phraseContext = NULL;
        this->phraseTranslation = NULL;
    }
    void display() {
        qDebug() << "phraseContext" << this->phraseContext;
        qDebug() << "phraseTranslation" << this->phraseTranslation;
    }
};


class Word {
   public:
    QString wordContext;

    QList<Translation> wordTranslation;
    QList<Phrase> wordPhrase;
    bool wordMark;

    Word() {
        this->wordContext = NULL;
        this->wordMark = NULL;
    }

    void display() {
        qDebug() << "wordContext" << wordContext;
        qDebug() << "wordMark" << wordMark;

        for (auto i : wordTranslation) {
            i.display();
        }

        for (auto i : wordPhrase) {
            i.display();
        }
    }
};

class Sentence {
   public:
    QString sentenceContext;
    Sentence() {
        this->sentenceContext = NULL;
    }
    void display() {
        qDebug() << "sentenceContext:" << sentenceContext;
    }
};

class WordGroup {
   public:
    QString wordgroupTag;
    QString wordgroupValid;
    QString sentenceReference;
    QString note;

    QList<Word> words;
    QList<Sentence> sentences;

    WordGroup() {
        this->wordgroupTag = NULL;
        this->note = NULL;
        this->sentenceReference = NULL;
        this->wordgroupTag = NULL;
        this->wordgroupValid = NULL;

        this->sentences;
        this->words;
    }

    void display() {
        qDebug() << "wordgroupTag: " << wordgroupTag;
        qDebug() << "wordgroupValid" << wordgroupValid;
        qDebug() << "sentenceReference" << sentenceReference;
        qDebug() << "note" << note;

        for (auto i : words) {
            i.display();
        }
        for (auto i : sentences) {
            i.display();
        }
    }
};

class Book {
   public:
    QString bookName;
    QString bookDescription;

    QList<WordGroup> wordGroups;

    Book() {
        this->bookName = NULL;
        this->bookDescription = NULL;
    }

    void display() {
        qDebug() << "bookName:" << bookName;
        qDebug() << "bokDescription" << bookDescription;
        
        for (auto i : wordGroups) {
            i.display();
        }
    }
};

// id maintained by return id



QByteArray loadFile(QString path) {
    QFile file (path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray fileText = file.readAll();

    return fileText;
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
        for (const QJsonValue &translation:translations) {
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

void insertPhrase(const Phrase& phrase ,int wordId) {
    QSqlQuery query;

    query.prepare("INSERT INTO Phrase (word_id,phrase_context,phrase_translation) VALUES (?,?,?)");
    query.addBindValue(wordId);
    query.addBindValue(phrase.phraseContext);
    query.addBindValue(phrase.phraseTranslation);

    if (!query.exec()) {
        qDebug() << "error insert phrase";
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
    }
}

void insertWord(const Word& word,int wordgroupId) {
    QSqlQuery query;

    query.prepare("INSERT INTO Word (wordgroup_id,word_context,word_mark) VALUES(?,?,?)");
    query.addBindValue(wordgroupId);
    query.addBindValue(word.wordContext);
    query.addBindValue(word.wordMark);

    if (!query.exec()) {
        qDebug() << "error insertWord";
    }

    int wordId = query.lastInsertId().toInt();

    for (const Translation& tran : word.wordTranslation) {
        insertTranslation(tran,wordId);
    }
    for (const Phrase& phra : word.wordPhrase) {
        insertPhrase(phra, wordId);
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
    
    query.prepare("INSERT INTO WordGroup(book_id,wordgroup_tag,sentence_reference,wordgroup_valid,note) VALUES (?,?,?,?,?)");
    query.addBindValue(bookId);
    query.addBindValue(wordgroup.wordgroupTag);
    query.addBindValue(wordgroup.sentenceReference);
    query.addBindValue(wordgroup.wordgroupValid);
    query.addBindValue(wordgroup.note);

    if (!query.exec()) {
        qDebug() << "error WG";
        return;
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
        qDebug() << "error in insertBook "<<query.lastError();
        return;
    }

    int bookId = query.lastInsertId().toInt();

    for (const WordGroup& wordgroup : book.wordGroups) {
        insertWordGroup(wordgroup,bookId);
    }

}

void deposit(const Book& book) {
    QString dbpath = "C:\\Users\\28063\\Desktop\\Mem_version3\\MemWord\\DB\\MemWord.db";
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(dbpath);
    if (!database.open()) {
        qDebug() << "can't open";
    }
    insertBook(book);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MemWord w;

    QString path = "C:\\Users\\28063\\Desktop\\Mem_version3\\MemWord\\file\\cet4.json";


    Book newbook = initeBook(path);

    deposit(newbook);

    w.show();
    return a.exec();
}
