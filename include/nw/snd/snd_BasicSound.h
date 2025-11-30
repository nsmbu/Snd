#ifndef NW_SND_BASIC_SOUND_H_
#define NW_SND_BASIC_SOUND_H_

#include <nw/snd/snd_Global.h>
#include <nw/snd/snd_MoveValue.h>
#include <nw/ut/ut_RuntimeTypeInfo.h>
#include <nw/ut/ut_LinkList.h>

namespace nw { namespace snd {

class SoundHandle;
class SoundPlayer;
class SoundActor;

struct OutputAmbientParam
{
    f32 volume;
    f32 pan;
    f32 span;
    f32 fxSend[AUX_BUS_NUM];

    OutputAmbientParam()
    {
        Initialize();
    }

    void Initialize()
    {
        volume = 1.0f;
        pan = span = 0.0f;
        for (int i = 0; i < AUX_BUS_NUM; i++)
            fxSend[i] = 0.0f;
    }
};
static_assert(sizeof(OutputAmbientParam) == 0x18);

struct SoundParam
{
    f32 volume;
    f32 pitch;
    f32 lpf;
    f32 biquadFilterValue;
    int biquadFilterType;
    int priority;
    int outputLineFlag;
    u32 userData;
    OutputAmbientParam tvParam;
    OutputAmbientParam drcParam[DRC_OUT_COUNT];

    SoundParam()
    {
        Initialize();
    }

    void Initialize()
    {
        volume            = 1.0f;
        pitch             = 1.0f;
        lpf               = 0.0f;
        biquadFilterValue = 0.0f;
        biquadFilterType  = BIQUAD_FILTER_TYPE_INHERIT;
        priority          = 0;
        userData          = 0;

        outputLineFlag    = -1;

        tvParam.Initialize();
        for (int i = 0; i < DRC_OUT_COUNT; i++)
            drcParam[i].Initialize();
    }
};
static_assert(sizeof(SoundParam) == 0x50);

struct SoundAmbientParam
{
    f32 volume;
    f32 pitch;
    f32 lpf;
    f32 biquadFilterValue;
    int biquadFilterType;
    int priority;
    u32 userData;
    int outputLineFlag;
    OutputAmbientParam tvParam;
    OutputAmbientParam drcParam[DRC_OUT_COUNT];

    SoundAmbientParam()
        : volume(1.0f)
        , pitch(1.0f)
        , lpf(0.0f)
        , biquadFilterValue(0.0f)
        , biquadFilterType(BIQUAD_FILTER_TYPE_INHERIT)
        , priority(0)
        , userData(0)
        , outputLineFlag(-1)
    {
        tvParam.Initialize();
        for (int i = 0; i < DRC_OUT_COUNT; i++)
            drcParam[i].Initialize();
    }
};
static_assert(sizeof(SoundAmbientParam) == 0x50);

namespace internal {

struct SoundActorParam
{
    f32 volume;
    f32 pitch;

    f32 tvVolume;
    f32 tvPan;

    f32 drcVolume[DRC_OUT_COUNT];
    f32 drcPan[DRC_OUT_COUNT];

    SoundActorParam()
    {
        Reset();
    }

    void Reset()
    {
        volume = pitch = tvVolume = 1.0f;
        tvPan = 0.0f;

        for (int i = 0; i < DRC_OUT_COUNT; i++)
        {
            drcVolume[i] = 1.0f;
            drcPan[i] = 0.0f;
        }
    }
};
static_assert(sizeof(SoundActorParam) == 0x18);

namespace driver {

class BasicSoundPlayer;

} // nw::snd::internal::driver

class PlayerHeap;
class ExternalSoundPlayer;

class BasicSound
{
    friend class nw::snd::SoundHandle;

public:
    NW_UT_RUNTIME_TYPEINFO_ROOT()

public:
    static const int PRIORITY_MIN = 0;
    static const int PRIORITY_MAX = 127;
    static const u32 INVALID_ID = 0xffffffff;

public:
    class AmbientParamUpdateCallback;
    class AmbientArgUpdateCallback;
    class AmbientArgAllocatorCallback;

    struct AmbientInfo
    {
        AmbientParamUpdateCallback* paramUpdateCallback;
        AmbientArgUpdateCallback* argUpdateCallback;
        AmbientArgAllocatorCallback* argAllocatorCallback;
        void* arg;
        unsigned long argSize;
    };
    static_assert(sizeof(AmbientInfo) == 0x14);

    enum PlayerState
    {
        PLAYER_STATE_INIT,
        PLAYER_STATE_PLAY,
        PLAYER_STATE_STOP
    };

public:
    BasicSound();
    virtual ~BasicSound() {}
    void Update();
    void StartPrepared();
    void Stop(int fadeFrames);
    void Pause(bool flag, int fadeFrames);
    void SetAutoStopCounter(int frames);
    void FadeIn(int frames);

