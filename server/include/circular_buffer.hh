#ifndef CIRCULARBUFFER_HH
#define CIRCULARBUFFER_HH

#include <cstdlib>
#include <vector>

typedef char byte;
typedef std::vector<byte> byte_buffer;

class circular_buffer
{
private:
  byte_buffer			m_buffer;
  byte_buffer::iterator		m_begin;
  byte_buffer::iterator		m_end;

public:
  circular_buffer();
  circular_buffer(size_t size);
  ~circular_buffer();

  size_t	size() const;
  size_t	capacity() const;
  bool		empty() const;

  void		resize(size_t size);
  void		clear();

  // void		peek(byte_buffer& dest);
  // void		read(byte_buffer& dest);
  // void		write(byte_buffer& src);
  size_t	peek(byte_buffer::iterator begin, byte_buffer::iterator end) const;
  size_t	read(byte_buffer::iterator begin, byte_buffer::iterator end);
  size_t	write(byte_buffer::iterator begin, byte_buffer::iterator end);

private:
  byte_buffer::const_iterator	cbegin() const;
  byte_buffer::const_iterator	cend() const;
};

#endif /* CIRCULARBUFFER_HH */
