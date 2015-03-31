#include "fileutil.h"
#include <fstream>
#include <direct.h>
#include "Shlwapi.h"

bool file_exists(const char * file) {
    auto fp = std::string(_getcwd(NULL, 0)).append("/").append(file);

    std::ifstream ifile(fp.c_str());
    return !!ifile;
}

bool has_extension(std::string const & path, const char * ext) {
    return path.length() >= 4 &&
        0 == path.compare(
        path.length() - strlen(ext), strlen(ext), ext);
}