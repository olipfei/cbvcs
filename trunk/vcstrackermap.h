#ifndef VCSTRACKERMAP_H
#define VCSTRACKERMAP_H

#include "copyprotector.h"
#include "vcsprojecttracker.h"

class VcsTrackerMap : private CopyProtector
{
    public:
        /** Default constructor */
        VcsTrackerMap() {}
        /** Default destructor */
        virtual ~VcsTrackerMap();

        bool CreateTracker(const wxString& prjFilename);
        bool RemoveTracker(const wxString& prjFilename);
        vcsProjectTracker* GetTracker(const wxString& prjFilename);
    protected:

    private:
        std::map<const wxString, vcsProjectTracker*> m_Map;
        vcsProjectTracker* Find(const wxString& prjFilename) const;
        void Remove(std::map<const wxString, vcsProjectTracker*>::iterator);
};

#endif // VCSTRACKERMAP_H
