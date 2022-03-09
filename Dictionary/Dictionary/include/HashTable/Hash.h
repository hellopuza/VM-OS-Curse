#ifndef HASHTABLE_HASH_H
#define HASHTABLE_HASH_H

#include <fstream>

namespace puza {

struct Hash final
{
    using TYPE = unsigned long;
    TYPE value;

    Hash();
    explicit Hash(TYPE val);

    template<typename T>
    Hash& operator()(const T& data);

    Hash& operator()(const void* buf, size_t size);
    bool operator==(const Hash& h) const;
    bool operator!=(const Hash& h) const;

    friend std::ostream& operator<<(std::ostream& os, const Hash& hash);
};

} // namespace puza

#endif // HASHTABLE_HASH_H
