#include "memword.h"
#include <QtWidgets/QApplication>

#include"all_func_definition.h"
#include"qtablewidget.h"
#include"qlabel.h"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MemWord w;

	 //QString path = "C:\\Users\\28063\\Desktop\\Mem_version3\\MemWord\\file\\cet4.json";
	 //Book newbook = initeBook(path);
	 //deposit(newbook);
	
	//QList<WordGroupSchema> re = findUnlearned(1, 5);


	w.show();


	//QWidget window;
	//window.setWindowTitle("QTableWidget example");
	//
	//
	//QTableWidget* tableWidget = new QTableWidget(5, 3, &window); // 5 ÐÐ 3 ÁÐ
	//tableWidget->setHorizontalHeaderLabels({ "line 1", "line 2", "line 3" });
	//
	//
	//for (int row = 0; row < 5; ++row) {
	//	for (int col = 0; col < 3; ++col) {
	//		tableWidget->setItem(row, col, new QTableWidgetItem(QString("Item %1").arg(row * 3 + col + 1)));
	//	}
	//}
	//
	//
	//QVBoxLayout* layout = new QVBoxLayout;
	//layout->addWidget(tableWidget);
	//window.setLayout(layout);
	//
	//
	//window.show();
	
	return a.exec();
}
