#ifndef NW_SND_TASK_H_
#define NW_SND_TASK_H_

#include <nw/ut/ut_LinkList.h>
#include <nw/ut/os/ut_Event.h>

namespace nw { namespace snd { namespace internal {

class TaskManager;

class Task
{
    friend class TaskManager;

public:
    enum Status
    {
        STATUS_FREE,
        STATUS_APPEND,
        STATUS_EXECUTE,
        STATUS_DONE,
        STATUS_CANCEL
    };
    static_assert(sizeof(Status) == 4);

    Task();
    virtual ~Task();

    void SetId(u32 id) { m_Id = id; }

    Status GetStatus() const { return m_Status; }

    void Wait() { m_Event.Wait(); }
    bool TryWait() { return m_Event.TryWait(); }

protected:
    virtual void Execute() = 0;

    void InitializeStatus() { m_Status = STATUS_FREE; }

private:
    NW_DISALLOW_COPY_AND_ASSIGN(Task);

    ut::LinkListNode m_TaskLink;
    ut::Event m_Event;
    Status m_Status;
    u32 m_Id;
};
static_assert(sizeof(Task) == 0x38);

} } } // namespace nw::snd::internal

#endif // NW_SND_TASK_H_
