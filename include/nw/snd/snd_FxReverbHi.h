#ifndef NW_SND_FX_REVERB_HI_H_
#define NW_SND_FX_REVERB_HI_H_

#include <nw/snd/snd_FxParam.h>

namespace nw { namespace snd {

class FxReverbHi
{
public:
    struct ReverbHiParam
    {
        f32 preDelayTime;
        f32 fusedTime;
        f32 coloration;
        f32 damping;
        f32 crosstalk;
        f32 outGain;
        FxReverbEarlyReflectionMode earlyMode;
        f32 preDelayTimeMax;
        FxReverbFusedMode fusedMode;
        f32 earlyGain;
        f32 fusedGain;

        ReverbHiParam()
            : preDelayTime(0.02f)
            , fusedTime(3.0f)
            , coloration(0.6f)
            , damping(0.4f)
            , crosstalk(0.1f)
            , outGain(1.0f)
            , earlyMode(FX_REVERB_EARLY_REFLECTION_30MS)
            , preDelayTimeMax(0.02f)
            , fusedMode(FX_REVERB_FUSED_OLD_AXFX)
            , earlyGain(0.0f)
            , fusedGain(1.0f)
        {
        }
    };
};

} }

#endif // NW_SND_FX_REVERB_HI_H_
