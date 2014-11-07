#ifndef APAAUDIOSTREAM_HH
#define APAAUDIOSTREAM_HH

#include "IAudioStream.hh"
#include "APAAudioStream.hh"

#include <list>
#include <portaudio.h>

class IAudioStreamListener;

class APAAudioStream
{
protected:
  PaStreamParameters	m_parameters;
  PaStream*		m_stream;

  unsigned int		m_channels;
  unsigned int		m_sampleRate;
  unsigned int		m_framesPerBuffer;
  SampleFormat		m_sampleFormat;

public:
  APAAudioStream(unsigned int channels,
		 unsigned int sampleRate,
		 unsigned int framesPerBuffer,
		 SampleFormat sampleFormat);
  ~APAAudioStream();

  void		setSampleFormat(SampleFormat format);
  void		setChannels(unsigned int channels);
  void		setSampleRate(unsigned int sampleRate);
  void		setFramesPerBuffer(unsigned int framesPerBuffer);

  SampleFormat	getSampleFormat();
  unsigned int	getChannels();
  unsigned int	getSampleRate();
  unsigned int	getFramesPerBuffer();

  bool		active();
  void		close();
  void		start();
  void		stop();
  virtual void	open() = 0;
};

#endif /* APAAUDIOSTREAM_HH */
