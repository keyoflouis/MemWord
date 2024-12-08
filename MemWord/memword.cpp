#include "memword.h"

#include"all_func_definition.h"
#include"qpushbutton.h"



MemWord::MemWord(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	openDatabase(database, dbpath);

	ui.file_tab->setLayout(reFreshFileTab());
	ui.book_tab->setLayout(reFreshBookTab());




}

MemWord::~MemWord()
{
	closeDatabase(database);
}

QGridLayout* MemWord::reFreshFileTab()
{

	return new QGridLayout();
}

QGridLayout* MemWord::reFreshBookTab()
{
	QGridLayout* bookLayOut = new QGridLayout();

	QSqlQuery query;
	QList<BookSchema> allbooks = allBook();


	for (const BookSchema& book : allbooks) {
		QPushButton* but = new QPushButton(book.bookName);
		bookLayOut->addWidget(but);
		connect(but, &QPushButton::clicked, this, [=]() {

			});
	}


	return bookLayOut;
}
