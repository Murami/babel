#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP


template<unsigned int BufferSize = 1024>
class CircularBuffer
{
private:
  char		m_buffer[BufferSize];
  size_t	m_size;
  size_t	m_start;

public:
  CircularBuffer();
  ~CircularBuffer();

  void		clear();
  unsigned int	getRemainingSize();
  unsigned int	getSize();
  bool		isEmpty();
  bool		isFull();
  unsigned int	peekData(void* dest, size_t size);
  unsigned int	readData(void* dest, size_t size);
  unsigned int	writeData(void* src, size_t size);
};

#include "CircularBuffer.tpp"

#endif /* CIRCULARBUFFER_HPP */
