#include "circular_buffer.hh"

#include <iostream>

#include <algorithm>
#include <iterator>

circular_buffer::circular_buffer() :
  m_begin(m_buffer.begin()), m_end(m_buffer.begin()) {}

circular_buffer::circular_buffer(size_t size) :
  m_buffer(size, 0), m_begin(m_buffer.begin()), m_end(m_buffer.begin()) {}

circular_buffer::~circular_buffer() {}

void	circular_buffer::clear() { m_buffer.clear(); }

size_t	circular_buffer::size() const
{
  size_t	distancebegin = std::distance(m_buffer.begin(), this->cbegin());
  size_t	distanceend = std::distance(m_buffer.begin(), this->cend());

  if (distanceend < distancebegin)
    distanceend += this->capacity();
  return (distanceend - distancebegin);
}

size_t	circular_buffer::capacity() const
{
  return (m_buffer.size());
}

bool	circular_buffer::empty() const { return (this->size() == 0); }

void	circular_buffer::resize(size_t size)
{
  size_t	enddistance;

  enddistance = this->size();
  std::rotate(m_buffer.begin(), m_begin, m_buffer.end());
  m_buffer.resize(size);
  m_begin = m_buffer.begin();
  m_end = m_buffer.begin() + enddistance;
}

size_t	circular_buffer::peek(byte_buffer::iterator begin, byte_buffer::iterator end) const
{
  byte_buffer::const_iterator	it;
  byte_buffer::iterator itdest;

  itdest = begin;
  for (it = m_begin; it != m_end && it != m_buffer.end() && itdest != end; it++, itdest++)
    *itdest = *it;
  if (it != m_end && itdest != end)
    for (it = m_buffer.begin(); it != m_end && itdest != end; it++, itdest++)
      *itdest = *it;
  return (std::distance(begin, itdest));
}

size_t	circular_buffer::read(byte_buffer::iterator begin, byte_buffer::iterator end)
{
  size_t	distance;
  size_t	copied;

  copied = this->peek(begin, end);
  distance = (std::distance(m_buffer.begin(), m_begin) + copied) % this->capacity();
  m_begin = m_buffer.begin() + distance;
  return (copied);
}

size_t	circular_buffer::write(byte_buffer::iterator begin, byte_buffer::iterator end)
{
  size_t	size = std::distance(begin, end);

  if (size + this->size() > this->capacity())
    this->resize(size + this->size());

  byte_buffer::iterator	it;
  byte_buffer::iterator itdest;

  itdest = begin;
  int	i = 0;
  for (it = m_end; (it != m_begin || it == m_end) && it != m_buffer.end() && itdest != end; it++, itdest++, i++);
    *it = *itdest;
  if (it != m_begin && itdest != end)
    for (it = m_buffer.begin(); it != m_begin && itdest != end; it++, itdest++);
      *it = *itdest;

  size_t	copied = std::distance(begin, itdest);
  size_t	distance = (std::distance(m_buffer.begin(), m_end) + copied - 1) % this->capacity() + 1;

  m_end = m_buffer.begin() + distance;
  return (copied);
}

byte_buffer::const_iterator	circular_buffer::cbegin() const
{
  return (m_begin);
}

byte_buffer::const_iterator	circular_buffer::cend() const
{
  return (m_end);
}
