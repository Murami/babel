#include "AudioBuffer.hh"
#include "AudioRecorder.hh"
#include "PAAudioInputStream.hh"
#include "OpusAudioCoder.hh"

#include "SampleFormat.hh"

#include <iostream>
#include <cstring>

AudioRecorder::AudioRecorder()
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
  //Mutex ICI
  m_frameQueue.push(frame);
}

void*	AudioRecorder::popFrame()
{
  //Mutex ICI
  void*	frame;

  frame = m_frameQueue.front();
  m_frameQueue.pop();
  return (frame);
}

int	AudioRecorder::nextFrameSize() const
{
  //Mutex ICI
  uint32_t	size;

  memcpy(&size, m_frameQueue.front(), 4);
  return (size);
}

int	AudioRecorder::size() const
{
  //Mutex ICI
  return (m_frameQueue.size());
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
  pushFrame(frame);
  return (true);
}
