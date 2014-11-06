#ifndef AUDIOPLAYER_HH
#define AUDIOPLAYER_HH

#include "IAudioOutputStreamListener.hh"

class AudioBuffer;
class IAudioOutputStream;

class AudioPlayer : public IAudioOutputStreamListener
{
private:
  AudioBuffer&		m_buffer;
  IAudioOutputStream*	m_stream;
  unsigned long		m_currentFrame;
  unsigned long		m_framesMax;

public:
  AudioPlayer(AudioBuffer& m_buffer, unsigned long framesMax = 0);
  ~AudioPlayer();

  void	start();
  void	stop();
  bool	active();

  int	onStreamRequest(void* output, unsigned long frame,
			unsigned int channels, SampleFormat sampleFormat);
};

#endif /* AUDIOPLAYER_HH */
