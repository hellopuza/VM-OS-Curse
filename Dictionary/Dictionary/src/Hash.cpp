#include "HashTable/Hash.h"
#include <cstring>
#include <iomanip>

namespace puza {

Hash::Hash() : value(0)
{}

Hash::Hash(TYPE val) : value(val)
{}

Hash Hash::operator()(const void* buf, size_t size) const
{
    return sum(buf, size);
}

Hash Hash::sum(const void* buf, size_t size)
{
    if (buf == nullptr)
    {
        return Hash(0);
    }

    const auto* data = static_cast<const char*>(buf);

    constexpr TYPE kPrime = 0x01000193;
    TYPE hval = 0x811c9dc5;

    for (size_t i = 0; i < size; i++)
    {
        hval *= kPrime;
        hval ^= static_cast<TYPE>(data[i]);
    }

    return Hash(hval);
}

bool Hash::operator == (const Hash& h) const
{
    return value == h.value;
}

bool Hash::operator != (const Hash& h) const
{
    return value != h.value;
}

std::ostream& operator<<(std::ostream& os, const Hash& hash)
{
    return os << std::setfill('0') << std::setw(sizeof(hash) * 2) << std::hex << std::uppercase << hash.value;
}

} // namespace puza