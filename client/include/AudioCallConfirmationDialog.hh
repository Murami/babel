#ifndef		__AUDIOCALLCONFIRMATIONDIALOG_HH__
# define	__AUDIOCALLCONFIRMATIONDIALOG_HH__

# include	<QDialog>

class		BabelCoreClient;

class		AudioCallConfirmationDialog : public QDialog
{
  Q_OBJECT

private:
  BabelCoreClient&		_core;
  QString			_caller;

public:
  AudioCallConfirmationDialog(BabelCoreClient& core,
			      const QString& caller,
			      QWidget *parent = 0);
  ~AudioCallConfirmationDialog();
};

#endif
