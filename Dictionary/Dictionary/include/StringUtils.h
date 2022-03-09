#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>

namespace puza {

std::string prepare_word(const std::string& word);
size_t lev_dist(const std::string& source, const std::string& target);

} // namespace puza

#endif // STRINGUTILS_H