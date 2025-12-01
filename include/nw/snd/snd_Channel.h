#ifndef NW_SND_CHANNEL_H_
#define NW_SND_CHANNEL_H_

#include <nw/snd/snd_Global.h>

namespace nw { namespace snd { namespace internal { namespace driver {

class Channel
{
public:
    enum ChannelCallbackStatus
    {
        CALLBACK_STATUS_STOPPED,
        CALLBACK_STATUS_DROP,
        CALLBACK_STATUS_FINISH,
        CALLBACK_STATUS_CANCEL
    };

    typedef void (*ChannelCallback)(
        Channel* channel,
        ChannelCallbackStatus status,
        void* userData
    );
};

} } } } // namespace nw::snd::internal::driver

#endif // NW_SND_CHANNEL_H_
