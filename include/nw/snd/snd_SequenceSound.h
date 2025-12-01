#ifndef NW_SND_SEQUENCE_SOUND_H_
#define NW_SND_SEQUENCE_SOUND_H_

#include <nw/snd/snd_SoundInstanceManager.h>

namespace nw { namespace snd { namespace internal {

class SequenceSound : public BasicSound
{
    // TODO;
};

typedef SoundInstanceManager<SequenceSound> SequenceSoundInstanceManager;
static_assert(sizeof(SequenceSoundInstanceManager) == 0x20);

} } } // namespace nw::snd::internal

#endif // NW_SND_SEQUENCE_SOUND_H_