    virtual void Initialize();
    virtual void Finalize();

    virtual bool IsPrepared() const = 0;
    bool IsPause() const;
    bool IsStarted() const { return m_StartedFlag; }

    void SetPriority(int priority, int ambientPriority);
    void GetPriority(int* priority, int* ambientPriority) const;

    void SetInitialVolume(f32 volume);
    f32  GetInitialVolume() const;

    void SetVolume(f32 volume, int frames = 0);
    f32  GetVolume() const;

    void SetPitch(f32 pitch);
    f32  GetPitch() const;
    /*
    void SetLpfFreq( f32 lpfFreq );
    f32  GetLpfFreq() const;
    void SetBiquadFilter( int type, f32 value );
    void GetBiquadFilter( int* type, f32* value ) const;
    */
    void SetOutputLine(u32 lineFlag);
    u32 GetOutputLine() const;
    void ResetOutputLine();
    /*
    void SetPlayerPriority( int priority );
    */
    void SetPan(f32 pan);
    f32  GetPan() const;
    /*
    void SetSurroundPan( f32 pan );
    f32  GetSurroundPan() const;
    void SetMainSend( f32 send );
    f32  GetMainSend() const;
    void SetFxSend( AuxBus bus, f32 send );
    f32  GetFxSend( AuxBus bus ) const;
    */

    void SetPanMode(PanMode mode);
    void SetPanCurve(PanCurve curve);
    void SetFrontBypass(bool isFrontBypass);
    void SetRemoteFilter(u8 filter);
    void SetVoiceRendererType(VoiceRendererType mode);

    void SetOutputVolume     (OutputDevice device, f32 volume);
    /*
    void SetOutputPan        (OutputDevice device, f32 pan);
    void SetOutputSurroundPan(OutputDevice device, f32 span);
    void SetOutputMainSend   (OutputDevice device, f32 send);
    void SetOutputFxSend     (OutputDevice device, AuxBus bus, f32 send);
    */

    f32 GetOutputVolume     (OutputDevice device) const;
    /*
    f32 GetOutputPan        (OutputDevice device) const;
    f32 GetOutputSurroundPan(OutputDevice device) const;
    f32 GetOutputMainSend   (OutputDevice device) const;
    f32 GetOutputFxSend     (OutputDevice device, AuxBus bus) const;
    */

    void SetRemoteOutVolume( u32 remoteIndex, f32 volume );
    f32 GetRemoteOutVolume( u32 remoteIndex ) const;
    /*
    void SetRemoteMainSend( u32 remoteIndex, f32 send );
    f32  GetRemoteMainSend( u32 remoteIndex ) const;
    void SetRemoteFxSend( u32 remoteIndex, f32 send );
    f32  GetRemoteFxSend( u32 remoteIndex ) const;

    int GetRemainingFadeFrames() const;
    int GetRemainingPauseFadeFrames() const;
    */
    int GetPlayerPriority() const { return m_Priority; }

    void SetId( u32 id );
    u32 GetId() const { return m_Id; }

    int CalcCurrentPlayerPriority() const
    {
        return ut::Clamp(
             static_cast<int>( m_Priority ) + static_cast<int>( m_AmbientParam.priority ),
             PRIORITY_MIN,
             PRIORITY_MAX
        );
    }

    SoundPlayer* GetSoundPlayer() { return m_pSoundPlayer; }
    const SoundPlayer* GetSoundPlayer() const { return m_pSoundPlayer; }

    void AttachSoundPlayer(SoundPlayer* player);
    void DetachSoundPlayer(SoundPlayer* player);

    void AttachSoundActor(SoundActor* actor);
    void DetachSoundActor(SoundActor* actor);

    void AttachExternalSoundPlayer(ExternalSoundPlayer* extPlayer);
    void DetachExternalSoundPlayer(ExternalSoundPlayer* extPlayer);

    void AttachPlayerHeap(PlayerHeap* pHeap);
    void DetachPlayerHeap(PlayerHeap* pHeap);
    PlayerHeap* GetPlayerHeap() { return m_pPlayerHeap; }

    void SetAmbientInfo(const AmbientInfo& info);
    void ClearAmbientArgUpdateCallback() { m_AmbientInfo.argUpdateCallback = NULL; }
    void ClearAmbientParamUpdateCallback() { m_AmbientInfo.paramUpdateCallback = NULL; }
    void ClearAmbientArgAllocatorCallback() { m_AmbientInfo.argAllocatorCallback = NULL; }
    const SoundParam& GetAmbientParam() const { return m_AmbientParam; }
    static int GetAmbientPriority(const AmbientInfo& ambientInfo, u32 soundId);

