#ifndef AUDIORECORDER_HH
#define AUDIORECORDER_HH

#include "IAudioInputStreamListener.hh"

class AudioBuffer;
class IAudioInputStream;

class AudioRecorder : public IAudioInputStreamListener
{
private:
  AudioBuffer&		m_buffer;
  IAudioInputStream*	m_stream;
  unsigned long		m_currentFrame;

public:
  AudioRecorder(AudioBuffer& buffer);
  ~AudioRecorder();

  void	start();
  void	stop();
  bool	active();

  int	onStreamRequest(const void* input, unsigned long frames,
			unsigned int channels, SampleFormat sampleFormat);
};

#endif /* AUDIORECORDER_HH */
