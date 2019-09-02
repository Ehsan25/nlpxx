#pragma once

#include <codecvt>
#include <locale>
#include <regex>
#include <string>

namespace nlpxx::utils
{
using character = char32_t;
using string = std::u32string;
using regex = std::basic_regex<character>;

std::string to_utf8(const std::u16string &str);
std::string to_utf8(const std::u32string &str);

std::u16string to_utf16(const std::string &str);
std::u16string to_utf16(const std::u32string &str);

std::u32string to_utf32(const std::string &str);
std::u32string to_utf32(const std::u16string &str);

}  // namespace nlpxx::utils
