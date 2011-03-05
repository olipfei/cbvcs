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
#ifndef VCSTRACKERMAP_H
#define VCSTRACKERMAP_H

#include "copyprotector.h"
#include "vcsprojecttracker.h"

class ICommandExecuter;

class VcsTrackerMap : private CopyProtector
{
    public:
        /** Default constructor */
        VcsTrackerMap() {}
        /** Default destructor */
        virtual ~VcsTrackerMap();

        bool CreateTracker(const wxString& prjFilename,
                           ICommandExecuter& shellUtils);
        bool RemoveTracker(const wxString& prjFilename);
        vcsProjectTracker* GetTracker(const wxString& prjFilename);
    protected:

    private:
        std::map<const wxString, vcsProjectTracker*> m_Map;
        vcsProjectTracker* Find(const wxString& prjFilename) const;
        void Remove(std::map<const wxString, vcsProjectTracker*>::iterator);
};

#endif // VCSTRACKERMAP_H
