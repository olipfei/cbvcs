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
