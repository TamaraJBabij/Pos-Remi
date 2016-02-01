//Currently a static list of all config variables, will later be imported from text file
//Uses a singleton design pattern, meaning the settings are accessible globally without re-loading variables
class Config
{
	public:
		//this is the only 
		static Settings& getSettings();
		//we won't implement these two functions, but declaring them here prevents the compiler from automatically generating copy methods
		Config(Config const&copy);
		Config& operator=(Config const& copy);

		Setting settings;
	private:
		Config();
};