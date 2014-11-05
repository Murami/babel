#include "AudioBuffer.hh"
#include "PAAudioService.hh"
#include "AudioRecorder.hh"
#include "AudioPlayer.hh"
// #include "APAAudioStream.hh"
// #include "PAAudioInputStream.hh"
// #include "PAAudioOutputStream.hh"

#include <stdint.h>
#include <unistd.h>


#include <iostream>

#define SAMPLE_RATE		(44100)
#define FRAMES_PER_BUFFER	(512)

#define SECONDS_RECORD		(10)
#define CHANNELS		(2)

// int	main()
// {
//   //init service
//   IAudioService*	service = new PAAudioService();
//   service->initialize();

//   //create audio buffer
//   AudioBuffer	buffer(CHANNELS, SAMPLE_RATE, SECONDS_RECORD, 0);

//   //create the recorder
//   AudioRecorder	recorder(&buffer, service);

//   //run it (each loop take 1000 ms)
//   recorder.run(1000);

//   //create the player
//   AudioPlayer	player(&buffer, service);

//   //run it (each loop take 1000 ms)
//   player.run(1000);

//   //release the service
//   service->release();
//   delete service;

//   return (0);
// }

int	main()
{
  // init the service
  PAAudioService::getInstance()->initialize();

  // create the buffer
  AudioBuffer	buffer(CHANNELS, SAMPLE_RATE, SECONDS_RECORD, 0, Int16);

  // create the recorder
  AudioRecorder	recorder(buffer);

  // run the recorder until it finish by itself
  std::cout << "Debut Record" << std::endl;
  recorder.start();
  while (recorder.active())
    usleep(1000);
  recorder.stop();
  std::cout << "Fin Record" << std::endl;

  // create the player
  AudioPlayer	player(buffer);


  // run the player until it finish by itself
  std::cout << "Debut Play" << std::endl;
  player.start();
  while (player.active())
    usleep(1000);
  player.stop();
  std::cout << "Fin Play" << std::endl;

  // release the service
  PAAudioService::getInstance()->release();
  return (0);
}
