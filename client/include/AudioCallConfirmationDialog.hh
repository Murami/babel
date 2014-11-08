#ifndef		__AUDIOCALLCONFIRMATIONDIALOG_HH__
# define	__AUDIOCALLCONFIRMATIONDIALOG_HH__

# include	<QDialog>
# include	"ICallErrorListener.hh"

class		MainWindow;
class		WidgetButton;
class		BabelCoreClient;

class		AudioCallConfirmationDialog : public QDialog,
					      public ICallErrorListener
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
  virtual void	onCallError(bool);

public:
  AudioCallConfirmationDialog(BabelCoreClient& core,
			      const QString& caller,
			      QWidget *parent = 0);
  ~AudioCallConfirmationDialog();
};

#endif
