#include <nw/snd/snd_SequenceSound.h>

namespace nw { namespace snd { namespace internal {

enum DriverCommandId
{
    DRIVER_COMMAND_SEQTRACK_SILENCE = 26
};

struct Command
{
    Command* next;
    u32 id;
    u32 tag;
    u32 memory_next;
};
static_assert(sizeof(Command) == 0x10);

struct DriverCommandSequenceSoundTrack : Command
{
    driver::SequenceSoundPlayer* player;
    u32 trackBitFlag;
};
static_assert(sizeof(DriverCommandSequenceSoundTrack) == 0x18);

struct DriverCommandSequenceSoundTrackSilence : DriverCommandSequenceSoundTrack
{
    bool silenceFlag;
    int fadeFrames;
};
static_assert(sizeof(DriverCommandSequenceSoundTrackSilence) == 0x20);

class CommandManager
{
public:
    template <typename CommandType>
    CommandType* AllocCommand()
    {
        return reinterpret_cast<CommandType*>(AllocMemory(sizeof(CommandType)));
    }

    u32 PushCommand(Command* command);

private:
    void* AllocMemory(u32 size);
};

class DriverCommand : public CommandManager
{
public:
    static DriverCommand& GetInstance();
};

void SequenceSound::SetTrackSilence(u32 trackBitFlag, bool silenceFlag, int fadeFrames)
{
    DriverCommand& cmdmgr = DriverCommand::GetInstance();
    DriverCommandSequenceSoundTrackSilence* command =
        cmdmgr.AllocCommand<DriverCommandSequenceSoundTrackSilence>();
    command->id = DRIVER_COMMAND_SEQTRACK_SILENCE;
    command->player = &m_SequenceSoundPlayerInstance;
    command->trackBitFlag = trackBitFlag;
    command->silenceFlag = silenceFlag;
    command->fadeFrames = fadeFrames;
    cmdmgr.PushCommand(command);
}

} } } // namespace nw::snd::internal
