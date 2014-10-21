//
// CircularBuffer.hh for  in /home/anto/workspace/git/babel/server
//
// Made by anto
// Login   <anto@epitech.net>
//
// Started on  Tue Oct 21 22:11:06 2014 anto
// Last update Tue Oct 21 22:17:45 2014 anto
//

#ifndef CIRCULARBUFFER_HH
#define CIRCULARBUFFER_HH

template<unsigned int BufferSize>
class CircularBuffer
{
public:
  CircularBuffer();
  ~CircularBuffer();

  unsigned int	peekData(void* destination, size_t size);
  unsigned int	readData(void* destination, size_t size);
  unsigned int	writeData(void* source, size_t size);

  unsigned int	getSize() const;
  unsigned int	getRemainingSize() const;

  bool		isEmpty() const;
  bool		isFull() const;

  void		clear();

private:
  char[BufferSize]	m_buffer;
  size_t		m_size;
  size_t		m_start;
};

#endif /* CIRCULARBUFFER_HH */
