#ifndef NW_SND_SOUND_ARCHIVE_H_
#define NW_SND_SOUND_ARCHIVE_H_

#include <nw/snd/snd_Util.h>
#include <nw/snd/snd_Global.h>

namespace nw { namespace snd {

class SoundArchive
{
public:
    typedef u32 ItemId;

    static const ItemId INVALID_ID = 0xffffffff;

    static const u32 SEQ_BANK_MAX = nw::snd::SEQ_BANK_MAX;

    const char* GetItemLabel(ItemId id) const;
    ItemId GetItemId(const char* pLabel) const;

    static ItemId GetSoundIdFromIndex(u32 index)
    {
        return internal::Util::GetMaskedItemId(index, internal::ItemType_Sound);
    }

    static ItemId GetSoundGroupIdFromIndex(u32 index)
    {
        return internal::Util::GetMaskedItemId(index, internal::ItemType_SoundGroup);
    }

    static ItemId GetBankIdFromIndex(u32 index)
    {
        return internal::Util::GetMaskedItemId(index, internal::ItemType_Bank);
    }

    static ItemId GetPlayerIdFromIndex(u32 index)
    {
        return internal::Util::GetMaskedItemId(index, internal::ItemType_Player);
    }

    static ItemId GetWaveArchiveIdFromIndex(u32 index)
    {
        return internal::Util::GetMaskedItemId(index, internal::ItemType_WaveArchive);
    }

    static ItemId GetGroupIdFromIndex(u32 index)
    {
        return internal::Util::GetMaskedItemId(index, internal::ItemType_Group);
    }
};

} }

#endif // NW_SND_SOUND_ARCHIVE_H_
