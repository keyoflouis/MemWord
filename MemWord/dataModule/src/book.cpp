#include"book.h"
#include"qdebug.h"

 Book::Book() {
	this->bookName = NULL;
	this->bookDescription = NULL;
}

void Book::display() {
	qDebug() << "bookName:" << bookName;
	qDebug() << "bokDescription" << bookDescription;

	for (auto i : wordGroups) {
		i.display();
	}
}
