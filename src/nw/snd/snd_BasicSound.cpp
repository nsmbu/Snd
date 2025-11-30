#include <nw/snd/snd_BasicSound.h>

namespace nw { namespace snd { namespace internal {

f32 BasicSound::GetVolume() const
{
    return m_CommonParam.GetVolume();
}

} } } // namespace nw::snd::internal
