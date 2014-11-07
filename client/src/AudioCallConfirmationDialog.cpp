#include	"AudioCallConfirmationDialog.hh"

AudioCallConfirmationDialog::AudioCallConfirmationDialog(BabelCoreClient &core,
							 const QString& caller,
							 QWidget *parent):
  QDialog(parent), _core(core)
{
  this->_caller = caller;
  this->setFixedSize(300, 200);
  this->setWindowTitle(QString("Incoming call from ") + caller);
}

AudioCallConfirmationDialog::~AudioCallConfirmationDialog() {}
