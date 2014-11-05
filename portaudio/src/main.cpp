#include "PAAudioService.hh"
#include "APAAudioStream.hh"
#include "PAAudioInputStream.hh"
#include "PAAudioOutputStream.hh"

#include <stdint.h>

// // #define SAMPLE_RATE		(44100)
// #define FRAMES_PER_BUFFER	(512)

// #define SECONDS_RECORD		(5)
// #define CHANNELS		(2)

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
  return 0;
}
