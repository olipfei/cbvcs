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
#ifndef COPYPROTECTOR_H
#define COPYPROTECTOR_H


class CopyProtector
{
    public:
        /** Default constructor */
        CopyProtector() {}
        /** Default destructor */
        ~CopyProtector() {}

    protected:

    private:
        /** Copy constructor (undefined)
         */
        CopyProtector(const CopyProtector&);

        /** Assignment operator (undefined)
         */
        CopyProtector& operator=(const CopyProtector&);
};

#endif // COPYPROTECTOR_H
