#ifndef PAAUDIOINPUTSTREAM_HH
#define PAAUDIOINPUTSTREAM_HH

#include "APAAudioStream.hh"
#include "IAudioInputStream.hh"

#include <cstdlib>

class PAAudioInputStream : public APAAudioStream, public IAudioInputStream
{
private:
  IAudioInputStreamListener*	m_listener;

public:
  PAAudioInputStream(unsigned int channels,
		     unsigned int sampleRate,
		     unsigned int framesPerBuffer,
		     SampleFormat sampleFormat,
		     IAudioInputStreamListener* listener,
		     IAudioDevice* device = NULL);

  ~PAAudioInputStream();

  void		setInputDevice(IAudioDevice* inputDevice);
  void		setListener(IAudioInputStreamListener* listener);
  void		open();

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

#endif /* PAAUDIOINPUTSTREAM_HH */
