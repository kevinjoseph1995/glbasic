//
// Created by kevin on 10/3/21.
//

#ifndef GL_BASIC_FILE_UTILS_H
#define GL_BASIC_FILE_UTILS_H
#include <string>

namespace glbasic
{

[[nodiscard]] bool ReadFileIntoString(const std::string &file_name, std::string &file_contents);
}

#endif // GL_BASIC_FILE_UTILS_H
