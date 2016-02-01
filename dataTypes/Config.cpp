#include "Config.h"
#include <libconfig.hh>
#include <iostream>

Config::Config(){
	//here we will load all the settings from a config file.
	//this will only ever be called ONCE
	libconfig::Config cfg;
	cfg.readFile("config.cfg");
	settings = cfg.getRoot();
	cout<<"Config file loaded!"<<endl;
}

static Settings& Config::getSettings(){
	//by using a static variable here, the constructor will be called the first time,
	//but not on any subsequent calls to getInstance.
	static Config c;
	return c.settings;
}

