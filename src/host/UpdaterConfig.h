#ifndef sergomor_UpdaterConfig_h
#define sergomor_UpdaterConfig_h
#include "../utils/Storageable.h"

namespace sergomor
{

constexpr char UpdaterConfig_filename[] = "/updater.cfg";
struct UpdaterConfig : public Storageable<UpdaterConfig, UpdaterConfig_filename>
{
	String host;
	String fingerprint;
	uint8_t enable = 0;

	// Serializable
	virtual size_t length()
	{
		return host.length() + fingerprint.length() + sizeof(enable) + 2;
	}

	virtual OStreambuff &output(OStreambuff &os)
	{
		return os << host << enable << fingerprint;
	}

	virtual IStreambuff &input(IStreambuff &is)
	{
		return is >> host >> enable >> fingerprint;
	}
};
}; // namespace sergomor
#endif