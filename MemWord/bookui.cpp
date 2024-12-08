#include "bookui.h"
#include"wordgroupui.h"

#include"qlabel.h"
#include"qlayout.h"
#include"qpushbutton.h"

#include"qtablewidget.h"

void initWordGroupUI( QList<WordGroupSchema> wordgroups) {
	WordGroupUI* wordgroupui = new WordGroupUI(nullptr,wordgroups);
	wordgroupui->show();
}

BookUI::BookUI(QWidget *parent ,BookSchema bookschema)
	: QWidget(parent)
{
	ui.setupUi(this);

	QVBoxLayout* bookLayOut = new QVBoxLayout();

	QLabel* bookName =new QLabel();
	bookName->setText(bookschema.bookName);

	QLabel* bookDescription = new QLabel();
	bookDescription->setText(bookschema.bookDescription);

	QPushButton* learn = new QPushButton();
	learn->setText("Learn");

	connect(learn, &QPushButton::clicked, this, [=]() {
		
		int numbersofGroup = 5;
		int rowsofaGroup = 6;

		QWidget* mediaUI = new QWidget();
		QVBoxLayout* mediaUILayOut = new QVBoxLayout(mediaUI);

		QList<WordGroupSchema> unlearned = findUnlearned(bookschema.bookId, numbersofGroup);

		QTableWidget* tableWidget = new QTableWidget(numbersofGroup,rowsofaGroup);
		tableWidget->setHorizontalHeaderLabels({ "book_id","wordgroup_id","wordgroup_tag","sentence_reference","wordgroup_mark","note" });
		
		int row = 0;
		for (const WordGroupSchema& item : unlearned) {
			tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(item.bookId)));
			tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(item.wordgroupId)));
			tableWidget->setItem(row, 2, new QTableWidgetItem(item.wordgroupTag));
			tableWidget->setItem(row, 3, new QTableWidgetItem(item.sentenceReference));
			tableWidget->setItem(row, 4, new QTableWidgetItem(item.wordgroupMark));
			tableWidget->setItem(row, 5, new QTableWidgetItem(item.note));
			row++;
		}


		mediaUILayOut->addWidget(tableWidget);

		QPushButton* next = new QPushButton();
		next->setText("start");
		connect(next, &QPushButton::clicked, this, [=]() {
			initWordGroupUI(unlearned);
			});
		mediaUILayOut->addWidget(next);
		mediaUI->setMinimumSize(800,600);
		mediaUI->show();
		this->close();
		});


	QPushButton* review = new QPushButton();
	review->setText("Review");
	connect(review, &QPushButton::clicked, this, [=]() {
		
		});


	QHBoxLayout* buts = new QHBoxLayout();
	buts->addWidget(learn);
	buts->addWidget(review);

	bookLayOut->addWidget(bookName);
	bookLayOut->addWidget(bookDescription);
	bookLayOut->addItem(buts);


	setLayout(bookLayOut);

}

BookUI::~BookUI()
{
}

