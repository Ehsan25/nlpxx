#pragma once

#include <string>

namespace nlpxx::stem
{
class Stemmer
{
public:
    virtual std::string stem(const std::string &token) = 0;
};

}  // namespace nlpxx::stem
