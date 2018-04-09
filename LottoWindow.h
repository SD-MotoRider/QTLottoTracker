#ifndef LOTTOWINDOW_H
#define LOTTOWINDOW_H

#include <QDialog>

namespace Ui {
class LottoWindow;
}

class LottoWindow : public QDialog
{
	Q_OBJECT

public:
	explicit LottoWindow(QWidget *parent = 0);
	~LottoWindow();

private:
	Ui::LottoWindow *ui;
};

#endif // LOTTOWINDOW_H
