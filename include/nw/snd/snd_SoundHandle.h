#ifndef NW_SND_SOUND_HANDLE_H_
#define NW_SND_SOUND_HANDLE_H_

#include <nw/snd/snd_BasicSound.h>
#include <nw/snd/snd_Global.h>

namespace nw { namespace snd {

class SoundHandle
{
public:
    enum PauseState
    {
        PAUSE_STATE_NORMAL,
        PAUSE_STATE_PAUSING,
        PAUSE_STATE_PAUSED,
        PAUSE_STATE_UNPAUSING,
        PAUSE_STATE_INVALID
    };

    SoundHandle()
        : m_pSound(NULL)
    {
    }

    ~SoundHandle()
    {
        DetachSound();
    }

    void StartPrepared()
    {
        if (IsAttachedSound())
            m_pSound->StartPrepared();
    }

    void Stop(int fadeFrames)
    {
        if (IsAttachedSound())
        {
          //NW_SND_LOG_APICALL_NW("SoundHandle::Stop [ID:%08x]", m_pSound->GetId());
            m_pSound->Stop(fadeFrames);
        }
    }

    void Pause(bool flag, int fadeFrames)
    {
        if (IsAttachedSound())
        {
          //NW_SND_LOG_APICALL_NW("SoundHandle::Pause [ID:%08x flag:%s frame:%d]", m_pSound->GetId(),flag?"true":"false",fadeFrames);
            m_pSound->Pause(flag, fadeFrames);
        }
    }

    bool IsPrepared() const
    {
        if (IsAttachedSound() && m_pSound->IsPrepared())
            return true;

        return false;
    }

    bool IsPause() const
    {
        if (IsAttachedSound() && m_pSound->IsPause())
            return true;

        return false;
    }

    PauseState GetPauseState() const
    {
        if (!IsAttachedSound())
            return PAUSE_STATE_INVALID;

        internal::BasicSound::PauseState state = m_pSound->GetPauseState();
        return static_cast<PauseState>(state);
    }

    void FadeIn(int frames)
    {
        if (IsAttachedSound())
            m_pSound->FadeIn(frames);
    }

    /*
    int GetRemainingFadeFrames() const
    {
        if (IsAttachedSound())
            return m_pSound->GetRemainingFadeFrames();

        return 0;
    }

    int GetRemainingPauseFadeFrames() const
    {
        if (IsAttachedSound())
            return m_pSound->GetRemainingPauseFadeFrames();

        return 0;
    }
    */

    void SetVolume(f32 volume, int frames = 0)
    {
        if (IsAttachedSound())
            m_pSound->SetVolume(volume, frames);
    }

    void SetPan(f32 pan)
    {
        if (IsAttachedSound())
            m_pSound->SetPan(pan);
    }

    /*
    void SetSurroundPan(f32 surroundPan)
    {
        if (IsAttachedSound())
            m_pSound->SetSurroundPan(surroundPan);
    }

    void SetMainSend(f32 send)
    {
        if (IsAttachedSound())
            m_pSound->SetMainSend(send);
    }

    void SetFxSend(AuxBus bus, f32 send)
    {
        if (IsAttachedSound())
            m_pSound->SetFxSend(bus, send);
    }
    */

    void SetPitch(f32 pitch)
    {
        if (IsAttachedSound())
            m_pSound->SetPitch(pitch);
    }

    /*
    void SetLpfFreq(f32 lpfFreq)
    {
        if (IsAttachedSound())
            m_pSound->SetLpfFreq(lpfFreq);
    }

    void SetBiquadFilter(int type, f32 value)
    {
      //NW_MINMAX_ASSERT(type, BIQUAD_FILTER_TYPE_MIN , BIQUAD_FILTER_TYPE_MAX);
        if (IsAttachedSound())
            m_pSound->SetBiquadFilter(type, value);
    }

    void SetPlayerPriority(int priority)
    {
        if (IsAttachedSound())
            m_pSound->SetPlayerPriority(priority);
    }
    */

    void SetOutputLine(u32 lineFlag)
    {
        if (IsAttachedSound())
            m_pSound->SetOutputLine(lineFlag);
    }

    void ResetOutputLine()
    {
        if (IsAttachedSound())
            m_pSound->ResetOutputLine();
    }

    void SetOutputVolume(OutputDevice device, f32 volume)
    {
        if (IsAttachedSound())
            m_pSound->SetOutputVolume(device, volume);
    }

    /*
    void SetOutputPan(OutputDevice device, f32 pan)
    {
        if (IsAttachedSound())
            m_pSound->SetOutputPan(device, pan);
    }

    void SetOutputSurroundPan(OutputDevice device, f32 span)
    {
        if (IsAttachedSound())
            m_pSound->SetOutputSurroundPan(device, span);
    }

    void SetOutputMainSend(OutputDevice device, f32 send)
    {
        if (IsAttachedSound())
            m_pSound->SetOutputMainSend(device, send);
    }

    void SetOutputFxSend(OutputDevice device, AuxBus bus, f32 send)
    {
        if (IsAttachedSound())
            m_pSound->SetOutputFxSend(device, bus, send);
    }
    */

    void SetMainOutVolume(f32 volume)
    {
        SetOutputVolume(OUTPUT_DEVICE_MAIN, volume);
    }

    void SetDrcOutVolume(f32 volume, u32 drcIndex = 0)
    {
        (void)drcIndex;
        SetOutputVolume(OUTPUT_DEVICE_DRC, volume);
    }

    /*
    void SetDrcPan(f32 pan, u32 drcIndex = 0)
    {
        (void)drcIndex;
        SetOutputPan(OUTPUT_DEVICE_DRC, pan);
    }
    */

    void SetRemoteOutVolume(u32 remoteIndex, f32 volume)
    {
        if (IsAttachedSound())
            m_pSound->SetRemoteOutVolume(remoteIndex, volume);
    }

    /*
    void SetRemoteMainSend(u32 remoteIndex, f32 send)
    {
        if (IsAttachedSound())
            m_pSound->SetRemoteMainSend(remoteIndex, send);
    }

    void SetRemoteFxSend(u32 remoteIndex, f32 send)
    {
        if (IsAttachedSound())
            m_pSound->SetRemoteFxSend(remoteIndex, send);
    }
    */

    bool IsAttachedSound() const
    {
        if (m_pSound != NULL)
            return true;

        return false;
    }

    void DetachSound();

    void SetId(u32 id)
    {
        if (IsAttachedSound())
            m_pSound->SetId(id);
    }

    u32 GetId() const
    {
        if (IsAttachedSound())
            return m_pSound->GetId();

        return internal::BasicSound::INVALID_ID;
    }

    const SoundParam* GetAmbientParam() const
    {
        if (!IsAttachedSound())
            return NULL;

        return &m_pSound->GetAmbientParam();
    }

    void* GetUserParam() const
    {
        if (!IsAttachedSound())
            return NULL;

        return m_pSound->GetUserParam();
    }


    void detail_AttachSound(internal::BasicSound* sound);
    void detail_AttachSoundAsTempHandle(internal::BasicSound* sound);

    internal::BasicSound* detail_GetAttachedSound()
    {
        return m_pSound;
    }

    const internal::BasicSound* detail_GetAttachedSound() const
    {
        return m_pSound;
    }

    /*
    void detail_DuplicateHandle(SoundHandle* handle);
    */

private:
    NW_DISALLOW_COPY_AND_ASSIGN(SoundHandle);

    internal::BasicSound* m_pSound;
};
static_assert(sizeof(SoundHandle) == 4);

} } // namespace nw::snd

#endif // NW_SND_SOUND_HANDLE_H_
