#ifndef CIRCULARBUFFER_HH
#define CIRCULARBUFFER_HH

#include <cstdlib>
#include <cstring>

class CircularBuffer
{
private:
  char*		m_buffer;
  size_t	m_size;
  size_t	m_start;
  size_t	m_end;
  size_t	m_max_size;

public:
  CircularBuffer(size_t size);
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

#endif /* CIRCULARBUFFER_HH */
