#pragma once

#include <string>
#include "../utils/utils.h"

namespace nlpxx::stem
{
class Stemmer
{
public:
    virtual utils::string stem(const utils::string &token) = 0;
};

}  // namespace nlpxx::stem
