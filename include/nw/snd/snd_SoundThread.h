#ifndef NW_SND_SOUND_THREAD_H_
#define NW_SND_SOUND_THREAD_H_

#include <nw/ut/ut_LinkList.h>

namespace nw { namespace snd { namespace internal { namespace driver {

class SoundThread
{
public:
    class PlayerCallback
    {
      public:
        ut::LinkListNode m_Link;

        virtual ~PlayerCallback() {}
        virtual void OnUpdateFrameSoundThread() {}
        virtual void OnShutdownSoundThread() {}
    };

    // TODO
};

} } } } // namespace nw::snd::internal::driver

#endif // NW_SND_SOUND_THREAD_H_
