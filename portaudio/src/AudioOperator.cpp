#include "AudioOperator.hh"

AudioOperator::AudioOperator(AudioBuffer* buffer, IAudioService* service,
			     unsigned long framesMax) :
  m_service(service),
  m_buffer(buffer),
  m_framesMax(framesMax),
  m_currentFrames(0)
{
  m_stream =  new PAAudioStream();

  m_stream->setListener(this);
}

AudioOperator::~AudioOperator()
{
}

void	AudioOperator::start()
{
  m_stream->start();
}

void	AudioOperator::run(unsigned int sleepTime)
{
  this->start();
  while (this->active())
    m_service->sleep(sleepTime);
}

bool	AudioOperator::isActive()
{
  return (m_stream->isActive());
}

void	AudioOperator::stop()
{
  m_stream->stop();
}

int	AudioOperator::onStreamRequest(const void* input, void* output, unsigned long framesPerBuffer)
{
  /* SOME PIECE OF SHIT HERE */
}
