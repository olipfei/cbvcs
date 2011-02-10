#ifndef VCSPROJECTTRACKER_H
#define VCSPROJECTTRACKER_H

#include "IVersionControlSystem.h"
#include "copyprotector.h"
#include "VcsTreeItem.h"

class wxString;

class vcsProjectTracker : private CopyProtector
{
    public:
        /** Default constructor

        Takes owmership of vcs
        */
        vcsProjectTracker(IVersionControlSystem* vcs, const wxString& projectPath);
        /** Default destructor */
        virtual ~vcsProjectTracker();
        /** Access m_ProjectState
         * \return The current value of m_ProjectState
         */
        ItemState& GetProjectState() { return m_ProjectState; }
        /** Set m_ProjectState
         * \param val New value to set
         */
        void SetProjectState(ItemState val) { m_ProjectState = val; }
        /** Access m_Vcs
         * \return The current value of m_Vcs
         */
        IVersionControlSystem& GetVcs() const { return m_Vcs; }
    protected:
    private:
        ItemState m_ProjectState; //!< Member variable "m_ProjectState"
        IVersionControlSystem& m_Vcs; //!< Member variable "m_Vcs"
};

#endif // VCSPROJECTTRACKER_H
