#include "PAAudioStream.hh"
#include "IAudioStreamListener.hh"

#include <cstdlib>
#include <algorithm>

PAAudioStream::PAAudioStream() :
  m_listener(NULL)
{
  m_inputParameters.device = -1;
  m_outputParameters.device = -1;
  m_stream = NULL;
}

PAAudioStream::~PAAudioStream()
{
}

void	PAAudioStream::setListener(IAudioStreamListener* listener)
{
  m_listener = listener;
}

void	PAAudioStream::setInputStream(int inputDevice, int channelCount)
{
  m_inputParameters.device = inputDevice;
  if (inputDevice == -1)
    return;
  m_inputParameters.channelCount = channelCount;
  m_inputParameters.sampleFormat = paInt16;
  m_inputParameters.suggestedLatency =
    Pa_GetDeviceInfo(inputDevice)->defaultLowOutputLatency;
  m_inputParameters.hostApiSpecificStreamInfo = NULL;
}

void	PAAudioStream::setOutputStream(int outputDevice, int channelCount)
{
  m_outputParameters.device = outputDevice;
  if (outputDevice == -1)
    return;
  m_outputParameters.channelCount = channelCount;
  m_outputParameters.sampleFormat = paInt16;
  m_outputParameters.suggestedLatency =
    Pa_GetDeviceInfo(outputDevice)->defaultLowOutputLatency;
  m_outputParameters.hostApiSpecificStreamInfo = NULL;
}

void	PAAudioStream::open(double sampleRate, unsigned long framesPerBuffer)
{
  if (m_stream != NULL)
    this->close();
  Pa_OpenStream(&m_stream,
		(m_inputParameters.device == -1) ? NULL : &m_inputParameters,
		(m_outputParameters.device == -1) ? NULL : &m_outputParameters,
		sampleRate,
		framesPerBuffer,
		paClipOff,
		&launch_listener_events,
		this);
}

void	PAAudioStream::close()
{
  if (this->isActive())
    this->stop();
  if (m_stream == NULL)
    return;
  Pa_CloseStream(m_stream);
  m_stream = NULL;
}

bool	PAAudioStream::isActive()
{
  return (Pa_IsStreamActive(m_stream));
}

void	PAAudioStream::start()
{
  if (!this->isActive())
    Pa_StartStream(m_stream);
}

void	PAAudioStream::stop()
{
  if (this->isActive())
    Pa_StopStream(m_stream);
}

int	PAAudioStream::onStreamRequest(const void* input, void* output, unsigned long frameCount)
{
  return (m_listener->onStreamRequest(input, output, frameCount));
}

int	launch_listener_events(const void* input, void* output, unsigned long frameCount,
			       const PaStreamCallbackTimeInfo* /*timeInfo*/,
			       PaStreamCallbackFlags /*statusFlags*/, void* userData)
{
  PAAudioStream*	stream = static_cast<PAAudioStream*>(userData);

  return (stream->onStreamRequest(input, output, frameCount));
}
