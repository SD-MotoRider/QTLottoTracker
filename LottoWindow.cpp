#include "LottoWindow.h"
#include "ui_LottoWindow.h"

LottoWindow::LottoWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LottoWindow)
{
	ui->setupUi(this);
}

LottoWindow::~LottoWindow()
{
	delete ui;
}
