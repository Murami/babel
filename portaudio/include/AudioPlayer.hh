#ifndef AUDIOPLAYER_HH
#define AUDIOPLAYER_HH

class AudioPlayer : public AudioOperator
{
private:

public:
  AudioPlayer(AudioBuffer* buffer, IAudioService* service,
	      unsigned long framesMax);
  // 	      : AudioStreamListener(buffer, service, framesMax)
  // {
  //   m_stream->setOuptutStream(service->getDefaultOutputDevice(), 2);
  //   m_stream->open(buffer->sampleRate(), 0);
  // }

  ~AudioPlayer();
// {}
};


#endif /* AUDIOPLAYER_HH */
