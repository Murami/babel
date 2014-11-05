#include "AudioPlayer.hh"
#include "AudioBuffer.hh"
#include "PAAudioOutputStream.hh"

#include <cstring>

AudioPlayer::AudioPlayer(AudioBuffer& buffer,
			 unsigned long framesMax) :
  m_buffer(buffer),
  m_currentFrame(0),
  m_framesMax(framesMax)
{
  m_stream = new PAAudioOutputStream(buffer.channels(),
				     buffer.sampleRate(),
				     0,
				     buffer.sampleFormat(),
				     this),
  m_stream->open();
}

AudioPlayer::~AudioPlayer()
{
  m_stream->close();
  delete m_stream;
}

void	AudioPlayer::start()
{
  m_stream->start();
}

bool	AudioPlayer::active()
{
  return (m_stream->active());
}

void	AudioPlayer::stop()
{
  m_stream->stop();
}

int	AudioPlayer::onStreamRequest(void* output,
				     unsigned long frames,
				     unsigned int channels,
				     SampleFormat sampleFormat)
{
  size_t	sampleSize = g_sampleFormatSizes[sampleFormat];
  size_t	framesLeft = m_buffer.maxFrame() - m_currentFrame;
  size_t	sizeBuffer;
  void*		ptr;

  if (framesLeft < frames)
    sizeBuffer = framesLeft * channels * sampleSize;
  else
    sizeBuffer = frames * channels * sampleSize;

  ptr = (char*)m_buffer.data() + (m_currentFrame * channels * sampleSize);
  if (m_currentFrame > m_buffer.maxFrame())
    m_currentFrame = m_buffer.maxFrame();
  memcpy(output, ptr, sizeBuffer);

  m_currentFrame += frames;
  return (m_currentFrame < m_buffer.maxFrame());
}
