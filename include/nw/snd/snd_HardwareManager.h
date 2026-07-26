#ifndef NW_SND_HARDWARE_MANAGER_H_
#define NW_SND_HARDWARE_MANAGER_H_

#include <nw/types.h>

#include <cafe/ax.h>

namespace nw { namespace snd { namespace internal { namespace driver {

class HardwareManager
{
public:
    static const u32 SOUND_FRAME_INTERVAL_MSEC = AX_MS_PER_FRAME;

    // TODO
};

} } } } // namespace nw::snd::internal::driver

#endif // NW_SND_HARDWARE_MANAGER_H_
