#include <cstring>
#include "OpusAudioCoder.hh"

#include <iostream>
#include <exception>
#include <stdexcept>

OpusAudioCoder::OpusAudioCoder(size_t samplingRate, size_t nbrChannels, size_t bitRate)
{
  int error;

  m_samplingRate	= samplingRate;
  m_nbrChannels		= nbrChannels;
  m_bitRate		= bitRate;
  m_encoder		= opus_encoder_create(m_samplingRate, m_nbrChannels, OPUS_APPLICATION_AUDIO, &error);
  std::cout << "=== opus_encoder_create(" << m_samplingRate << ", " <<  m_nbrChannels << ", OPUS_APPLICATION_VOIP) ===" << std::endl;
  if (error < 0) throw std::runtime_error("opus encoder create");
  m_decoder		= opus_decoder_create(m_samplingRate, m_nbrChannels, &error);
  if (error < 0) throw std::runtime_error("opus encoder create");
}

OpusAudioCoder::~OpusAudioCoder()
{
  opus_encoder_destroy(m_encoder);
  opus_decoder_destroy(m_decoder);
}

uint32_t	 OpusAudioCoder::decode(int16_t* audioRaw, const unsigned char* packetData)
{
  uint32_t		frameSize;
  uint32_t		nbBytes;
  // int16_t*		ptr;

  // ptr = static_cast<int16_t*>(static_cast<void*>(packetData));

  memcpy(&nbBytes, packetData, 4);
  memset(audioRaw, 0, 960);
  frameSize = opus_decode(m_decoder, packetData + 4, nbBytes - 4, audioRaw, 960, 0);
  return (frameSize);
}

uint32_t	OpusAudioCoder::encode(const int16_t* audioRaw, unsigned char* packetData)
{
  uint32_t	nbBytes;

  nbBytes = opus_encode(m_encoder, audioRaw, 960, packetData + 4, 500);
  // std::cout << "[ ENCODER ] : Returning " << nbBytes << std::endl;
  memcpy(packetData, &nbBytes, 4);
  return (nbBytes + 4);
}

void OpusAudioCoder::setSamplingRate(size_t samplingRate)
{
  m_samplingRate = samplingRate;
}

void OpusAudioCoder::setNbrChannels(size_t nbrChannels)
{
  m_nbrChannels = nbrChannels;
}

void OpusAudioCoder::setBitRate(size_t bitRate)
{
  m_bitRate = bitRate;
}

size_t	OpusAudioCoder::getSamplingRate() const
{
  return (m_samplingRate);
}

size_t	OpusAudioCoder::getNbrChannels() const
{
  return (m_nbrChannels);
}

size_t	OpusAudioCoder::getBitRate() const
{
  return (m_bitRate);
}
