#include <exception>
#include "Babel.hh"
#include "BabelProtocol.hh"

int	main()
{
  try
    {
      Babel babel(PORT);

      babel.run();
    }
  catch (const std::runtime_error& e)
    {
      std::cout << "Not supported exception : "  << e.what() << std::endl;
    }
  return (0);
}
