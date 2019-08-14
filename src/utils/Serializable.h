#ifndef sergomor_Serializable_h
#define sergomor_Serializable_h

namespace sergomor
{

template <typename T>
class Serializable
{
public:
	virtual size_t length() = 0;
	//virtual OStreambuff &output(OStreambuff &) = 0;
	//virtual IStreambuff &input(IStreambuff &) = 0;

	//friend OStreambuff &operator<<(OStreambuff &os, T &t) { return t.output(os); }
	//friend IStreambuff &operator>>(IStreambuff &is, T &t) { return t.input(is); };
};
} // namespace sergomor
#endif