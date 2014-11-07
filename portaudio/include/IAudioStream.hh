#ifndef IAUDIOSTREAM_HH
#define IAUDIOSTREAM_HH

#include "SampleFormat.hh"

class IAudioStreamListener;

class IAudioStream
{
public:
  virtual ~IAudioStream() {}

  virtual void	setSampleFormat(SampleFormat format) = 0;
  virtual void	setChannels(unsigned int channels) = 0;
  virtual void	setSampleRate(unsigned int sampleRate) = 0;
  virtual void	setFramesPerBuffer(unsigned int framesPerBuffer) = 0;
  virtual bool	active() = 0;
  virtual void	close() = 0;
  virtual void	start() = 0;
  virtual void	stop() = 0;
  virtual void	open() = 0;
};

#endif /* IAUDIOSTREAM_HH */
