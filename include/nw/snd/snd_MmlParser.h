#ifndef NW_SND_MML_PARSER_H_
#define NW_SND_MML_PARSER_H_

#include <nw/snd/snd_Global.h>

namespace nw { namespace snd { namespace internal { namespace driver {

class MmlSequenceTrack;

class MmlParser
{
public:
    virtual ~MmlParser() {}

protected:
    virtual void CommandProc(
        MmlSequenceTrack* track,
        u32 command,
        s32 commandArg1,
        s32 commandArg2
    ) const;

    virtual void NoteOnCommandProc(
        MmlSequenceTrack* track,
        int key,
        int velocity,
        s32 length,
        bool tieFlag
    ) const;
};
static_assert(sizeof(MmlParser) == 4);

} } } } // namespace nw::snd::internal::driver

#endif // NW_SND_MML_PARSER_H_
