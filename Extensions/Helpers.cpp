// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
// SPDX-License-Identifier: BSD-3-Clause-Clear

#include <sstream>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <cerrno>
#include <cctype>

#include "Helpers.h"

int8_t fileExists(const std::string& filePath) {
    return access(filePath.c_str(), F_OK) == 0;
}

// cpumask to hex
void cpuMaskToHex(uint64_t mask, std::string& hexStr) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%llx",
             (unsigned long long)mask);
    hexStr = std::string(buf);
}

// Lowercase utility
void toLower(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
}

void trim(const std::string& s, std::string& trimStr) {
    size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;
    trimStr = s.substr(b, e - b);
}

// Check writability using access(2)
int8_t isWritable(const std::string& path) {
    if (path.empty()) return false;
    return ::access(path.c_str(), W_OK) == 0;
}


int32_t writeLineToFile(const std::string& fileName, const std::string& value) {
    if (fileName.empty()) return EINVAL;

    std::ofstream fileStream(fileName, std::ios::out | std::ios::trunc);
    if (!fileStream.is_open()) {
        return EIO;
    }

    fileStream << value;

    if (!fileStream.good()) {
        fileStream.close();
        return EIO;
    }

    fileStream.flush();
    fileStream.close();
    return 0;
}

int8_t readLineFromFile(const std::string& fileName, std::string& line) {
    if (fileName.empty()) return false;

    std::ifstream fileStream(fileName, std::ios::in);
    std::string value;

    if(!fileStream.is_open()) {
        return false;
    }

    if(!getline(fileStream, value)) {
        fileStream.close();
        return false;
    }

    fileStream.close();
    line = value;
    return true;
}
