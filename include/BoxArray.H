/*
** This software is copyright (C) by the Lawrence Berkeley National
** Laboratory.  Permission is granted to reproduce this software for
** non-commercial purposes provided that this notice is left intact.
**  
** It is acknowledged that the U.S. Government has rights to this
** software under Contract DE-AC03-765F00098 between the U.S.  Department
** of Energy and the University of California.
**  
** This software is provided as a professional and academic contribution
** for joint exchange. Thus it is experimental, is provided ``as is'',
** with no warranties of any kind whatsoever, no support, no promise of
** updates, or printed documentation. By using this software, you
** acknowledge that the Lawrence Berkeley National Laboratory and Regents
** of the University of California shall have no liability with respect
** to the infringement of other copyrights by any part of this software.
**  
** For further information about this software, contact:
** 
**         Dr. John Bell
**         Bldg. 50D, Rm. 129,
**         Lawrence Berkeley National Laboratory
**         Berkeley, CA, 94720
**         jbbell@lbl.gov
*/

#ifndef _BOXARRAY_H_
#define _BOXARRAY_H_

//
// $Id: BoxArray.H,v 1.2 2008/12/03 17:54:46 chand Exp $
//

#include <stddef.h>

#include <Boolean.H>
#include <IndexType.H>
#include <BoxList.H>
#include <Array.H>

class BoxList;

//
//@Man:
//@Memo: An Array of Boxes
/*@Doc:

  A BoxArray is a collection of Boxes stored in an Array.  It is a concrete
  class, not a polymorphic one; i.e. you cannot use any of the List
  member functions with a BoxList.

  It does NOT provide an assignment operator.
*/

class BoxArray
{
public:
    //
    //@ManDoc: Write a BoxArray to an ostream in ASCII format.
    //
    friend std::ostream& operator<< (std::ostream&        os,
                                const BoxArray& ba);
    //
    //@ManDoc: Construct an empty BoxArray.
    //
    BoxArray ();
    //
    //@ManDoc: Construct a BoxArray of the specified size.
    //
    BoxArray (size_t size);
    //
    //@ManDoc: Construct a BoxArray from an array of Boxes of size nbox.
    //
    BoxArray (const Box* bxvec,
              int        nbox);
    //
    //@ManDoc: Construct a BoxArray from a BoxList.
    //
    BoxArray (const BoxList& bl);
    //
    //@ManDoc: The copy constructor.
    //
    BoxArray (const BoxArray& bs);
    //
    //@ManDoc: Construct a BoxArray from a checkpoint file.
    //
    BoxArray& operator= (const BoxArray& rhs);
    //
    //@ManDoc: Construct a BoxArray from a checkpoint file.
    //
    BoxArray (std::istream& is);
    //
    //@ManDoc: The destructor.
    //
    ~BoxArray ();

    /*@ManDoc: Initialize the BoxArray from the supplied BoxList.
               It is an error if the BoxArray has already been initialized.
    */
    void define (const BoxList& bl);

    /*@ManDoc: Initialize the BoxArray from the supplied BoxArray.
               It is an error if the BoxArray has already been initialized.
    */
    void define (const BoxArray& bs);

    /*@ManDoc: Initialize the BoxArray from the supplied istream.
               It is an error if the BoxArray has already been initialized.
               Note that the BoxArray in the istream must have been written
               using writeOn().
    */
    void define (std::istream& is);
    //
    //@ManDoc: Remove all Boxes from the BoxArray.
    //
    void clear ();
    //
    //@ManDoc: Resizes the array.  See Array<T>::resize() for the gory details.
    //
    void resize (int len);
    //
    //@ManDoc: Returns the number of elements in the BoxArray.
    //
    int length () const;
    //
    //@ManDoc: Returns true if the BoxArray is not empty.
    //
    bool ready () const;
    //
    //@ManDoc: Output this BoxArray to a checkpoint file.
    //
    std::ostream& writeOn (std::ostream&) const;

    /*@ManDoc: Are the BoxArrays equal?  This function works by examining
               an internally maintained hash value.  It will make a mistake
               once in 256 million.
    */
    bool operator== (const BoxArray& obs) const;

    /*@ManDoc: Are the BoxArrays not equal?  This function works by examining
               an internally maintained hash value.  It will make a mistake
               once in 256 million.
    */
    bool operator != (const BoxArray& obs) const;
    //
    //@ManDoc: Forces each Box in BoxArray to have sides <= block\_size.
    //
    BoxArray& maxSize (int block_size);
    //
    //@ManDoc: Refine each Box in the BoxArray to the specified ratio.
    //
    BoxArray& refine (int refinement_ratio);
    //
    //@ManDoc: Refine each Box in the BoxArray to the specified ratio.
    //
    BoxArray& refine (const IntVect& refinement_ratio);
    //
    //@ManDoc: Coarsen each Box in the BoxArray to the specified ratio.
    //
    BoxArray& coarsen (int refinement_ratio);
    //
    //@ManDoc: Coarsen each Box in the BoxArray to the specified ratio.
    //
    BoxArray& coarsen (const IntVect& refinement_ratio);
    //
    //@ManDoc: Grow each Box in the BoxArray by the specified amount.
    //
    BoxArray& grow (int n);
    //
    //@ManDoc: Grow each Box in the BoxArray by the specified amount.
    //
    BoxArray& grow (const IntVect& iv);

