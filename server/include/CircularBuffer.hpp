#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <cstdlib>

template<unsigned int BufferSize = 1024>
class CircularBuffer
{
private:
  char		m_buffer[BufferSize];
  size_t	m_size;
  size_t	m_start;
  size_t	m_end;

public:
  CircularBuffer();
  ~CircularBuffer();

  void		clear();
  unsigned int	getRemainingSize() const;
  unsigned int	getSize() const;
  bool		isEmpty() const;
  bool		isFull() const;
  unsigned int	peek(void* dest, size_t size);
  unsigned int	read(void* dest, size_t size);
  unsigned int	write(const void* src, size_t size);
};

#include "CircularBuffer.tpp"

#endif /* CIRCULARBUFFER_HPP */
