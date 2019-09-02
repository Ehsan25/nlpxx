#pragma once

#include <string>
#include "../utils/utils.h"

namespace nlpxx::stem
{
class Stemmer
{
public:
    virtual utils::string stem(utils::string token) const = 0;
};

}  // namespace nlpxx::stem
