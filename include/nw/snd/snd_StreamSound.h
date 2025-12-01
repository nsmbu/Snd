#ifndef NW_SND_STREAM_SOUND_H_
#define NW_SND_STREAM_SOUND_H_

#include <nw/snd/snd_SoundInstanceManager.h>
#include <nw/snd/snd_StreamBufferPool.h>

namespace nw { namespace snd { namespace internal {

class StreamSound : public BasicSound
{
    // TODO;
};

typedef SoundInstanceManager<StreamSound> StreamSoundInstanceManager;
static_assert(sizeof(StreamSoundInstanceManager) == 0x20);

} } } // namespace nw::snd::internal

#endif // NW_SND_STREAM_SOUND_H_
