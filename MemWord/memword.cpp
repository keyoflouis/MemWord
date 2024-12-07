#include "memword.h"

MemWord::MemWord(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

MemWord::~MemWord()
{}

QGridLayout* MemWord::reFreshFileTab()
{

    return new QGridLayout();
}

QGridLayout* MemWord::reFreshBookTab()
{

    return nullptr;
}
