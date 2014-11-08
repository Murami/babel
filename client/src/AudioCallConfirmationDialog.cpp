#include	<iostream>
#include	<QVBoxLayout>
#include	"BabelCoreClient.hh"
#include	"WidgetButton.hh"
#include	"AudioCallConfirmationDialog.hh"
#include	"MainWindow.hh"

AudioCallConfirmationDialog::AudioCallConfirmationDialog(BabelCoreClient &core,
							 const QString& caller,
							 QWidget *parent):
  QDialog(parent), _core(core)
{
  this->_mainWindow = static_cast<MainWindow*>(parent);
  QVBoxLayout *layout = new QVBoxLayout(this);
  this->_caller = caller;
  this->setFixedSize(300, 200);
  this->setWindowTitle(QString("Incoming call from ") + caller);
  this->_acceptButton = new WidgetButton("Accept", this);
  this->_declineButton = new WidgetButton("Decline", this);
  layout->addWidget(this->_acceptButton);
  layout->addWidget(this->_declineButton);
  this->setLayout(layout);
  connect(this->_acceptButton, SIGNAL(clicked()), this, SLOT(acceptCall()));
  connect(this->_declineButton, SIGNAL(clicked()), this, SLOT(declineCall()));
}

void		AudioCallConfirmationDialog::acceptCall()
{
  this->_core.onUserAcceptCall(this->_caller);
  this->_mainWindow->openAudioConversationWindow(this->_caller);
  this->close();
}

void		AudioCallConfirmationDialog::declineCall()
{
  this->_core.onUserDeclineCall(this->_caller);
  this->close();
}

AudioCallConfirmationDialog::~AudioCallConfirmationDialog() {}
