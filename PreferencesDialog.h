#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include "ui_PreferencesDialog.h"

class PreferencesDialog :
	public QDialog,
	private Ui::PreferencesDialog
{
Q_OBJECT

public:
	explicit PreferencesDialog(QWidget* parent = Q_NULLPTR);
};

#endif // PREFERENCESDIALOG_H
