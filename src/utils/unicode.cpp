#include "unicode.h"

namespace nlpxx::utils
{
std::string to_utf8(const std::u16string &str)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>().to_bytes(str);
}

std::string to_utf8(const std::u32string &str)
{
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(str);
}

std::u16string to_utf16(const std::string &str)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>().from_bytes(str);
}

std::u16string to_utf16(const std::u32string &str)
{
    auto result = std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t>().to_bytes(str);
    return std::u16string(reinterpret_cast<const char16_t *>(result.data()),
                          result.size() / sizeof(char16_t));
}

std::u32string to_utf32(const std::string &str)
{
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().from_bytes(str);
}

std::u32string to_utf32(const std::u16string &str)
{
    auto data = reinterpret_cast<const char *>(str.data());
    return std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t>().from_bytes(
        data, data + str.size());
}
}  // namespace nlpxx::utils
