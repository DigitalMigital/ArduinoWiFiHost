#ifndef sergomor_Updater_h
#define sergomor_Updater_h

//const char github_fingerprint[] = "CA 06 F5 6B 25 8B 7A 0D 4F 2B 05 47 09 39 47 86 51 15 19 84";
// raw.githubusercontent.com
constexpr char githubusercontent_fingerprint[] = "CC:AA:48:48:66:46:0E:91:53:2C:9C:7C:23:2A:B1:74:4D:29:9D:33";
constexpr char githubusercontent_host[] = "https://raw.githubusercontent.com/sergomor/loundry_bin/master";

namespace sergomor
{

#define NUM_WEB_FILES 2

class Updater
{
public:
	static void begin();

private:
	static void updateWebServerFiles();
	static const char *webserver_path;
	static const char *binary_path;
	static const char *const web_files[NUM_WEB_FILES];
};
}; // namespace sergomor
#endif