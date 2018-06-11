#include "PreferencesDialog.h"

#include "PowerballPreferences.h"

PreferencesDialog::PreferencesDialog
(
	QWidget* parent
) :
	QDialog(parent)
{
	setupUi(this);

	PowerballPreferences powerBallPreferece;

	_limitToAboveExpected->setChecked(powerBallPreferece.pickNumbersThatExceedProbability());
	bool limitToTimeSpan = powerBallPreferece.limitPicksToTimeSpan();
	_limitToTimeSpan->setChecked(limitToTimeSpan);
	_weekSpanSpinBox->setEnabled(_limitToTimeSpan);
	_weekSpanSpinBox->setValue(powerBallPreferece.timeSpanInWeeks());

	updateSpinText();
}

void PreferencesDialog::updateSpinText()
{
	int spinWeeks = _weekSpanSpinBox->value();
	int spinMonths = spinWeeks / 4;
	int spinRemainder = spinWeeks % 4;

	QString months = QString("%1").arg(spinMonths);
	switch (spinRemainder)
	{
	case 1: months += ".25"; break;
	case 2: months += ".5"; break;
	case 3: months += ".75"; break;
	default: break;
	}

	_spinText->setText(QString("Weeks ( %1 months)").arg(months));
}

void PreferencesDialog::on__weekSpanSpinBox_valueChanged
(
	int newValue
)
{
	Q_UNUSED(newValue);

	updateSpinText();
}
