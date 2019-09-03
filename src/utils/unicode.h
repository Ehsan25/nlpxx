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

#pragma once

#include <codecvt>
#include <locale>
#include <regex>
#include <string>

namespace nlpxx::utils
{
using character = char32_t;
using string = std::u32string;

std::string to_utf8(const std::u16string &str);
std::string to_utf8(const std::u32string &str);

std::u16string to_utf16(const std::string &str);
std::u16string to_utf16(const std::u32string &str);

std::u32string to_utf32(const std::string &str);
std::u32string to_utf32(const std::u16string &str);

}  // namespace nlpxx::utils
