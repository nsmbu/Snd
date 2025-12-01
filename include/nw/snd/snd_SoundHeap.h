#ifndef NW_SND_SOUND_HEAP_H_
#define NW_SND_SOUND_HEAP_H_

#include <nw/snd/snd_SoundMemoryAllocatable.h>

namespace nw { namespace snd {

class SoundHeap : public SoundMemoryAllocatable
{
public:
    typedef void (*DisposeCallback)(void* mem, unsigned long size, void* userArg);


public:
    SoundHeap();
    virtual ~SoundHeap();

    bool Create(void* startAddress, size_t size);
    void Destroy();

    virtual void* Alloc(size_t size);
    void* Alloc(size_t size, DisposeCallback callback, void* callbackArg);
    void Clear();

    int SaveState();
    void LoadState(int level);

private:
    static void DisposeCallbackFunc(void* mem, unsigned long size, void* arg);

private:
    u32 m_CriticalSection[0x30 / sizeof(u32)];  // TODO: nw::ut::CriticalSection
    u32 m_FrameHeap[0x10 / sizeof(u32)];        // TODO: nw::snd::internal::FrameHeap
};
static_assert(sizeof(SoundHeap) == 0x44);

} } // namespace nw::snd

#endif // NW_SND_SOUND_HEAP_H_
