#ifndef NW_SND_SOUND_MEMORY_ALLOCATABLE_H_
#define NW_SND_SOUND_MEMORY_ALLOCATABLE_H_

#include <nw/snd/snd_Global.h>

namespace nw { namespace snd {

class SoundMemoryAllocatable
{
public:
    virtual ~SoundMemoryAllocatable() {}

    virtual void* Alloc(size_t size) = 0;
};
static_assert(sizeof(SoundMemoryAllocatable) == 4);

} } // namespace nw::snd

#endif // NW_SND_SOUND_MEMORY_ALLOCATABLE_H_
