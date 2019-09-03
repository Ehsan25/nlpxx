// Copyright (C) 2019 Shahriar Rezghi, Ehsan Alizadeh
// Copyright (C) 2001-2019 NLTK Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
