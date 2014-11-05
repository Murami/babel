#findef AUDIORECORDER_HH
#define AUDIORECORDER_HH

class AudioRecorder : public AudioStreamListener
{
private:
  IAudioStream*		stream;
  IAudioService*	service;

public:
  AudioRecorder(AudioBuffer* buffer, IAudioService* service,
		unsigned long framesMax) : AudioStreamListener(buffer, service, framesMax)
  {
    m_stream->setInputStream(service->getDefaultInputDevice(), 2);
    m_stream->open(buffer->sampleRate(), 0);
  }

  ~AudioRecorder(){}
};

#endif /* AUDIORECORDER_HH */
