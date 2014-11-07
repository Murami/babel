#include "APAAudioStream.hh"
#include "PAAudioService.hh"

#include <cstdlib>
#include <algorithm>

APAAudioStream::APAAudioStream(unsigned int channels,
			       unsigned int sampleRate,
			       unsigned int framesPerBuffer,
			       SampleFormat sampleFormat) :
  m_stream(NULL),
  m_channels(channels),
  m_sampleRate(sampleRate),
  m_framesPerBuffer(framesPerBuffer),
  m_sampleFormat(sampleFormat)
{
  m_parameters.channelCount = m_channels;
  m_parameters.sampleFormat = PAAudioService::getInstance()->getPaSampleFormat(sampleFormat);
  m_parameters.hostApiSpecificStreamInfo = NULL;
}

APAAudioStream::~APAAudioStream()
{
}

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

// void	APAAudioStream::open()
// {
//   if (m_stream != NULL)
//     this->close();
//   Pa_OpenStream(&m_stream,
//   		(m_inputParameters.device == -1) ? NULL : &m_inputParameters,
//   		(m_outputParameters.device == -1) ? NULL : &m_outputParameters,
//   		sampleRate,
//   		framesPerBuffer,
//   		paClipOff,
//   		&launch_listener_events,
//   		this);
// }

void		APAAudioStream::setSampleFormat(SampleFormat format)
{
  m_sampleFormat = format;
  m_parameters.sampleFormat = PAAudioService::getInstance()->getPaSampleFormat(m_sampleFormat);
}

void		APAAudioStream::setChannels(unsigned int channels)
{
  m_channels = channels;
}

void		APAAudioStream::setSampleRate(unsigned int sampleRate)
{
  m_sampleRate = sampleRate;
}

void		APAAudioStream::setFramesPerBuffer(unsigned int framesPerBuffer)
{
  m_framesPerBuffer = framesPerBuffer;
}

SampleFormat	APAAudioStream::getSampleFormat()
{
  return (m_sampleFormat);
}

unsigned int	APAAudioStream::getChannels()
{
  return (m_channels);
}

unsigned int	APAAudioStream::getSampleRate()
{
  return (m_sampleRate);
}

unsigned int	APAAudioStream::getFramesPerBuffer()
{
  return (m_framesPerBuffer);
}

void	APAAudioStream::close()
{
  if (this->active())
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
  if (!this->active())
    Pa_StartStream(m_stream);
}

void	APAAudioStream::stop()
{
  if (this->active())
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
