#ifndef SETTINGSMANAGER_H_
#define SETTINGSMANAGER_H_

#include <map>
#include "../../util/patterns/singleton.h"
#include "../../util/patterns/dator.h"
#include "../../util/memory/memoryManagedObject.h"

class SettingsManager{
	
	public:
		SettingsManager();
		virtual ~SettingsManager();

		void registerVariable(std::string &name, MemoryManagedPointer<BaseDator> &var);
		void setVariable(std::string &name, std::string &value, int bias=0);

		void createStandardSettings();
		void destroyStandardSettings();

		void parseSetting(std::string str);
		void parseFile(std::string filename);

	protected:
		std::map<std::string, MemoryManagedPointer<BaseDator> > settingMap;
};

typedef singleton<SettingsManager> SETTINGS;

#endif /*SETTINGSMANAGER_H_*/
