#ifndef SAMPLEFORMAT_HH
#define SAMPLEFORMAT_HH

#include <cstdlib>

enum SampleFormat
  {
    Float32 = 0,
    Int32,
    Int24,
    Int16,
    Int8,
    UInt8
  };

extern size_t	g_sampleFormatSizes[];

#endif /* SAMPLEFORMAT_HH */
