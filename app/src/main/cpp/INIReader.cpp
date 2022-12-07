//
// Created by michelle on 22/05/18.
//

#include "INIReader.h"

INIReader::INIReader(AAssetManager* assetManager, std::string path) {
    _assetManager = assetManager;
    _path = path;

    this->_parse();
}

INIReader::~INIReader() {
    _assetManager = nullptr;
}

void INIReader::_parse() {
    AAsset* asset = AAssetManager_open(_assetManager, _path.c_str(),
                                       AASSET_MODE_UNKNOWN);

    off_t len = AAsset_getLength(asset);
    size_t size = static_cast<size_t>(len);

    char* buffer = (char*) malloc(size);
    AAsset_read(asset, buffer, size);
    AAsset_close(asset);

    std::string str = buffer;
    std::replace(str.begin(), str.end(), '\r', ' ');

    int sectionNameStart = -1;
    int pairStart = -1;

    for (int i = 0; i < size; i++) {
        switch (buffer[i]) {
            case '[': {
                sectionNameStart = i;
                pairStart = -1;
                break;
            }
            case ']': {
                if (sectionNameStart < 0) {
                    // Fall through
                } else {
                    _section(str, sectionNameStart + 1, i);
                    sectionNameStart = -1;
                    pairStart = i + 1;
                    break;
                }
            }
            case '\n':
                if (pairStart < 0) {
                    // Fall through
                } else {
                    _line(str, pairStart, i);
                    pairStart = i + 1;
                }
                break;
            default: {

                break;
            }
        }
    }

    if (pairStart < size) {
        _line(str, pairStart, static_cast<int>(size));
    }

    free(buffer);
}

void INIReader::_section(std::string& string, int start, int end) {
    if (_overlap(start, end)) return;

    std::string section = string.substr(static_cast<unsigned long>(start),
                                        static_cast<unsigned long>(end - start));

    _currentSection = section;

    // Add to sections if it is not in there already
    if (std::find(_sections.begin(), _sections.end(), _currentSection) == _sections.end()) {
        _sections.push_back(_currentSection);
    }
}

std::string INIReader::Get(std::string section, std::string key, std::string vdefault) {
    try {
        std::string get = _values[_makeKey(section, key)];
        if (get.size() <= 0) {
            return vdefault;
        } else {
            return get;
        }
    } catch (std::exception& e) {
        /*
         * Something unusual has happenend.
         */
    }

    return vdefault;
}

std::vector<std::string> INIReader::Sections() {
    return _sections;
}

long INIReader::GetInteger(std::string section, std::string key, long vdefault) {
    return std::stol(Get(section, key, std::to_string(vdefault)));
}

void INIReader::_line(std::string pairString, int start, int end) {
    if (_overlap(start, end)) return;

    std::string section = pairString.substr(static_cast<unsigned long>(start),
                                            static_cast<unsigned long>(end - start));

    int equalsPosition = -1;
    for (int i = 0; i < section.size(); i++) {
        if (section[i] == '=') {
            equalsPosition = i;
            break;
        }
    }
    std::string key = section.substr(0, static_cast<unsigned long>(equalsPosition));
    std::string value = section.substr(static_cast<unsigned long>(equalsPosition + 1));
    trim(key);
    trim(value);

    if (_shouldAdd(key, value)) {
        _values[_makeKey(_currentSection, key)] = value;
    }
}

std::string INIReader::_makeKey(std::string& section, std::string& key) {
    return section + KEY_JOINER + key;
}

bool INIReader::_overlap(int start, int end) {
    if (start < 0) return true;

    // Reject on equals
    if (start == end) return true;

    // Reject on overlap
    if (end < start) return true;
    // Please ignore the simplification by android studio,
    // this is more readable..
    if (start > end) return true;

    return false;
}

INIREADER_SECTION_LIST INIReader::GetSection(std::string section) {
    INIREADER_SECTION_LIST props;
    section += KEY_JOINER;

    for (auto it = _values.begin(); it != _values.end(); it++) {
        std::string key = it->first;
        if (key.compare(0, section.length(), section) == 0) {
            props.push_back(
                    std::pair<std::string, std::string>(key.substr(section.length()), it->second));
        }
    }

    return props;
}

bool INIReader::_shouldAdd(std::string key, std::string value) {
    if (key.length() <= 0 || value.length() <= 0) return false;

    return true;
}
