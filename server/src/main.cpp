#include "circular_buffer.hh"

#include <iostream>

/* CIRCULAR BUFFER TEST */

void	basic_test()
{
  // circular_buffer	test;
  // char			buff[5] = {0};

  // std::cout << "write : " << test.write((char*)"toto", 5) << std::endl;
  // std::cout << "read : " << test.read(buff, 5) <<  std::endl;
  // std::cout << buff << std::endl;
}

void	fill_test()
{
  // circular_buffer	test;
  // char			nb;

  // for (int i = 0; i < 16; i++)
  //   {
  //     char tmp = (char)i;
  //     test.write(&tmp, 1);
  //   }
  // std::cout << "write test passed" << std::endl;
  // for (int i = 0; i < 16; i++)
  //   {
  //     test.read(&nb, 1);
  //     std::cout << (int)nb << std::endl;
  //   }
  // std::cout << "read test passed" << std::endl;
}

void	fill_loop_test()
{
  // circular_buffer	test;
  // char			buffer[1024];

  // std::cout << "write : " << test.write("ceci est test", 14) << std::endl;
  // std::cout << "read : " << test.read(buffer, 7) << std::endl;
  // std::cout << buffer << std::endl;
  // std::cout << "write : " << test.write("yolomod", 8) << std::endl;
  // std::cout << "read: " << test.read(buffer, 16) << std::endl;
  // std::cout << buffer << "\\0" << buffer + 7 <<std::endl;
  circular_buffer	buffer(2);
  byte_buffer		buffer_local(10);

  // std::cout << buffer.size() << std::endl;
  buffer.write(buffer_local.begin(), buffer_local.end());
  std::cout << "** size ** : " << buffer.size() << std::endl;
  std::cout << std::endl;
  std::cout << "--------" << std::endl;
  buffer.write(buffer_local.begin(), buffer_local.end());
  std::cout << "** size ** : " << buffer.size() << std::endl;
}

int	main()
{
  // fill_test();
  fill_loop_test();
  return (0);
}
