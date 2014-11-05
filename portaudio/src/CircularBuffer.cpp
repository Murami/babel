#include "CircularBuffer.hh"
#include <cstring>

CircularBuffer::CircularBuffer(capacity) :
  m_size(0), m_start(0), m_end(0), m_capacity(capacity)
{
  m_buffer = new char[m_capacity];
}

CircularBuffer::~CircularBuffer()
{
  delete[] m_buffer;
}

void		CircularBuffer::clear()
{
  m_size = 0;
  m_start = 0;
  m_end = 0;
}

unsigned int	CircularBuffer::size() const
{
  return (m_size);
}

bool		CircularBuffer::empty() const
{
  return (m_size == 0);
}

unsigned int	CircularBuffer::peek(void* dest, size_t size)
{
  unsigned int	maxIndex = m_capacity - 1;
  unsigned int	cpySize;
  char*		destBytes = static_cast<char*>(dest);

  if (m_size <= size)
    size = m_size;
  cpySize = maxIndex - m_start;
  if (size < cpySize)
    cpySize = size;
  memcpy(destBytes, m_buffer + m_start, cpySize);
  memcpy(destBytes + cpySize, m_buffer, size - cpySize);
  return (size);
}

unsigned int	CircularBuffer::read(void* dest, size_t size)
{
  unsigned int	copiedSize;

  copiedSize = peek(dest, size);
  m_size -= copiedSize;
  m_start = (m_start + copiedSize) % m_capacity;
  return (copiedSize);
}

unsigned int	CircularBuffer::write(const void* src, size_t size)
{
  unsigned int	maxIndex = m_capacity - 1;
  unsigned int	cpySize;
  const char*	srcBytes = static_cast<const char*>(src);

  if (getRemainingSize() < size)
    size = getRemainingSize();
  cpySize = maxIndex - m_end;
  if (size < cpySize)
    cpySize = size;
  memcpy(m_buffer + m_end, srcBytes, cpySize);
  memcpy(m_buffer, srcBytes + cpySize, size - cpySize);
  m_size += size;
  m_end = (m_end + size) % m_capacity;
  return (size);
}
