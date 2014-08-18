#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H

#include <string>
#include <map>

class EditorSettings
{
	typedef std::map<std::wstring, std::wstring> PropertyMap;
	bool loadFile();
	std::wstring fileName;
	PropertyMap propertyMap;
public:
	EditorSettings(std::wstring fileName);
	std::wstring getProperty(std::wstring key) {
		if (propertyMap.find(key) != propertyMap.end()) {
			return propertyMap[key];
		}
		return L"";
	}
	void setProperty(std::wstring key, std::wstring value) {
		propertyMap[key] = value;
	}
	bool saveFile(std::string version);
};

#endif // EDITORSETTINGS_H
