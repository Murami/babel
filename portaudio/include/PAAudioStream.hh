#ifndef PAAUDIOSTREAM_HH
#define PAAUDIOSTREAM_HH

#include "PAAudioStream.hh"

#include <list>
#include <portaudio.h>

class IAudioStreamListener;

int	launch_listener_events(const void* input, void* output, unsigned long frameCount,
			       const PaStreamCallbackTimeInfo* timeInfo,
			       PaStreamCallbackFlags statusFlags, void* userData);

class PAAudioStream
{
private:
  PaStreamParameters	m_inputParameters;
  PaStreamParameters	m_outputParameters;
  IAudioStreamListener*	m_listener;
  PaStream*		m_stream;

public:
  PAAudioStream();
  ~PAAudioStream();

  void	setListener(IAudioStreamListener* listener);
  void	setInputStream(int inputDevice, int channelCount);
  void	setOutputStream(int outputDevice, int channelCount);
  bool	isActive();
  void	open(double sampleRate, unsigned long framesPerBuffer);
  void	close();
  void	start();
  void	stop();

  int	onStreamRequest(const void* input, void* output, unsigned long frameCount);
};

#endif /* PAAUDIOSTREAM_HH */
