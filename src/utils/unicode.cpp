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
#include <assert.h>

#define PCRE2_CODE_UNIT_WIDTH 32
#include <pcre2.h>

namespace nlpxx::utils
{
std::string str2std(const string &str)
{
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(str);
}

string std2str(const std::string &str)
{
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().from_bytes(str);
}

regex::regex() {}

regex::~regex()
{
    if (data) delete static_cast<pcre2_code_32 *>(data);
}

regex::regex(const string &pattern) { set(pattern); }

void regex::set(const string &pattern)
{
    auto str = reinterpret_cast<PCRE2_SPTR32>(pattern.data());
    auto ptr = static_cast<pcre2_code_32 *>(data);
    if (ptr) delete ptr;

    ptr = pcre2_compile_32(str, pattern.size(), 0, nullptr, nullptr, nullptr);
    assert(ptr);
}

bool regex::match(const string &text)
{
    auto str = reinterpret_cast<PCRE2_SPTR32>(text.data());
    auto ptr = static_cast<pcre2_code_32 *>(data);
    assert(ptr);

    auto md = pcre2_match_data_create_from_pattern_32(ptr, nullptr);
    auto result = pcre2_match_32(ptr, str, text.size(), 0, 0, md, nullptr);
    return result >= 0;
}

}  // namespace nlpxx::utils
