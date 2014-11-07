#ifndef PAAUDIOOUTPUTSTREAM_HH
#define PAAUDIOOUTPUTSTREAM_HH

#include "APAAudioStream.hh"
#include "IAudioOutputStream.hh"

#include <cstdlib>

class PAAudioOutputStream : public APAAudioStream, public IAudioOutputStream
{
private:
  IAudioOutputStreamListener*	m_listener;

public:
  PAAudioOutputStream(unsigned int channels,
		     unsigned int sampleRate,
		     unsigned int framesPerBuffer,
		     SampleFormat sampleFormat,
		     IAudioOutputStreamListener* listener,
		     IAudioDevice* device = NULL);

  ~PAAudioOutputStream();

  void	setOutputDevice(IAudioDevice* inputDevice);
  void	setListener(IAudioOutputStreamListener* listener);
  void	open();

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

  static int	onEventRequest(const void* input,
			       void* output,
			       unsigned long frame,
			       const PaStreamCallbackTimeInfo* timeinfo,
			       PaStreamCallbackFlags status,
			       void* data
			       );
};

#endif /* PAAUDIOOUTPUTSTREAM_HH */
