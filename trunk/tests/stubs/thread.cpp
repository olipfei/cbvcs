/* stubgen: reading from stdin */
#include <wx/thread.h>

/***********************************************************************
 * AUTHOR: Dushara Jayasinghe <dushara>
 *   FILE: stdout
 *   DATE: Mon Feb 14 23:49:34 2011
 *  DESCR:
 ***********************************************************************/

/***********************************************************************
 *  Method: wxMutex::wxMutex
 *  Params: wxMutexType mutexType
 * Effects:
 ***********************************************************************/
wxMutex::wxMutex(wxMutexType mutexType)
{
}


/***********************************************************************
 *  Method: wxMutex::~wxMutex
 *  Params:
 * Effects:
 ***********************************************************************/
wxMutex::~wxMutex()
{
}


/***********************************************************************
 *  Method: wxMutex::IsOk
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxMutex::IsOk() const
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxMutex::Lock
 *  Params:
 * Returns: wxMutexError
 * Effects:
 ***********************************************************************/
wxMutexError
wxMutex::Lock()
{
    wxMutexError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxMutex::TryLock
 *  Params:
 * Returns: wxMutexError
 * Effects:
 ***********************************************************************/
wxMutexError
wxMutex::TryLock()
{
    wxMutexError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxMutex::Unlock
 *  Params:
 * Returns: wxMutexError
 * Effects:
 ***********************************************************************/
wxMutexError
wxMutex::Unlock()
{
    wxMutexError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxCondition::wxCondition
 *  Params: wxMutex &mutex
 * Effects:
 ***********************************************************************/
wxCondition::wxCondition(wxMutex &mutex)
{
}


/***********************************************************************
 *  Method: wxCondition::~wxCondition
 *  Params:
 * Effects:
 ***********************************************************************/
wxCondition::~wxCondition()
{
}


/***********************************************************************
 *  Method: wxCondition::IsOk
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxCondition::IsOk() const
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxCondition::Wait
 *  Params:
 * Returns: wxCondError
 * Effects:
 ***********************************************************************/
wxCondError
wxCondition::Wait()
{
    wxCondError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxCondition::WaitTimeout
 *  Params: unsigned long milliseconds
 * Returns: wxCondError
 * Effects:
 ***********************************************************************/
wxCondError
wxCondition::WaitTimeout(unsigned long milliseconds)
{
    wxCondError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxCondition::Signal
 *  Params:
 * Returns: wxCondError
 * Effects:
 ***********************************************************************/
wxCondError
wxCondition::Signal()
{
    wxCondError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxCondition::Broadcast
 *  Params:
 * Returns: wxCondError
 * Effects:
 ***********************************************************************/
wxCondError
wxCondition::Broadcast()
{
    wxCondError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxSemaphore::wxSemaphore
 *  Params: int initialcount, int maxcount
 * Effects:
 ***********************************************************************/
wxSemaphore::wxSemaphore(int initialcount, int maxcount)
{
}


/***********************************************************************
 *  Method: wxSemaphore::~wxSemaphore
 *  Params:
 * Effects:
 ***********************************************************************/
wxSemaphore::~wxSemaphore()
{
}


/***********************************************************************
 *  Method: wxSemaphore::IsOk
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxSemaphore::IsOk() const
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxSemaphore::Wait
 *  Params:
 * Returns: wxSemaError
 * Effects:
 ***********************************************************************/
wxSemaError
wxSemaphore::Wait()
{
    wxSemaError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxSemaphore::TryWait
 *  Params:
 * Returns: wxSemaError
 * Effects:
 ***********************************************************************/
wxSemaError
wxSemaphore::TryWait()
{
    wxSemaError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxSemaphore::WaitTimeout
 *  Params: unsigned long milliseconds
 * Returns: wxSemaError
 * Effects:
 ***********************************************************************/
wxSemaError
wxSemaphore::WaitTimeout(unsigned long milliseconds)
{
    wxSemaError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxSemaphore::Post
 *  Params:
 * Returns: wxSemaError
 * Effects:
 ***********************************************************************/
wxSemaError
wxSemaphore::Post()
{
    wxSemaError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::This
 *  Params:
 * Returns: wxThread *
 * Effects:
 ***********************************************************************/
wxThread *
wxThread::This()
{
    return NULL;
}


/***********************************************************************
 *  Method: wxThread::IsMain
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxThread::IsMain()
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::Yield
 *  Params:
 * Returns: void
 * Effects:
 ***********************************************************************/
void
wxThread::Yield()
{
}


/***********************************************************************
 *  Method: wxThread::Sleep
 *  Params: unsigned long milliseconds
 * Returns: void
 * Effects:
 ***********************************************************************/
void
wxThread::Sleep(unsigned long milliseconds)
{
}


/***********************************************************************
 *  Method: wxThread::GetCPUCount
 *  Params:
 * Returns: int
 * Effects:
 ***********************************************************************/
int
wxThread::GetCPUCount()
{
    int dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::GetCurrentId
 *  Params:
 * Returns: wxThreadIdType
 * Effects:
 ***********************************************************************/
wxThreadIdType
wxThread::GetCurrentId()
{
    wxThreadIdType dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::SetConcurrency
 *  Params: size_t level
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxThread::SetConcurrency(size_t level)
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::wxThread
 *  Params: wxThreadKind kind
 * Effects:
 ***********************************************************************/
wxThread::wxThread(wxThreadKind kind)
{
}


/***********************************************************************
 *  Method: wxThread::Create
 *  Params: unsigned int stackSize
 * Returns: wxThreadError
 * Effects:
 ***********************************************************************/
wxThreadError
wxThread::Create(unsigned int stackSize)
{
    wxThreadError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::Run
 *  Params:
 * Returns: wxThreadError
 * Effects:
 ***********************************************************************/
wxThreadError
wxThread::Run()
{
    wxThreadError dummy;

    return dummy;
}

#if 0
/***********************************************************************
 *  Method: wxThread::Wait
 *  Params:
 * Returns: ExitCode
 * Effects:
 ***********************************************************************/
ExitCode
wxThread::Wait()
{
    return 0;
}
#endif

/***********************************************************************
 *  Method: wxThread::Kill
 *  Params:
 * Returns: wxThreadError
 * Effects:
 ***********************************************************************/
wxThreadError
wxThread::Kill()
{
    wxThreadError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::Pause
 *  Params:
 * Returns: wxThreadError
 * Effects:
 ***********************************************************************/
wxThreadError
wxThread::Pause()
{
    wxThreadError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::Resume
 *  Params:
 * Returns: wxThreadError
 * Effects:
 ***********************************************************************/
wxThreadError
wxThread::Resume()
{
    wxThreadError dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::SetPriority
 *  Params: unsigned int prio
 * Returns: void
 * Effects:
 ***********************************************************************/
void
wxThread::SetPriority(unsigned int prio)
{
}


/***********************************************************************
 *  Method: wxThread::GetPriority
 *  Params:
 * Returns: unsigned int
 * Effects:
 ***********************************************************************/
unsigned int
wxThread::GetPriority() const
{
    unsigned int dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::IsAlive
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxThread::IsAlive() const
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::IsRunning
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxThread::IsRunning() const
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::IsPaused
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxThread::IsPaused() const
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::GetId
 *  Params:
 * Returns: wxThreadIdType
 * Effects:
 ***********************************************************************/
wxThreadIdType
wxThread::GetId() const
{
    wxThreadIdType dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::TestDestroy
 *  Params:
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
wxThread::TestDestroy()
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: wxThread::~wxThread
 *  Params:
 * Effects:
 ***********************************************************************/
wxThread::~wxThread()
{
}


/***********************************************************************
 *  Method: wxThread::Exit
 *  Params: ExitCode exitcode
 * Returns: void
 * Effects:
 ***********************************************************************/
void
wxThread::Exit(ExitCode exitcode)
{
}
