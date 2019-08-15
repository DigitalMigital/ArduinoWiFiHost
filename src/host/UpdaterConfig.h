#ifndef sergomor_UpdaterConfig_h
#define sergomor_UpdaterConfig_h
#include "../utils/Storageable.h"
#include "../utils/Singleton.h"

namespace sergomor
{

constexpr char UpdaterConfig_filename[] = "/updater.cfg";
struct UpdaterConfig : public Storageable<UpdaterConfig, UpdaterConfig_filename>, public Singleton<UpdaterConfig>
{
	String host;
	String fingerprint;
	uint8_t enable = 0;
	String webfiles_version;

	// Serializable
	virtual size_t length()
	{
		return host.length() + fingerprint.length() + webfiles_version.length() + sizeof(enable) + 3;
	}

	virtual OStreambuff &output(OStreambuff &os)
	{
		return os << host << enable << webfiles_version << fingerprint;
	}

	virtual IStreambuff &input(IStreambuff &is)
	{
		return is >> host >> enable >> webfiles_version >> fingerprint;
	}
};
}; // namespace sergomor
#endif