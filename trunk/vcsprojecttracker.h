/*  cbvcs Code::Blocks version control system plugin

    Copyright (C) 2011 Dushara Jayasinghe.

    cbvcs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cbvcs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cbvcs.  If not, see <http://www.gnu.org/licenses/>.
*/
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
