#ifndef NW_SND_SOUND_ARCHIVE_H_
#define NW_SND_SOUND_ARCHIVE_H_

#include <nw/snd/snd_Util.h>
#include <nw/snd/snd_Global.h>
#include <nw/snd/snd_Config.h>

namespace nw { namespace snd {

class SoundArchive
{
public:
    typedef u32 ItemId;

    static const ItemId INVALID_ID = 0xffffffff;

    typedef ItemId FileId;

    struct SoundInfo
    {
        FileId fileId;
        ItemId playerId;

        u8 actorPlayerId;
        u8 playerPriority;
        u8 volume;
        u8 remoteFilter;
        PanMode panMode;
        PanCurve panCurve;

        bool isFrontBypass;
    };
    static_assert(sizeof(SoundInfo) == 0x18);

    static const u32 SEQ_BANK_MAX = nw::snd::SEQ_BANK_MAX;

    struct SequenceSoundInfo
    {
        u32 startOffset;
        u32 bankIds[SEQ_BANK_MAX];

        u32 allocateTrackFlags;
        u8  channelPriority;
        bool isReleasePriorityFix;

        SequenceSoundInfo()
            : startOffset(0)
            , allocateTrackFlags(0)
            , channelPriority(0)
            , isReleasePriorityFix(false)
        {
            for (u32 i = 0; i < SEQ_BANK_MAX; i++)
                bankIds[i] = INVALID_ID;
        }
    };
    static_assert(sizeof(SequenceSoundInfo) == 0x1C);

    static const u32 STRM_TRACK_NUM = internal::STRM_TRACK_NUM;

    struct StreamTrackInfo
    {
        u8 volume;
        u8 pan;
        u8 span;
        u8 flags; // nw::snd::internal::StreamSoundFile::SurroundMode
        u8 channelCount;
        s8 globalChannelIndex[WAVE_CHANNEL_MAX];

        StreamTrackInfo()
            : volume(0)
            , pan(0)
            , span(0)
            , channelCount(0)
        {
            std::memset(globalChannelIndex, -1, sizeof(s8)*WAVE_CHANNEL_MAX);
        }
    };
    static_assert(sizeof(StreamTrackInfo) == 7);

    struct StreamSoundInfo
    {
        u16 allocateTrackFlags;
        u16 allocateChannelCount;
        StreamTrackInfo trackInfo[STRM_TRACK_NUM];

        StreamSoundInfo()
            : allocateTrackFlags(0)
            , allocateChannelCount(0)
        {
        }
    };
    static_assert(sizeof(StreamSoundInfo) == 0x3C);

    struct WaveSoundInfo
    {
        u32     index;
        u32     allocateTrackCount;
        u8      channelPriority;
        bool    isReleasePriorityFix;

        WaveSoundInfo()
            : allocateTrackCount(0)
            , channelPriority(0)
            , isReleasePriorityFix(false)
        {
        }
    };
    static_assert(sizeof(WaveSoundInfo) == 0xC);

    struct SoundArchivePlayerInfo
    {
        int sequenceSoundMax;
        int sequenceTrackMax;
        int streamSoundMax;
        int streamTrackMax;
        int streamChannelMax;
        int waveSoundMax;
        int waveTrackMax;
    };
    static_assert(sizeof(SoundArchivePlayerInfo) == 0x1C);

public:
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
