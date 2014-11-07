#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <cstdlib>

class CircularBuffer
{
private:
  char*		m_buffer;
  size_t	m_capacity;
  size_t	m_size;
  size_t	m_start;
  size_t	m_end;

public:
  CircularBuffer(size_t capacity);
  ~CircularBuffer();

  void		clear();
  size_t	size() const;
  size_t	capacity() const;
  bool		empty() const;
  size_t	peek(void* dest, size_t size) const;
  size_t	read(void* dest, size_t size);
  size_t	write(const void* src, size_t size);
  size_t	write(char c);
};

#endif /* CIRCULARBUFFER_HPP */
