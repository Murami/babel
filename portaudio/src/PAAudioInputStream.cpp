#include "PAAudioInputStream.hh"
#include "PAAudioService.hh"
#include "IAudioDevice.hh"
#include "IAudioInputStreamListener.hh"

#include <cstdlib>

PAAudioInputStream::PAAudioInputStream(unsigned int channels,
				       unsigned int sampleRate,
				       unsigned int framesPerBuffer,
				       SampleFormat sampleFormat,
				       IAudioInputStreamListener* listener,
				       IAudioDevice* device) :

  APAAudioStream(channels,
		 sampleRate,
		 framesPerBuffer,
		 sampleFormat)
{
  m_listener = listener;
  if (device == NULL)
    m_parameters.device = PAAudioService::getInstance()->getDefaultInputDevice()->getIndex();
  else
    m_parameters.device = device->getIndex();
  m_parameters.suggestedLatency = Pa_GetDeviceInfo(m_parameters.device)->defaultLowInputLatency;
}

PAAudioInputStream::~PAAudioInputStream()
{
}

void	PAAudioInputStream::setInputDevice(IAudioDevice* inputDevice)
{
  if (inputDevice == NULL)
    m_parameters.device = inputDevice->getIndex();

  m_parameters.suggestedLatency =
    Pa_GetDeviceInfo(m_parameters.device)->defaultLowOutputLatency;
  m_parameters.hostApiSpecificStreamInfo = NULL;
}

void	PAAudioInputStream::setListener(IAudioInputStreamListener* listener)
{
  m_listener = listener;
}

#include <iostream>

void	PAAudioInputStream::open()
{
  if (m_stream != NULL)
    this->close();
  Pa_OpenStream(&m_stream,
  		&m_parameters,
  		NULL,
  		m_sampleRate,
 		m_framesPerBuffer,
  		paClipOff,
  		&PAAudioInputStream::onEventRequest,
  		this);
}

void		PAAudioInputStream::setSampleFormat(SampleFormat format)
{ APAAudioStream::setSampleFormat(format); }

void		PAAudioInputStream::setChannels(unsigned int channels)
{ APAAudioStream::setChannels(channels); }

void		PAAudioInputStream::setSampleRate(unsigned int sampleRate)
{ APAAudioStream::setSampleRate(sampleRate); }

void		PAAudioInputStream::setFramesPerBuffer(unsigned int framesPerBuffer)
{ APAAudioStream::setFramesPerBuffer(framesPerBuffer); }

SampleFormat	PAAudioInputStream::getSampleFormat()
{ return (APAAudioStream::getSampleFormat()); }

unsigned int	PAAudioInputStream::getChannels()
{ return (APAAudioStream::getChannels()); }

unsigned int	PAAudioInputStream::getSampleRate()
{ return (APAAudioStream::getSampleRate()); }

unsigned int	PAAudioInputStream::getFramesPerBuffer()
{ return (APAAudioStream::getFramesPerBuffer()); }

bool		PAAudioInputStream::active()
{ return (APAAudioStream::active()); }

void		PAAudioInputStream::close()
{ APAAudioStream::close(); }

void		PAAudioInputStream::start()
{ APAAudioStream::start(); }

void		PAAudioInputStream::stop()
{ APAAudioStream::stop(); }

int	PAAudioInputStream::onEventRequest(const void* input,
					   void* /*output*/,
					   unsigned long frame,
					   const PaStreamCallbackTimeInfo* /*timeinfo*/,
					   PaStreamCallbackFlags /*status*/,
 					   void* data
					   )
{
  PAAudioInputStream*	_this = static_cast<PAAudioInputStream*>(data);

  if (_this->m_listener->onStreamRequest(input, frame, _this->getChannels(), _this->getSampleFormat()))
    return (paContinue);
  else
    return (paComplete);
}
