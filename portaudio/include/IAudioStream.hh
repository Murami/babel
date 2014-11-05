#ifndef IAUDIOSTREAM_HH
#define IAUDIOSTREAM_HH

enum SampleFormat
  {
    Float32,
    Int32,
    Int24,
    Int16,
    Int8,
    UInt8
  };

class IAudioStreamListener;

class IAudioStream
{
public:
  virtual void	setSampleFormat(SampleFormat format);
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
