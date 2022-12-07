//
// Created by michelle on 22/05/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_INIREADER_H
#define RHYTHMIC_PROGRAMMING_GAME_INIREADER_H


#include <string>
#include <android/asset_manager.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <locale>
#include <chrono>

#define KEY_JOINER "~+"
#define INIREADER_SECTION_LIST std::vector<std::pair<std::string, std::string>>

class INIReader {
private:
    AAssetManager* _assetManager = nullptr;
    std::string _path;
    std::vector<std::string> _sections;
    std::map<std::string, std::string> _values;
    std::string _currentSection;

    void _parse();

    void _section(std::string& string, int start, int end);

    void _line(std::string pairString, int start, int end);

    std::string _makeKey(std::string& basic_string, std::string& basicString);

    bool _overlap(int start, int end);

    bool _shouldAdd(std::string key, std::string value);

public:
    INIReader() {};

    INIReader(AAssetManager* assetManager, std::string path);

    ~INIReader();

    std::vector<std::string> Sections();

    long GetInteger(std::string section, std::string key, long vdefault);

    std::string Get(std::string section, std::string key, std::string vdefault);

    INIREADER_SECTION_LIST GetSection(std::string section);
};

#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
    std::replace(s.begin(), s.end(), '\r', ' ');
    ltrim(s);
    rtrim(s);
}


#endif //RHYTHMIC_PROGRAMMING_GAME_INIREADER_H
