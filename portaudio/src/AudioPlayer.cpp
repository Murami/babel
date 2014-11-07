#include "AudioPlayer.hh"
#include "AudioBuffer.hh"
#include "PAAudioOutputStream.hh"
#include "OpusAudioCoder.hh"


#include <iostream>
#include <cstring>

AudioPlayer::AudioPlayer()
{
  m_coder = new OpusAudioCoder(48000, 2, 64000);
  m_stream = new PAAudioOutputStream(2, 44100, 960, Int16, this);
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

void	AudioPlayer::pushFrame(void* frame)
{
  //Mutex ICI
  m_frameQueue.push(frame);
}

void*	AudioPlayer::popFrame()
{
  //Mutex ICI
  void*	frame;

  frame = m_frameQueue.front();
  m_frameQueue.pop();
  return (frame);
}

int	AudioPlayer::nextFrameSize() const
{
  //Mutex ICI
  uint32_t	size;

  memcpy(&size, m_frameQueue.front(), 4);
  return (size);
}

int	AudioPlayer::size() const
{
  //Mutex ICI
  return (m_frameQueue.size());
}

int	AudioPlayer::onStreamRequest(void* output,
				     unsigned long frames,
				     unsigned int channels,
				     SampleFormat sampleFormat)
{
  // size_t	sampleSize = g_sampleFormatSizes[sampleFormat];
  // size_t	framesLeft = m_buffer.maxFrame() - m_currentFrame;
  // size_t	sizeBuffer;
  // void*		ptr;

  // if (framesLeft < frames)
  //   sizeBuffer = framesLeft * channels * sampleSize;
  // else
  //   sizeBuffer = frames * channels * sampleSize;

  // ptr = (char*)m_buffer.data() + (m_currentFrame * channels * sampleSize);
  // if (m_currentFrame > m_buffer.maxFrame())
  //   m_currentFrame = m_buffer.maxFrame();
  // memcpy(output, ptr, sizeBuffer);

  // m_currentFrame += frames;
  // return (m_currentFrame < m_buffer.maxFrame());
  if (!m_frameQueue.empty())
    {
      m_coder->decode(static_cast<int16_t*>(output),
		      static_cast<unsigned char*>(m_frameQueue.front()));
      delete static_cast<char*>(m_frameQueue.front());
      m_frameQueue.pop();
    }
  else
    {
      memset(output, 0, frames * 4);
    }
  return (true);
}
