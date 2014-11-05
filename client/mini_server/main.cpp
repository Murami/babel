#include	<iostream>
#include	<SFML/Network.hpp>
#include	"Protocol.hh"

int		main()
{
  sf::TcpSocket	socket;
  sf::TcpListener listener;

  if (listener.listen(1235) != sf::Socket::Done)
    {
      std::cerr << "Listening error on port 1235" << std::endl;
      return (-1);
    }

  if (listener.accept(socket) != sf::Socket::Done)
    {
      std::cerr << "Accept error" << std::endl;
      return (-2);
    }

  NET::Header header;

  header.type = NET::T_KO_REGISTER;
  header.size = 0;
  if (socket.send(&header, sizeof(header)) != sf::Socket::Done)
    {
      std::cerr << "Error while sending data" << std::endl;
      return (-3);
    }
  while (42);
  return (0);
}
