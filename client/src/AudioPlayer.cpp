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
  m_mutex.lock();
  m_frameQueue.push(frame);
  m_mutex.unlock();
}

void  AudioPlayer::pushFrames(void* frames, size_t size)
{
  void*		frame;
  uint32_t	_size;

  for (uint32_t i = 0; i < size;)
    {
      // ####### PROBLEME DE SIZE ICI
      memcpy(&_size, static_cast<char*>(frames) + i, 4);
      frame = new char[_size];
      memcpy(frame, static_cast<char*>(frames) + i, _size + 4);
      this->pushFrame(frame);
      i += _size;
    }
}

void*	AudioPlayer::popFrame()
{
  void*	frame;

  m_mutex.lock();
  frame = m_frameQueue.front();
  m_frameQueue.pop();
  m_mutex.unlock();
  return (frame);
}

int	AudioPlayer::nextFrameSize()
{
  uint32_t	size;

  m_mutex.lock();
  memcpy(&size, m_frameQueue.front(), 4);
  m_mutex.unlock();
  return (size + 4);
}

int	AudioPlayer::size()
{
  int size;

  m_mutex.lock();
  size = m_frameQueue.size();
  m_mutex.unlock();
  return (size);
}

int	AudioPlayer::onStreamRequest(void* output,
				     unsigned long frames,
				     unsigned int channels,
				     SampleFormat sampleFormat)
{
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
