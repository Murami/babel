#include "PAAudioOutputStream.hh"
#include "PAAudioService.hh"
#include "IAudioDevice.hh"
#include "IAudioOutputStreamListener.hh"

#include <cstdlib>

PAAudioOutputStream::PAAudioOutputStream(unsigned int channels,
					 unsigned int sampleRate,
					 unsigned int framesPerBuffer,
					 SampleFormat sampleFormat,
					 IAudioOutputStreamListener* listener,
					 IAudioDevice* device) :

  APAAudioStream(channels,
		 sampleRate,
		 framesPerBuffer,
		 sampleFormat)
{
  m_listener = listener;
  if (device == NULL)
    m_parameters.device = PAAudioService::getInstance()->getDefaultOutputDevice()->getIndex();
  else
    m_parameters.device = device->getIndex();
  m_parameters.suggestedLatency = Pa_GetDeviceInfo(m_parameters.device)->defaultLowOutputLatency;
}

PAAudioOutputStream::~PAAudioOutputStream()
{
}

void	PAAudioOutputStream::setOutputDevice(IAudioDevice* inputDevice)
{
  if (inputDevice == NULL)
    m_parameters.device = inputDevice->getIndex();

  m_parameters.suggestedLatency =
    Pa_GetDeviceInfo(m_parameters.device)->defaultLowOutputLatency;
  m_parameters.hostApiSpecificStreamInfo = NULL;
}

void	PAAudioOutputStream::setListener(IAudioOutputStreamListener* listener)
{
  m_listener = listener;
}

void	PAAudioOutputStream::open()
{
  if (m_stream != NULL)
    this->close();
  Pa_OpenStream(&m_stream,
  		NULL,
  		&m_parameters,
  		m_sampleRate,
  		m_framesPerBuffer,
  		paClipOff,
  		&PAAudioOutputStream::onEventRequest,
  		this);
}

void		PAAudioOutputStream::setSampleFormat(SampleFormat format)
{ APAAudioStream::setSampleFormat(format); }

void		PAAudioOutputStream::setChannels(unsigned int channels)
{ APAAudioStream::setChannels(channels); }

void		PAAudioOutputStream::setSampleRate(unsigned int sampleRate)
{ APAAudioStream::setSampleRate(sampleRate); }

void		PAAudioOutputStream::setFramesPerBuffer(unsigned int framesPerBuffer)
{ APAAudioStream::setFramesPerBuffer(framesPerBuffer); }

SampleFormat	PAAudioOutputStream::getSampleFormat()
{ return (APAAudioStream::getSampleFormat()); }

unsigned int	PAAudioOutputStream::getChannels()
{ return (APAAudioStream::getChannels()); }

unsigned int	PAAudioOutputStream::getSampleRate()
{ return (APAAudioStream::getSampleRate()); }

unsigned int	PAAudioOutputStream::getFramesPerBuffer()
{ return (APAAudioStream::getFramesPerBuffer()); }

bool		PAAudioOutputStream::active()
{ return (APAAudioStream::active()); }

void		PAAudioOutputStream::close()
{ APAAudioStream::close(); }

void		PAAudioOutputStream::start()
{ APAAudioStream::start(); }

void		PAAudioOutputStream::stop()
{ APAAudioStream::stop(); }

int	PAAudioOutputStream::onEventRequest(const void* /*input*/,
					    void* output,
					    unsigned long frame,
					    const PaStreamCallbackTimeInfo* /*timeinfo*/,
					    PaStreamCallbackFlags /*status*/,
					    void* data
					    )
{
  PAAudioOutputStream*	_this = static_cast<PAAudioOutputStream*>(data);

  if (_this->m_listener->onStreamRequest(output, frame, _this->getChannels(), _this->getSampleFormat()))
    return (paContinue);
  else
    return (paComplete);
}
