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
#ifndef VCSPROJECT_H
#define VCSPROJECT_H

#include "VcsTreeItem.h"


class VcsProject : public VcsTreeItem
{
    public:
        /** Default constructor */
        VcsProject(wxString Name, ItemState& prjState);
        /** Default destructor */
        virtual ~VcsProject();

        virtual void VisualiseState() const;
    protected:
    private:
        ItemState& m_PrjState;
};

#endif // VCSPROJECT_H
