#include"translation.h"
#include"qdebug.h"



Translation::Translation() {
	this->type = NULL;
	this->translationContext = NULL;
}

void Translation::display() {
	qDebug() << "type" << this->type;
	qDebug() << "translationContext" << translationContext;
}
