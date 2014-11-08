#ifndef		__AUDIOCALLCONFIRMATIONDIALOG_HH__
# define	__AUDIOCALLCONFIRMATIONDIALOG_HH__

# include	<QDialog>

class		MainWindow;
class		WidgetButton;
class		BabelCoreClient;

class		AudioCallConfirmationDialog : public QDialog
{
  Q_OBJECT

private:
  BabelCoreClient&		_core;
  QString			_caller;
  WidgetButton			*_acceptButton;
  WidgetButton			*_declineButton;
  MainWindow			*_mainWindow;

private slots:
  void		acceptCall();
  void		declineCall();

public:
  AudioCallConfirmationDialog(BabelCoreClient& core,
			      const QString& caller,
			      QWidget *parent = 0);
  ~AudioCallConfirmationDialog();
};

#endif
