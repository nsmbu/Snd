#ifndef NW_SND_SOUND_HEAP_H_
#define NW_SND_SOUND_HEAP_H_

#include <nw/snd/snd_FrameHeap.h>
#include <nw/snd/snd_SoundMemoryAllocatable.h>
#include <nw/ut/os/ut_CriticalSection.h>

namespace nw { namespace snd {

class SoundArchive;
class SoundDataManager;

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

    bool IsValid() const { return m_FrameHeap.IsValid(); }

    int SaveState();
    void LoadState(int level);

    int GetCurrentLevel() const
    {
        ut::ScopedLock<ut::CriticalSection> lock(m_CriticalSection);
        return m_FrameHeap.GetCurrentLevel();
    }

    size_t GetSize() const
    {
        ut::ScopedLock<ut::CriticalSection> lock(m_CriticalSection);
        return m_FrameHeap.GetSize();
    }

    size_t GetFreeSize() const
    {
        ut::ScopedLock<ut::CriticalSection> lock(m_CriticalSection);
        return m_FrameHeap.GetFreeSize();
    }

    void Dump(nw::snd::SoundDataManager& mgr, nw::snd::SoundArchive& arc) const
    {
        ut::ScopedLock<ut::CriticalSection> lock(m_CriticalSection);
        m_FrameHeap.Dump(mgr, arc);
    }

private:
    static void DisposeCallbackFunc(void* mem, unsigned long size, void* arg);

private:
    mutable ut::CriticalSection m_CriticalSection;
    internal::FrameHeap m_FrameHeap;
};
static_assert(sizeof(SoundHeap) == 0x44);

} } // namespace nw::snd

#endif // NW_SND_SOUND_HEAP_H_
