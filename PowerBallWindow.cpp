#include "PowerBallWindow.h"

#include "PreferencesDialog.h"

#include <QDesktopWidget>
#include <QMenuBar>
#include <QStatusBar>

PowerBallWindow::PowerBallWindow() :
	QMainWindow(Q_NULLPTR)
{
	setupUi(this);

	connect(actionUpdate_Draw_Data, &QAction::triggered, this, &PowerBallWindow::onUpdateDataTriggered);
	connect(actionQuit, &QAction::triggered, QCoreApplication::instance(), &QCoreApplication::quit);
}

void PowerBallWindow::onUpdateDataTriggered
(
	bool checked //= false
)
{
	Q_UNUSED(checked);

   LottoWidget* lottoWidget = qobject_cast<LottoWidget*>(centralWidget());
   if (lottoWidget != Q_NULLPTR)
   {
	   lottoWidget->on__updateDrawData_released();
   }
}

void PowerBallWindow::on_actionPreferences_triggered
(
	bool checked //= false
)
{
	Q_UNUSED(checked);

	PreferencesDialog preferencesDialog(this);

	if (preferencesDialog.exec() == QDialog::Accepted)
	{
	}
}
