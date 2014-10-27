template<class UserData, unsigned int BufferSize>
AsyncClient<UserData, BufferSize>::AsyncClient(IAsyncService& service)
{
}

template<class UserData, unsigned int BufferSize>
AsyncClient<UserData, BufferSize>::~AsyncClient()
{
}

template<class UserData, unsigned int BufferSize>
void	AsyncClient<UserData, BufferSize>::addListener(AsyncListener& listener)
{
}

template<class UserData, unsigned int BufferSize>
void	AsyncClient<UserData, BufferSize>::deleteListener(AsyncListener& listener)
{
}

template<class UserData, unsigned int BufferSize>
void	AsyncClient<UserData, BufferSize>::peekData(void* buffer, size_t size)
{
}

template<class UserData, unsigned int BufferSize>
void	AsyncClient<UserData, BufferSize>::readData(void* buffer, size_t size)
{
}

template<class UserData, unsigned int BufferSize>
void	AsyncClient<UserData, BufferSize>::writeData(void* buffer, size_t size)
{
}

template<class UserData, unsigned int BufferSize>
void	AsyncClient<UserData, BufferSize>::notifyRead()
{
}
