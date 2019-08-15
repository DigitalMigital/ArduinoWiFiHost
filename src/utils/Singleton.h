#ifndef sergomor_Singleton_h
#define sergomor_Singleton_h

namespace sergomor
{

template <typename T>
class Singleton
{
public:
	static T &instance();

	Singleton(const Singleton &) = delete;
	Singleton &operator=(const Singleton) = delete;

protected:
	Singleton() {}
};

template <typename T>
T &Singleton<T>::instance()
{
	static T instance;
	return instance;
};
}; // namespace sergomor
#endif