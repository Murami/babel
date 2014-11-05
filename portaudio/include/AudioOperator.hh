#ifndef AUDIOOPERATOR_HH
#define AUDIOOPERATOR_HH

#include "IAudioStreamListener.hh"

// if framesMax == 0 -> infinite
class AudioOperator : public IAudioStreamListener
{
protected:
  IAudioStream*		m_stream;
  IAudioService*	m_service;
  AudioBuffer*		m_buffer;
  unsigned long		m_framesMax;
  unsigned long		m_currentFrames;

public:
  AudioOperator(AudioBuffer* buffer, IAudioService* service, unsigned long framesMax = 0);
  ~AudioOperator();

  void		start();
  void		run(unsigned int sleepTime);
  bool		isActive();
  void		stop();
  int		onStreamRequest(const void* input, void* output,
				unsigned long framesPerBuffer, unsigned int channel);
};
