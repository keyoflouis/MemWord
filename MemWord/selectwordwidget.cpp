#include "selectwordwidget.h"

#include"qtablewidget.h"
#include"qcheckbox.h"



SelectWordWidget::SelectWordWidget(QWidget *parent , wordgroup_data agroupuidata)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->agroupuidata = agroupuidata;
	this->Refresh();
}

SelectWordWidget::~SelectWordWidget()
{
}

void SelectWordWidget::Refresh()
{
    ui.wordlist->setColumnCount(3);
    ui.wordlist->setRowCount(agroupuidata.words.size());
    ui.wordlist->setHorizontalHeaderLabels({ "word_context", "translation_context", "word_mark" });

    for (int row = 0; row < agroupuidata.words.size(); ++row) {
        const word_data& wd = agroupuidata.words[row];
        ui.wordlist->setItem(row, 0, new QTableWidgetItem(wd.word.wordContext));

        if (wd.word.wordMark) {
            QString showtranslation;
            for (const auto& tran : wd.trans) {
                if (tran.wordId == wd.word.wordId) {
                    showtranslation += QString("%1 %2 ").arg(tran.type, tran.translationContext);
                }
            }
            ui.wordlist->setItem(row, 1, new QTableWidgetItem(showtranslation));
        }
        else
        {
            ui.wordlist->setItem(row, 1, new QTableWidgetItem(" "));
        }
        

        QCheckBox* checkword = new QCheckBox();
        checkword->setChecked(wd.word.wordMark);
        ui.wordlist->setCellWidget(row, 2, checkword);

        connect(checkword, &QCheckBox::stateChanged, this, [this, row, wd](int state) {
            this->handleCheckBoxStateChange(state, row, wd);
            });
    }

}

void SelectWordWidget::handleCheckBoxStateChange(int state, int row, const word_data& wd)
{
    QString showtranslation;
    if (state == Qt::Unchecked) {
        ui.wordlist->item(row, 1)->setText(" ");
        agroupuidata.words[row].word.wordMark = false;
    }
    else {
        for (const auto& tran : wd.trans) {
            if (tran.wordId == wd.word.wordId) {
                showtranslation += QString("%1 %2 ").arg(tran.type, tran.translationContext);
            }
        }
        ui.wordlist->item(row, 1)->setText(showtranslation);
        agroupuidata.words[row].word.wordMark = true;
    }
    
}

void SelectWordWidget::emiteRefreshData()
{
		emit refreshData(agroupuidata);
}
void SelectWordWidget::onRefresh(wordgroup_data agroupuidata) {
	this->agroupuidata = agroupuidata;
	this->Refresh();
}