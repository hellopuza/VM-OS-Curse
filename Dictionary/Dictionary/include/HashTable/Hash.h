#ifndef HASHTABLE_HASH_H
#define HASHTABLE_HASH_H

#include <fstream>

namespace puza {

struct Hash
{
    using TYPE = unsigned long;
    TYPE value;

    Hash();
    explicit Hash(TYPE val);

    template <typename T>
    Hash operator()(const T& data) const;

    Hash operator()(const void* buf, size_t size) const;
    bool operator==(const Hash& h) const;
    bool operator!=(const Hash& h) const;

    friend std::ostream& operator<<(std::ostream& os, const Hash& hash);

private:
    static Hash sum(const void* buf, size_t size);
};

} // namespace puza

#endif // HASHTABLE_HASH_H
