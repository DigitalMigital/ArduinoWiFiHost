#ifndef sergomor_WifiConfig_h
#define sergomor_WifiConfig_h

#include "../utils/Storageable.h"

namespace sergomor
{

constexpr char WifiConfig_filename[] = "/wifi.cfg";
struct WifiConfig : public Storageable<WifiConfig, WifiConfig_filename>
{

	String ssid;
	String password;
	// SoftAp mode config
	String ap_ipaddress;
	String ap_ssid;
	String ap_password;

	// Serializable
	virtual size_t length() {
		return ssid.length() + password.length()
		+ ap_ssid.length() +  ap_password.length() + ap_ipaddress.length() + 5;
	}

	virtual OStreambuff &output(OStreambuff &os)
	{
		return os << ssid << password << ap_ipaddress << ap_ssid << ap_password;
	}

	virtual IStreambuff &input(IStreambuff &is)
	{
		return is >> ssid >> password >> ap_ipaddress >> ap_ssid >> ap_password;
	}
};
}; // namespace sergomor
#endif