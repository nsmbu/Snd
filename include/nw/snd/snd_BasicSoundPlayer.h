#ifndef NW_SND_BASIC_SOUND_PLAYER_H_
#define NW_SND_BASIC_SOUND_PLAYER_H_

#include <nw/snd/snd_Global.h>
#include <nw/snd/snd_HardwareManager.h>
#include <nw/snd/snd_PlayerHeapDataManager.h>
#include <nw/ut/os/ut_Event.h>

namespace nw { namespace snd { namespace internal { namespace driver {

struct PlayerParamSet
{
    f32 volume;
    f32 pitch;
    f32 lpfFreq;
    f32 biquadValue;
    s8 biquadType;
    bool isFrontBypass;
    u8 remoteFilter;
    PanMode panMode;
    PanCurve panCurve;
    u32 outputLineFlag;
    VoiceRendererType rendererType;

    OutputParam tvParam;
    OutputParam drcParam[DRC_OUT_COUNT];
    RemoteOutputParam remoteParam[REMOTE_OUT_COUNT];

    PlayerParamSet() { Initialize(); }
    void Initialize();
};
static_assert(sizeof(PlayerParamSet) == 0x8C);

class BasicSoundPlayer
{
public:
    BasicSoundPlayer();
    virtual ~BasicSoundPlayer() {};

    virtual void Initialize();
    virtual void Finalize();

    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Pause(bool flag) = 0;

    bool IsActive() const { return m_ActiveFlag; }
    bool IsStarted() const { return m_StartedFlag; }
    bool IsPause() const { return m_PauseFlag; }
    bool IsPlayFinished() const { return m_FinishFlag; }
    bool IsFinalizedForCannotAllocateResource() const
    {
        return m_IsFinalizedForCannotAllocateResource;
    }

    void SetVolume(f32 volume) { m_PlayerParamSet.volume = volume; }
    void SetPitch(f32 pitch) { m_PlayerParamSet.pitch = pitch; }
    void SetLpfFreq(f32 lpfFreq) { m_PlayerParamSet.lpfFreq = lpfFreq; }
    void SetBiquadFilter(int type, f32 value);
    void SetPanMode(PanMode mode) { m_PlayerParamSet.panMode = mode; }
    void SetPanCurve(PanCurve curve)  { m_PlayerParamSet.panCurve = curve; }
    void SetFrontBypass(bool frontBypass) { m_PlayerParamSet.isFrontBypass = frontBypass; }
    void SetRemoteFilter(int filter) { /* NW_MINMAX_ASSERT(filter,0,0xff); */ m_PlayerParamSet.remoteFilter = static_cast<u8>(filter); }
    void SetVoiceRendererType(VoiceRendererType mode) { m_PlayerParamSet.rendererType = mode; }

    f32 GetVolume() const { return m_PlayerParamSet.volume; }
    f32 GetPitch() const { return m_PlayerParamSet.pitch; }
    f32 GetLpfFreq() const { return m_PlayerParamSet.lpfFreq; }
    int GetBiquadFilterType() const { return m_PlayerParamSet.biquadType; }
    f32 GetBiquadFilterValue() const { return m_PlayerParamSet.biquadValue; }
    PanMode GetPanMode() const { return m_PlayerParamSet.panMode; }
    PanCurve GetPanCurve() const { return m_PlayerParamSet.panCurve; }
    bool IsFrontBypass() const { return m_PlayerParamSet.isFrontBypass; }
    u8 GetRemoteFilter() const { return m_PlayerParamSet.remoteFilter; }
    VoiceRendererType GetVoiceRendererType() const { return m_PlayerParamSet.rendererType; }

    void SetOutputLine(u32 outputLineFlag) { m_PlayerParamSet.outputLineFlag = outputLineFlag; }
    u32 GetOutputLine() const { return m_PlayerParamSet.outputLineFlag; }

    void SetTvParam(const OutputParam& param)
    {
        m_PlayerParamSet.tvParam = param;
    }
    const OutputParam& GetTvParam() const
    {
        return m_PlayerParamSet.tvParam;
    }

    void SetDrcParam(u32 drcIndex, const OutputParam& param)
    {
        m_PlayerParamSet.drcParam[drcIndex] = param;
    }
    const OutputParam& GetDrcParam(u32 drcIndex) const
    {
        return m_PlayerParamSet.drcParam[drcIndex];
    }

    void SetRemoteParam(u32 remoteIndex, const RemoteOutputParam& param)
    {
        m_PlayerParamSet.remoteParam[remoteIndex] = param;
    }
    const RemoteOutputParam& GetRemoteParam(u32 remoteIndex) const
    {
        return m_PlayerParamSet.remoteParam[remoteIndex];
    }

    bool TryWaitInstanceFree()
    {
        return m_Event.TryWait();
    }

    void WaitInstanceFree()
    {
        m_Event.Wait();
    }

    void InitializeEvent()
    {
        m_Event.Reset();
    }

    const PlayerHeapDataManager* GetPlayerHeapDataManager() const
    {
        return m_pPlayerHeapDataManager;
    }

    void ClearIsFinalizedForCannotAllocatedResourceFlag()
    {
        m_IsFinalizedForCannotAllocateResource = false;
    }

protected:
    void SetPlayerHeapDataManagerImpl(const PlayerHeapDataManager* mgr)
    {
        m_pPlayerHeapDataManager = mgr;
    }

    static s32 ToDelayCount(s32 delayTimeMilliSec)
    {
        //NW_ASSERT(delayTimeMilliSec % HardwareManager::SOUND_FRAME_INTERVAL_MSEC == 0);
        return delayTimeMilliSec / HardwareManager::SOUND_FRAME_INTERVAL_MSEC;
    }

    nw::ut::Event m_Event;
    bool m_ActiveFlag;
    bool m_StartedFlag;
    bool m_PauseFlag;
    bool m_FinishFlag;

    bool m_IsFinalizedForCannotAllocateResource;

private:
    PlayerParamSet m_PlayerParamSet;
    const PlayerHeapDataManager* m_pPlayerHeapDataManager;
};
static_assert(sizeof(BasicSoundPlayer) == 0xC0);

} } } } // namespace nw::snd::internal::driver

#endif // NW_SND_BASIC_SOUND_PLAYER_H_
