#include "memword.h"

#include"bookui.h"
#include"all_func_definition.h"

#include"qpushbutton.h"

void initBookUi(BookSchema bookschema){
	BookUI* bookui = new BookUI(nullptr,bookschema);
	bookui->show();
}

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

	// generate but for book ui
	for (const BookSchema& book : allbooks) {
		QPushButton* but = new QPushButton(book.bookName);
		bookLayOut->addWidget(but);
		connect(but, &QPushButton::clicked, this, [=]() {
			initBookUi(book);
			this->close();
			});
	}


	return bookLayOut;
}
