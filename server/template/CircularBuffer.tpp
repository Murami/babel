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
unsigned int	CircularBuffer<BufferSize>::getRemainingSize()
{
  return (BufferSize - m_size);
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::getSize()
{
  return (m_size);
}

template<unsigned int BufferSize>
bool		CircularBuffer<BufferSize>::isEmpty()
{
  return (m_size == 0);
}

template<unsigned int BufferSize>
bool		CircularBuffer<BufferSize>::isFull()
{
  return (m_size == BufferSize);
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::peekData(void* dest, size_t size)
{
  unsigned int	maxIndex = BufferSize - 1;
  unsigned int	cpySize;

  if (m_size <= size)
    size = m_size;

  cpySize = maxIndex - start;
  if (m_size < cpySize)
    cpySize = m_size;
  memcpy(dest, buffer + start, cpySize);

  cpySize = size - cpySize;
  memcpy(dest, buffer, cpySize);

  return (size);
}

template<unsigned int BufferSize>
unsigned int	CircularBuffer<BufferSize>::readData(void* dest, size_t size)
{
  unsigned int	copiedSize;

  copiedSize = peekData(dest, size);
  m_size -= copiedSize;
  m_start = (m_start + copiedSize) % BufferSize;
  return (copiedSize);
}

template<unsigned int BufferSize>
CircularBuffer<BufferSize>::writeData(void* src, size_t size)
{
  unsigned int	maxIndex = BufferSize - 1;
  unsigned int	cpySize;

  if (getRemainingSize() < size)
    size = getRemainingSize();

  cpySize = maxIndex - m_end;
  if (size < cpySize)
    cpySize = size;
  memcpy(buffer + m_end, src, cpySize);

  cpySize = size - cpySize;
  memcpy(buffer, src, cpySize);

  m_size += size;
  m_end = (m_end + size) % BufferSize;

  return (size);
}
