#include "AudioBuffer.hh"
#include "AudioRecorder.hh"
#include "PAAudioInputStream.hh"
#include "OpusAudioCoder.hh"
#include "SampleFormat.hh"
#include "BabelCoreClient.hh"

#include <istream>
#include <iostream>
#include <cstring>

AudioRecorder::AudioRecorder(BabelCoreClient& core) :
  m_core(core)
{
  m_coder = new OpusAudioCoder(48000, 2, 64000);
  m_stream = new PAAudioInputStream(2, 44100, 960, Int16, this);
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

void	AudioRecorder::pushFrame(void* frame)
{
  m_mutex.lock();
  m_frameQueue.push(frame);
  m_mutex.unlock();
}

void*	AudioRecorder::popFrame()
{
  void*	frame;

  m_mutex.lock();
  frame = m_frameQueue.front();
  m_frameQueue.pop();
  m_mutex.unlock();
  return (frame);
}

int	AudioRecorder::nextFrameSize()
{
  uint32_t	size;

  m_mutex.lock();
  memcpy(&size, m_frameQueue.front(), 4);
  m_mutex.unlock();
  return (size + 4);
}

int	AudioRecorder::size()
{
  int size;

  m_mutex.lock();
  size = m_frameQueue.size();
  m_mutex.unlock();
  return (size);
}

int	AudioRecorder::onStreamRequest(const void* input,
				       unsigned long,
				       unsigned int,
				       SampleFormat)
{
  unsigned char		cbits[4096];
  size_t		size;
  char*			frame;
  int			total_size = 0;

  size = m_coder->encode(static_cast<const int16_t*>(input), cbits);
  frame = new char[size];
  memcpy(frame, cbits, size);
  pushFrame(frame);

  if (this->size() >= 10)
    {
      char	buffer[RAW_SIZE];

      for (int i = 0; i != 10; i++)
	{
	  int	_size = nextFrameSize();
	  void*	_frame = popFrame();

	  memcpy(buffer + total_size, _frame, _size);
	  total_size += _size;
	  delete static_cast<char*>(_frame);
	}
      m_core.sendAudioFrame(buffer, total_size);
    }
  return (true);
}