    /*@ManDoc: Grow each Box in the BoxArray on the low and high end
               by n\_cell cells in idir direction.
    */
    BoxArray& grow (int idir,
                    int n_cell);

    /*@ManDoc: Applies surroundingNodes(Box) to each Box in BoxArray.
               See the documentation of Box for details.
    */
    BoxArray& surroundingNodes ();

    /*@ManDoc: Applies surroundingNodes(Box,int) to each Box in
               BoxArray.  See the documentation of Box for details.
    */
    BoxArray& surroundingNodes (int dir);
    //
    //@ManDoc: Applies Box::enclosedCells() to each Box in the BoxArray.
    //
    BoxArray& enclosedCells ();
    //
    //@ManDoc: Applies Box::enclosedCells(int) to each Box in the BoxArray.
    //
    BoxArray& enclosedCells  (int dir);
    //
    //@ManDoc: Applies Box::convert(IndexType) to each Box in the BoxArray.
    //
    BoxArray& convert (IndexType typ);
    //
    //@ManDoc: Applies Box::shift(int,int) to each Box in the BoxArray.
    //
    BoxArray& shift (int dir,
                     int nzones);
    //
    //@ManDoc: Applies Box::shiftHalf(int,int) to each Box in the BoxArray.
    //
    BoxArray& shiftHalf (int dir,
                         int num_halfs);
    //
    //@ManDoc: Applies Box::shiftHalf(IntVect) to each Box in BoxArray.
    //
    BoxArray& shiftHalf (const IntVect &iv);
    //
    //@ManDoc: Set element i in this BoxArray to Box ibox.
    //
    void set (int        i,
              const Box& ibox);
    //
    //@ManDoc: Returns element index of this BoxArray.
    //
    const Box& operator[] (int index) const;
    //
    //@ManDoc: Returns element index of this BoxArray.
    //
    const Box& get (int index) const;

    /*@ManDoc: Returns true if Box is valid and they all have the same
               IndexType.  Is true by default if the BoxArray is empty.
    */
    bool ok () const;
    //
    //@ManDoc: Returns true if set of intersecting Boxes in BoxArray is null.
    //
    bool isDisjoint () const;
    //
    //@ManDoc: Create a BoxList from this BoxArray.
    //
    BoxList boxList () const;
    //
    //@ManDoc: True if the IntVect is within any of the Boxes in this BoxArray.
    //
    bool contains (const IntVect& v) const;

    /*@ManDoc: True if the Box is within any of the Boxes in the List.
               The Box must also have the same IndexType as those in this
               BoxArray.
    */
    bool contains (const Box& b) const;
    //
    //@ManDoc: True if all Boxes in bl are contained in this BoxArray.
    //
    bool contains (const BoxArray& bl) const;
    //
    //@ManDoc: Returns smallest Box that contains all Boxes in this BoxArray.
    //
    Box minimalBox () const;
    //
    //@ManDoc: Makes a BoxArray from the the complement of b2 in b1in.
    //
    friend BoxArray boxComplement (const Box& b1in,
                                   const Box& b2);
    //
    //@ManDoc: Makes a BoxArray from the complement of Box b in BoxArray ba.
    //
    friend BoxArray complementIn (const Box&      b,
                                  const BoxArray& ba);
    //
    //@ManDoc: Makes a BoxArray from the intersection of Box b and BoxArray ba.
    //
    friend BoxArray intersect (const BoxArray& ba,
                               const Box&      b);
protected:
    //
    // Recalculate the internal hash value.
    //
    void rehash ();
    //
    // Returns a 24 bit number (nearly) unique to this BoxArray.
    //
    unsigned long do_hash () const;
    //
    // The Array of Boxes.
    //
    Array<Box> abox;
    //
    // Pseudo-random 24 bit number.
    //
    unsigned long hash_sig;
};

//
// Inlines.
//

inline
void
BoxArray::clear ()
{
    abox.clear();
    hash_sig = 0;
}

inline
void
BoxArray::resize (int len)
{
    abox.resize(len);
    hash_sig = do_hash();
}

inline
int
BoxArray::length () const
{
    return abox.length();
}

inline
bool
BoxArray::ready () const
{
    return abox.ready();
}

inline
bool
BoxArray::operator== (const BoxArray& obs) const
{
    return hash_sig == obs.hash_sig;
}

inline
bool
BoxArray::operator != (const BoxArray& obs) const
{
    return hash_sig != obs.hash_sig;
}

inline
const Box&
BoxArray::operator[] (int index) const
{
    return abox.get(index);
}

inline
const Box&
BoxArray::get (int index) const
{
    return abox.get(index);
}

inline
void
BoxArray::rehash ()
{
    hash_sig = do_hash();
}

#endif /*_BOXARRAY_H_*/
