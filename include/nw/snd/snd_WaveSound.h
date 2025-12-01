#ifndef NW_SND_WAVE_SOUND_H_
#define NW_SND_WAVE_SOUND_H_

#include <nw/snd/snd_SoundInstanceManager.h>

namespace nw { namespace snd { namespace internal {

class WaveSound : public BasicSound
{
    // TODO;
};

typedef SoundInstanceManager<WaveSound> WaveSoundInstanceManager;
static_assert(sizeof(WaveSoundInstanceManager) == 0x20);

} } } // namespace nw::snd::internal

#endif // NW_SND_WAVE_SOUND_H_
