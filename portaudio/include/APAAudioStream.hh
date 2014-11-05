#ifndef PAAUDIOSTREAM_HH
#define PAAUDIOSTREAM_HH

#include "IAudioStream.hh"
#include "APAAudioStream.hh"

#include <list>
#include <portaudio.h>

class IAudioStreamListener;

class APAAudioStream : public IAudioStream
{
private:
  PaStreamParameters	m_streamParameters;
  PaSampleFormat	m_PaSampleFormat;

  unsigned int		m_channels;
  unsigned int		m_sampleRate;
  unsigned int		m_framesPerBuffer;
  SampleFormat		m_sampleFormat;

public:
  APAAudioStream();
  ~APAAudioStream();

  void		setSampleFormat(SampleFormat format);
  void		setChannels(unsigned int channels);
  void		setSampleRate(unsigned int sampleRate);
  void		setFramesPerBuffer(unsigned int framesPerBuffer);

  unsigned int	getSampleFormat();
  unsigned int	getChannels();
  unsigned int	getSampleRate();
  SampleFormat	getFramesPerBuffer();

  bool		active();
  void		close();
  void		start();
  void		stop();

  virtual void	open() = 0;
};

#endif /* PAAUDIOSTREAM_HH */
