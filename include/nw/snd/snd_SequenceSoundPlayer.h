#ifndef NW_SND_SEQUENCE_SOUND_PLAYER_H_
#define NW_SND_SEQUENCE_SOUND_PLAYER_H_

#include <nw/types.h>

namespace nw { namespace snd {

struct SequenceUserprocCallbackParam
{
    vs16* localVariable;
    vs16* globalVariable;
    vs16* trackVariable;
    bool cmpFlag;
};
static_assert(sizeof(SequenceUserprocCallbackParam) == 0x10);

typedef void (*SequenceUserprocCallback)(
    u16 procId,
    SequenceUserprocCallbackParam* param,
    void* arg
);

} } // namespace nw::snd

#endif // NW_SND_SEQUENCE_SOUND_PLAYER_H_
