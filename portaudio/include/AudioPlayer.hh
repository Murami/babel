#ifndef AUDIOPLAYER_HH
#define AUDIOPLAYER_HH

#include "IAudioOutputStreamListener.hh"
#include <queue>

class AudioBuffer;
class IAudioOutputStream;
class IAudioCoder;

class AudioPlayer : public IAudioOutputStreamListener
{
private:
  std::queue<void*>	m_frameQueue;
  IAudioCoder*		m_coder;
  IAudioOutputStream*	m_stream;

public:
  AudioPlayer();
  ~AudioPlayer();

  void	start();
  void	stop();
  bool	active();

  void	pushFrame(void* frame);
  void* popFrame();
  int	nextFrameSize() const;
  int	size() const;

  int	onStreamRequest(void* output, unsigned long frame,
			unsigned int channels, SampleFormat sampleFormat);
};

#endif /* AUDIOPLAYER_HH */
