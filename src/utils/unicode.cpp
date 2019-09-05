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

void regex::delete_if()
{
    if (data) pcre2_code_free_32(static_cast<pcre2_code_32 *>(data));
}

regex::regex() {}

regex::~regex() { delete_if(); }

regex::regex(const string &pattern) { set(pattern); }

void regex::set(const string &pattern)
{
    auto str = reinterpret_cast<PCRE2_SPTR32>(pattern.data());
    delete_if();

    int error_number;
    size_t error_offset;
    data = pcre2_compile_32(str, pattern.size(), 0, &error_number, &error_offset, nullptr);
    assert(data && "Failed to compile regex (probably wrong syntax)");
}

bool regex::match(const string &text)
{
    auto str = reinterpret_cast<PCRE2_SPTR32>(text.data());
    auto code = static_cast<pcre2_code_32 *>(data);
    assert(code && "Can't use empty regex to match");

    auto md = pcre2_match_data_create_from_pattern_32(code, nullptr);
    auto result = pcre2_match_32(code, str, text.size(), 0, 0, md, nullptr);
    pcre2_match_data_free_32(md);

    assert((result >= 0 || result == PCRE2_ERROR_NOMATCH || result == PCRE2_ERROR_PARTIAL) &&
           "Failed to match using regex");
    return result >= 0;
}

string regex::replace(const string &text, const string &replacement)
{
    auto rep = reinterpret_cast<PCRE2_SPTR32>(replacement.data());
    auto str = reinterpret_cast<PCRE2_SPTR32>(text.data());
    auto code = static_cast<pcre2_code_32 *>(data);
    assert(code && "Can't use empty regex to replace");

    PCRE2_UCHAR32 output[1024];
    size_t output_size = 1024;
    auto result = pcre2_substitute_32(code, str, text.size(), 0, PCRE2_SUBSTITUTE_GLOBAL, nullptr,
                                      nullptr, rep, replacement.size(), output, &output_size);
    assert(result >= 0 && "Failed to replace using regex");
    return string(output, output + output_size);
}

}  // namespace nlpxx::utils
