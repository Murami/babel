#include "PAAudioService.hh"
#include "PAAudioStream.hh"
#include "IAudioStreamListener.hh"

#include <stdint.h>

#define SAMPLE_RATE		(44100)
#define FRAMES_PER_BUFFER	(512)

#define SECONDS_RECORD		(5)
#define CHANNELS		(2)

class AudioBuffer
{
private:
  void*		m_data;
  unsigned int	m_channels;
  unsigned int	m_sampleRate;
  unsigned int	m_maxFrame;
  unsigned int	m_size;

public:
  AudioBuffer(unsigned int channels, unsigned int sampleRate, unsigned int frameCount)
  {
    AudioBuffer	buffer;

    m_channels = channels;
    m_sampleRate = sampleRate;
    m_maxFrame = frameCount;
    m_size = frameCount * channels * sizeof(uint16_t);
    m_data = new char[size];
  }

  AudioBuffer(unsigned int channels, unsigned int sampleRate,
	      unsigned int second, unsigned int millisecond)
  {
    m_channels = channels;
    m_sampleRate = sampleRate;
    m_maxFrame = (sampleRate * millisecond) / 1000 + sampleRate * second;
    m_size = buffer.maxFrame * channels * sizeof(uint16_t);
    m_data = new char[size];
  }

  ~AudioBuffer()
  {
    delete[] m_data;
  }

  unsigned int	channels() const
  {
    return (m_channels);
  }

  unsigned int	sampleRate() const
  {
    return (m_sampleRate);
  }

  unsigned int	maxFrame() const
  {
    return (m_maxFrame);
  }

  unsigned int	size() const
  {
    return (m_size);
  }

  void*		data() const
  {
    return (m_buffer);
  }
};

class AudioStreamListener : public IAudioStreamListener
{
protected:
  IAudioStream*		m_stream;
  IAudioService*	m_service;
  AudioBuffer*		m_buffer;

public:
  AudioStreamListener(AudioBuffer* buffer, IAudioService* service) :
    m_service(service),
    m_buffer(buffer)
  {
    m_stream =  new PAAudioStream();

    m_stream->setListener(this);
  }

  void	start()
  {
    m_stream->start();
  }

  void	run(unsigned int sleepTime)
  {
    this->start();
    while (this->active())
      m_service->sleep(sleepTime);
  }

  bool	isActive()
  {
    return (m_stream->isActive());
  }

  void	stop()
  {
    m_stream->stop();
  }

  int	onStreamRequest(const void* input, void* output, unsigned long framesPerBuffer)
  {
    /* SOME PIECE OF SHIT HERE */
  }
};

class AudioRecorder : public AudioStreamListener
{
private:
  IAudioStream*		stream;
  IAudioService*	service;

public:
  AudioRecorder(AudioBuffer* buffer, IAudioService* service) : AudioStreamListener(buffer, service)
  {
    m_stream->setInputStream(service->getDefaultInputDevice(), 2);
    m_stream->open(buffer->sampleRate(), 0);
  }

  ~AudioRecorder(){}
};

class AudioPlayer : public AudioStreamListener
{
private:

public:
  AudioPlayer(AudioBuffer* buffer, IAudioService* service) : AudioStreamListener(buffer, service)
  {
    m_stream->setOuptutStream(service->getDefaultOutputDevice(), 2);
    m_stream->open(buffer->sampleRate(), 0);
  }

  ~AudioPlayer(){}
};


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

int	main()
{
  //init service
  IAudioService*	service = new PAAudioService();
  service->initialize();

  //create audio buffer
  AudioBuffer	buffer(CHANNELS, SAMPLE_RATE, SECONDS_RECORD, 0);

  //create the recorder
  AudioRecorder	recorder(&buffer, service);

  //run it (each loop take 1000 ms)
  recorder.run(1000);

  //create the player
  AudioPlayer	player(&buffer, service);

  //run it (each loop take 1000 ms)
  player.run(1000);

  //release the service
  service->release();
  delete service;

  return (0);
}
