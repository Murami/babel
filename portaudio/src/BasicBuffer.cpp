#include "BasicBuffer.hh"

BasicBuffer::BasicBuffer(size_t capacity) :
  m_size(0),
  m_capacity(size)
{
  m_buffer = new char[size];
}

BasicBuffer::~BasicBuffer()
{
  delete[] m_buffer;
}

size_t	BasicBuffer::size() const
{
  return (m_size);
}

size_t	BasicBuffer::capacity() const
{
  return (m_capacity);
}

void	BasicBuffer::operator<<(const BasicBuffer& buffer)
{
}

void	BasicBuffer::operator>>(BasicBuffer& buffer)
{
}
