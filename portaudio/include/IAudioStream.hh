#ifndef IAUDIOSTREAM_HH
#define IAUDIOSTREAM_HH

class IAudioStreamListener;

class IAudioStream
{
public:
  virtual void	setListener(IAudioStreamListener* listener);
  virtual void	setInputStream(int inputDevice, int channelCount);
  virtual void	setOutputStream(int outputDevice , int channelCount);
  virtual bool	isActive() = 0;
  virtual void	open(double sampleRate, unsigned long framesPerBuffer);
  virtual void	close() = 0;
  virtual void	start() = 0;
  virtual void	stop() = 0;
};

#endif /* IAUDIOSTREAM_HH */
