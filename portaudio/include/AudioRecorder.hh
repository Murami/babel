#ifndef AUDIORECORDER_HH
#define AUDIORECORDER_HH

#include <queue>
#include <stdint.h>

#include "IAudioInputStreamListener.hh"

class AudioBuffer;
class IAudioInputStream;
class IAudioCoder;

class AudioRecorder : public IAudioInputStreamListener
{
private:
  std::queue<void*>	m_frameQueue;
  IAudioCoder*		m_coder;
  IAudioInputStream*	m_stream;

public:
  AudioRecorder();
  ~AudioRecorder();

  void	start();
  void	stop();
  bool	active();

  void	pushFrame(void* frame);
  void* popFrame();
  int	nextFrameSize() const;
  int	size() const;

  int	onStreamRequest(const void* input, unsigned long frames,
			unsigned int channels, SampleFormat sampleFormat);
};

#endif /* AUDIORECORDER_HH */
