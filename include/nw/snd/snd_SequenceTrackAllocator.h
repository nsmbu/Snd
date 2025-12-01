#ifndef NW_SND_SEQUENCE_TRACK_ALLOCATOR_H_
#define NW_SND_SEQUENCE_TRACK_ALLOCATOR_H_

#include <nw/snd/snd_Global.h>

namespace nw { namespace snd { namespace internal { namespace driver {

class SequenceTrack;
class SequenceSoundPlayer;

class SequenceTrackAllocator
{
public:
    virtual ~SequenceTrackAllocator() {}

    virtual SequenceTrack* AllocTrack(SequenceSoundPlayer* player) = 0;
    virtual void FreeTrack(SequenceTrack* track) = 0;

    virtual int GetAllocatableTrackCount() const = 0;
};
static_assert(sizeof(SequenceTrackAllocator) == 4);

} } } } // namespace nw::snd::internal::driver


#endif // NW_SND_SEQUENCE_TRACK_ALLOCATOR_H_
