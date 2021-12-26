//
// Created by kevin on 10/3/21.
//

#include "file_utils.h"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <fstream>

namespace glbasic
{
bool ReadFileIntoString(const std::string &file_name, std::string &file_contents)
{
    if (!std::filesystem::is_regular_file(file_name))
    {
        spdlog::error("[ReadFileIntoString]{0} is not a regular file", file_name);
        return false;
    }
    std::ifstream fs(file_name);
    if (!fs.is_open())
    {
        spdlog::error("[ReadFileIntoString]Failed to read file: {0} ", file_name);
        return false;
    }
    fs.seekg(0, std::ios::end);
    file_contents.clear();
    file_contents.reserve(fs.tellg());
    fs.seekg(0, std::ios::beg);
    file_contents.assign((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    fs.close();
    return true;
}

} // namespace glbasic