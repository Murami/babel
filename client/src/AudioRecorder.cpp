#include "AudioBuffer.hh"
#include "AudioRecorder.hh"
#include "PAAudioInputStream.hh"
#include "OpusAudioCoder.hh"
#include "SampleFormat.hh"
#include "BabelCoreClient.hh"

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
  // return (960);
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
				       unsigned long frames,
				       unsigned int /*channels*/,
				       SampleFormat /*sampleFormat*/)
{
  unsigned char		cbits[4096];
  size_t		size;
  char*			frame;

  size = m_coder->encode(static_cast<const int16_t*>(input), cbits);
  frame = new char[size];
  memcpy(frame, cbits, size);
  m_core.sendAudioFrame(frame, size);
  return (true);
}
