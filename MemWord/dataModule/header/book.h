#pragma once

#include"qstring.h"
#include"qlist.h"
#include"wordgroup.h"


class Book {
public:
	QString bookName;
	QString bookDescription;

	QList<WordGroup> wordGroups;

	Book();

	void display();
};