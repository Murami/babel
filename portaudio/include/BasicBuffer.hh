#ifndef BASICBUFFER_HH
#define BASICBUFFER_HH

class BasicBuffer
{
private:
  size_t	m_size;
  size_t	m_capacity;
  char*		m_buffer;

public:
  BasicBuffer(size_t capacity);
  ~BasicBuffer();

  size_t	size() const;
  size_t	capacity() const;

  void		operator<<(const BasicBuffer& buffer);
  void		operator>>(BasicBuffer& buffer);
};

#endif /* BASICBUFFER_HH */
