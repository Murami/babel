#ifndef _BUFFER_HH_
# define _BUFFER_HH_

struct		Buffer
{
  char*		data[4096];
  unsigned int	size;
};

#endif /* _BUFFER_HH_ */