    bool IsAttachedGeneralHandle();
    bool IsAttachedTempGeneralHandle();
    virtual bool IsAttachedTempSpecialHandle() = 0;
    void DetachGeneralHandle();
    void DetachTempGeneralHandle();
    virtual void DetachTempSpecialHandle() = 0;

    void SetUserParamBuffer(void* buffer, size_t size) { m_pUserParam = buffer; m_UserParamSize = size; }
    void* GetUserParam() { return m_pUserParam; }

    enum PauseState
    {
        PAUSE_STATE_NORMAL,
        PAUSE_STATE_PAUSING,
        PAUSE_STATE_PAUSED,
        PAUSE_STATE_UNPAUSING
    };
    PauseState GetPauseState() const { return m_PauseState; }

protected:
    virtual driver::BasicSoundPlayer* GetBasicSoundPlayerHandle() = 0;

    virtual void OnUpdatePlayerPriority() {}
    virtual void OnUpdate() {}

    virtual void UpdateMoveValue();
    virtual void UpdateParam();

    bool IsPlayerAvailable() const { return m_PlayerAvailableFlag; }

private:
    void ClearIsFinalizedForCannotAllocatedResourceFlag();

    PlayerHeap* m_pPlayerHeap;
    SoundHandle* m_pGeneralHandle;
    SoundHandle* m_pTempGeneralHandle;
    SoundPlayer* m_pSoundPlayer;
    SoundActor* m_pSoundActor;
    ExternalSoundPlayer* m_pExtSoundPlayer;

    AmbientInfo m_AmbientInfo;
    SoundParam m_AmbientParam;
    SoundActorParam m_ActorParam;

    MoveValue<f32, int> m_FadeVolume;
    MoveValue<f32, int> m_PauseFadeVolume;

    bool m_InitializeFlag;
    bool m_StartFlag;
    bool m_StartedFlag;
    bool m_AutoStopFlag;

    bool m_FadeOutFlag;
    bool m_PlayerAvailableFlag;
    bool m_UnPauseFlag;

    PlayerState m_PlayerState;
    PauseState m_PauseState;

    s32 m_AutoStopCounter;
    u32 m_UpdateCounter;

    u8 m_Priority;
    s8 m_BiquadFilterType;

    u32 m_Id;

    f32 m_InitVolume;
    f32 m_Pitch;
    f32 m_LpfFreq;
    f32 m_BiquadFilterValue;
    u32 m_OutputLineFlag;

    u32 _e8; // Set in Initialize() to 0 but never used

    struct CommonParam
    {
        MoveValue<f32, int> volume;
        f32 pan;
        f32 span;
        f32 mainSend;
        f32 fxSend[AUX_BUS_NUM];

        void Initialize()
        {
            volume.InitValue(1.0f);
            pan = span = mainSend = 0.0f;
            for (int i = 0; i < AUX_BUS_NUM; i++)
                fxSend[i] = 0.0f;
        }

        void Update()
        {
            volume.Update();
        }

        f32 GetVolume() const
        {
            return volume.GetValue();
        }

        void SetVolume(f32 target, int frame)
        {
            volume.SetTarget(target, frame);
        }
    };
    static_assert(sizeof(CommonParam) == 0x28);

    void ApplyCommonParam(OutputParam& param);

    CommonParam m_CommonParam;
    OutputParam m_OutputParam[OUTPUT_DEVICE_COUNT];
    RemoteOutputParam m_RemoteParam[REMOTE_OUT_COUNT];

    void* m_pUserParam;
    size_t m_UserParamSize;

public:
    ut::LinkListNode m_PriorityLink;
    ut::LinkListNode m_SoundPlayerPlayLink;
    ut::LinkListNode m_SoundPlayerPriorityLink;
    ut::LinkListNode m_ExtSoundPlayerPlayLink;
};
static_assert(sizeof(BasicSound) == 0x1A8);

class BasicSound::AmbientParamUpdateCallback
{
public:
    virtual ~AmbientParamUpdateCallback() {}
    virtual void detail_UpdateAmbientParam(
        const void* arg,
        u32 soundId,
        SoundAmbientParam* param
    ) = 0;
    virtual int detail_GetAmbientPriority(
        const void* arg,
        u32 soundId
    ) = 0;
};

class BasicSound::AmbientArgUpdateCallback
{
public:
    virtual ~AmbientArgUpdateCallback() {}
    virtual void detail_UpdateAmbientArg(
        void* arg,
        const internal::BasicSound* sound
    ) = 0;
};

class BasicSound::AmbientArgAllocatorCallback
{
public:
    virtual ~AmbientArgAllocatorCallback() {}
    virtual void* detail_AllocAmbientArg( size_t argSize ) = 0;
    virtual void detail_FreeAmbientArg(
        void* arg,
        const internal::BasicSound* sound
    ) = 0;
};

} } } // namespace nw::snd::internal

#endif // NW_SND_BASIC_SOUND_H_
