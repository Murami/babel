#include "AudioBuffer.hh"
#include "AudioRecorder.hh"
#include "PAAudioInputStream.hh"

#include "SampleFormat.hh"

#include <iostream>
#include <cstring>

AudioRecorder::AudioRecorder(AudioBuffer& buffer) :
  m_buffer(buffer),
  m_currentFrame(0)
{
  m_stream = new PAAudioInputStream(buffer.channels(),
				    buffer.sampleRate(),
				    0,
				    buffer.sampleFormat(),
				    this),
  m_stream->open();
}

AudioRecorder::~AudioRecorder()
{
  m_stream->close();
  delete m_stream;
}

void	AudioRecorder::start()
{
  m_stream->start();
}

bool	AudioRecorder::active()
{
  return (m_stream->active());
}

void	AudioRecorder::stop()
{
  m_stream->stop();
}

int	AudioRecorder::onStreamRequest(const void* input,
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
  memcpy(ptr, input, sizeBuffer);

  m_currentFrame += frames;
  return (m_currentFrame < m_buffer.maxFrame());
}
