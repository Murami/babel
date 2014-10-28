#include <cstring>

//***//
// #include <iostream>

template<unsigned int BufferSize>
CircularBuffer<BufferSize>::CircularBuffer() :
  m_size(0), m_start(0), m_end(0)
{
}

template<unsigned int BufferSize>
CircularBuffer<BufferSize>::~CircularBuffer()
{
}

template<unsigned int BufferSize>
void		CircularBuffer<BufferSize>::clear()
{
  m_size = 0;
  m_start = 0;
  m_end = 0;
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::getRemainingSize() const
{
  return (BufferSize - m_size);
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::getSize() const
{
  return (m_size);
}

template<unsigned int BufferSize>
bool		CircularBuffer<BufferSize>::isEmpty() const
{
  return (m_size == 0);
}

template<unsigned int BufferSize>
bool		CircularBuffer<BufferSize>::isFull() const
{
  return (m_size == BufferSize);
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::peek(void* dest, size_t size)
{
  unsigned int	maxIndex = BufferSize - 1;
  unsigned int	cpySize;
  char*		destBytes = static_cast<char*>(dest);

  if (m_size <= size)
    size = m_size;

  cpySize = maxIndex - m_start;
  if (size < cpySize)
    cpySize = size;
  // std::cout << "size:" << size << std::endl;
  // std::cout << "DBG1:" << cpySize << std::endl;
  memcpy(destBytes, m_buffer + m_start, cpySize);

  // std::cout << "DBG2:" << cpySize << std::endl;
  memcpy(destBytes + cpySize, m_buffer, size - cpySize);

  return (size);
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::read(void* dest, size_t size)
{
  unsigned int	copiedSize;

  copiedSize = peek(dest, size);
  m_size -= copiedSize;
  m_start = (m_start + copiedSize) % BufferSize;
  return (copiedSize);
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::write(const void* src, size_t size)
{
  unsigned int	maxIndex = BufferSize - 1;
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
  m_end = (m_end + size) % BufferSize;

  return (size);
}
