#ifndef NW_SND_NOTE_ON_CALLBACK_H_
#define NW_SND_NOTE_ON_CALLBACK_H_

#include <nw/snd/snd_Channel.h>     // Channel::ChannelCallback

namespace nw { namespace snd { namespace internal { namespace driver {

class SequenceSoundPlayer;

struct NoteOnInfo
{
    int prgNo;
    int key;
    int velocity;
    int length;
    int initPan;
    int priority;
    Channel::ChannelCallback channelCallback;
    void* channelCallbackData;
    VoiceRendererType rendererType;
};
static_assert(sizeof(NoteOnInfo) == 0x24);

class NoteOnCallback
{
public:
    virtual ~NoteOnCallback() {}

    virtual Channel* NoteOn(
        SequenceSoundPlayer* sequenceSoundPlayer,
        u8 bankIndex,
        const NoteOnInfo& noteOnInfo
    ) = 0;
};
static_assert(sizeof(NoteOnCallback) == 4);

} } } } // namespace namespace nw::snd::internal::driver

#endif // NW_SND_NOTE_ON_CALLBACK_H_
