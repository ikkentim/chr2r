/**
 * fileutil.h
 * Declares various file path helper functions.
 */
#pragma once

#include <string>

// Gets a value indicating whether the specified file exist
bool file_exists(const char * file);

// Gets a value indicating whether the specfied path has the specified extension
bool has_extension(std::string const & path, const char * ext);