#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include "ui_PreferencesDialog.h"

class PreferencesDialog :
	public QDialog,
	private Ui::PreferencesDialog
{
Q_OBJECT

public:
	PreferencesDialog(QWidget* parent = Q_NULLPTR);

private:
	void updateSpinText();

private slots:
	void on__weekSpanSpinBox_valueChanged(int newValue);
};

#endif // PREFERENCESDIALOG_H
