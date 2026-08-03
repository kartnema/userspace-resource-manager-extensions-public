// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
// SPDX-License-Identifier: BSD-3-Clause-Clear

#ifndef URM_EXT_HELPERS_H
#define URM_EXT_HELPERS_H

#include <string>

#include <Urm/Logger.h>
#include <Urm/Resource.h>
#include <Urm/Extensions.h>
#include <Urm/UrmPlatformAL.h>
#include <Urm/SignalInternal.h>

// File I/O Helpers
int8_t fileExists(const std::string& filePath);
int8_t isWritable(const std::string& path);
int8_t readLineFromFile(const std::string& fileName, std::string& line);
int32_t writeLineToFile(const std::string& fileName, const std::string& value);

// String Utils
void trim(const std::string& value, std::string& trimStr);
void toLower(std::string& value);
void cpuMaskToHex(uint64_t mask, std::string& hexStr);

#endif
