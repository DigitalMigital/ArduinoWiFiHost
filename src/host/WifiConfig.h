#ifndef sergomor_WifiConfig_h
#define sergomor_WifiConfig_h

#include "../utils/Storageable.h"
#include "../utils/Singleton.h"

namespace sergomor
{

constexpr char WifiConfig_filename[] = "/wifi.cfg";
struct WifiConfig : public Storageable<WifiConfig, WifiConfig_filename>, public Singleton<WifiConfig>
{

	String ssid;
	String password;
	// SoftAp mode config
	//String ap_ipaddress;
	//String ap_ssid;
	//String ap_password;

	WifiConfig()
	{
		ssid = "";
		password = "";
	}

	// Serializable
	virtual size_t length()
	{
		return ssid.length() + password.length() + 2;
	}

	virtual OStreambuff &output(OStreambuff &os)
	{
		return os << ssid << password;
	}

	virtual IStreambuff &input(IStreambuff &is)
	{
		return is >> ssid >> password;
	}
};
}; // namespace sergomor
#endif