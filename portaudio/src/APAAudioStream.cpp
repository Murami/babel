#include "APAAudioStream.hh"
#include "IAudioStreamListener.hh"

#include <cstdlib>
#include <algorithm>

APAAudioStream::APAAudioStream() :
  m_listener(NULL)
{
  m_inputParameters.device = -1;
  m_outputParameters.device = -1;
  m_stream = NULL;
}

APAAudioStream::~APAAudioStream()
{
}

// void	APAAudioStream::setInputStream(int inputDevice, int channelCount)
// {
//   m_inputParameters.device = inputDevice;
//   if (inputDevice == -1)
//     return;
//   m_inputParameters.channelCount = channelCount;
//   m_inputParameters.sampleFormat = paInt16;
//   m_inputParameters.suggestedLatency =
//     Pa_GetDeviceInfo(inputDevice)->defaultLowOutputLatency;
//   m_inputParameters.hostApiSpecificStreamInfo = NULL;
// }

// void	APAAudioStream::setOutputStream(int outputDevice, int channelCount)
// {
//   m_outputParameters.device = outputDevice;
//   if (outputDevice == -1)
//     return;
//   m_outputParameters.channelCount = channelCount;
//   m_outputParameters.sampleFormat = paInt16;
//   m_outputParameters.suggestedLatency =
//     Pa_GetDeviceInfo(outputDevice)->defaultLowOutputLatency;
//   m_outputParameters.hostApiSpecificStreamInfo = NULL;
// }

// void	APAAudioStream::open(double sampleRate, unsigned long framesPerBuffer)
// {
//   if (m_stream != NULL)
//     this->close();
//   Pa_OpenStream(&m_stream,
// 		(m_inputParameters.device == -1) ? NULL : &m_inputParameters,
// 		(m_outputParameters.device == -1) ? NULL : &m_outputParameters,
// 		sampleRate,
// 		framesPerBuffer,
// 		paClipOff,
// 		&launch_listener_events,
// 		this);
// }

void		setSampleFormat(SampleFormat format)
{
  m_sampleFormat = format;
  // mapper le format vers un pa format
}

void		setChannels(unsigned int channels)
{
}

void		setSampleRate(unsigned int sampleRate)
{
}

void		setFramesPerBuffer(unsigned int framesPerBuffer)
{
}

SampleFormat	getSampleFormat()
{
  return (m_sampleFormat);
}

unsigned int	getChannels()
{
  return (m_channels);
}

unsigned int	getSampleRate()
{
  return (m_sampleRate);
}

unsigned int	getFramesPerBuffer()
{
  return (m_framesPerBuffer);
}

void	APAAudioStream::close()
{
  if (this->isActive())
    this->stop();
  if (m_stream == NULL)
    return;
  Pa_CloseStream(m_stream);
  m_stream = NULL;
}

bool	APAAudioStream::active()
{
  return (Pa_IsStreamActive(m_stream));
}

void	APAAudioStream::start()
{
  if (!this->isActive())
    Pa_StartStream(m_stream);
}

void	APAAudioStream::stop()
{
  if (this->isActive())
    Pa_StopStream(m_stream);
}

// int	APAAudioStream::onStreamRequest(const void* input, void* output, unsigned long frameCount)
// {
//   return (m_listener->onStreamRequest(input, output, frameCount));
// }

// int	launch_listener_events(const void* input, void* output, unsigned long frameCount,
// 			       const PaStreamCallbackTimeInfo* /*timeInfo*/,
// 			       PaStreamCallbackFlags /*statusFlags*/, void* userData)
// {
//   APAAudioStream*	stream = static_cast<APAAudioStream*>(userData);

//   return (stream->onStreamRequest(input, output, frameCount));
// }
