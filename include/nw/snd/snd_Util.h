#ifndef NW_SND_UTIL_H_
#define NW_SND_UTIL_H_

#include <nw/types.h>
#include <nw/ut/ut_BinaryFileFormat.h>
#include <nw/snd/snd_ItemType.h>

namespace nw { namespace snd { namespace internal {

class Util
{
public:
    static NW_INLINE ItemType GetItemType(u32 id)
    {
        return static_cast<ItemType>(id >> 24);
    }

    static NW_INLINE u32 GetItemIndex(u32 id)
    {
        return id & 0x00ffffff;
    }

    static NW_INLINE u32 GetMaskedItemId(u32 id, internal::ItemType type)
    {
        return id | (static_cast<u32>(type) << 24);
    }
};

} } } // namespace nw::snd::internal

#endif // NW_SND_UTIL_H_
