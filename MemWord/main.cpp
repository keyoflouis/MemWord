#include "memword.h"
#include <QtWidgets/QApplication>

#include"all_func_definition.h"

#include"qwizard.h"
#include"qdockwidget.h"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MemWord w;

	 //QString path = "C:\\Users\\28063\\Desktop\\Mem_version3\\MemWord\\file\\cet4.json";
	 //Book newbook = initeBook(path);
	 //deposit(newbook);
	
	//QList<WordGroupSchema> re = findUnlearned(1, 5);

	w.show();
	return a.exec();
}
