// Filename: LNodeIndex.h
// Created on 28 Feb 2004 by Boyce Griffith
//
// Copyright (c) 2002-2010, Boyce Griffith
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of New York University nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef included_LNodeIndex
#define included_LNodeIndex

/////////////////////////////// INCLUDES /////////////////////////////////////

// IBTK INCLUDES
#include <ibtk/Streamable.h>

// SAMRAI INCLUDES
#include <Index.h>
#include <IntVector.h>
#include <tbox/AbstractStream.h>
#include <tbox/DescribedClass.h>
#include <tbox/Pointer.h>

// C++ STDLIB INCLUDES
#include <vector>

/////////////////////////////// CLASS DEFINITION /////////////////////////////

namespace IBTK
{
/*!
 * \brief Class LNodeIndex provides Lagrangian and <A
 * HREF="http://www-unix.mcs.anl.gov/petsc">PETSc</A> indexing information and
 * data storage for a single node of a Lagrangian mesh.
 */
class LNodeIndex
    : public SAMRAI::tbox::DescribedClass
{
public:
    friend bool
    operator<(
        const LNodeIndex& lhs,
        const LNodeIndex& rhs);

    /*!
     * \brief Default constructor.
     */
    LNodeIndex(
        const int lagrangian_nidx=-1,
        const int local_petsc_nidx=-1,
        double* const X_ptr=NULL,
        const SAMRAI::hier::IntVector<NDIM>& periodic_offset=SAMRAI::hier::IntVector<NDIM>(0),
        const std::vector<double>& periodic_displacement=std::vector<double>(NDIM,0.0),
        const std::vector<SAMRAI::tbox::Pointer<Streamable> >& node_data=std::vector<SAMRAI::tbox::Pointer<Streamable> >());

    /*!
     * \brief Copy constructor.
     *
     * \param from The value to copy to this object.
     */
    LNodeIndex(
        const LNodeIndex& from);

    /*!
     * \brief Destructor.
     *
     * The LNodeIndex destructor does nothing interesting.
     */
    ~LNodeIndex();

    /*!
     * \brief Assignment operator.
     *
     * \param that The value to assign to this object.
     *
     * \return A reference to this object.
     */
    LNodeIndex&
    operator=(
        const LNodeIndex& that);

    /*!
     * \return The Lagrangian index referenced by this LNodeIndex.
     */
    int
    getLagrangianIndex() const;

    /*!
     * \brief Reset the Lagrangian index referenced by this LNodeIndex.
     */
    void
    setLagrangianIndex(
        const int lagrangian_nidx);

    /*!
     * \return The local PETSc index referenced by this LNodeIndex.
     */
    int
    getLocalPETScIndex() const;

    /*!
     * \brief Reset the local PETSc index referenced by this LNodeIndex.
     */
    void
    setLocalPETScIndex(
        const int local_petsc_nidx);

    /*!
     * \return A pointer to the physical location of the node referenced by this
     * LNodeIndex.
     */
    double*
    getNodeLocation() const;

    /*!
     * \brief Reset the pointer to the physical location of the node referenced
     * by this LNodeIndex.
     */
    void
    setNodeLocation(
        double* const X_ptr);

    /*!
     * \brief Indicate that the LNodeIndex has been shifted across a periodic
     * boundary.
     */
    void
    registerPeriodicShift(
        const SAMRAI::hier::IntVector<NDIM>& offset,
        const std::vector<double>& displacement);

    /*!
     * \brief Get the periodic offset.
     */
    const SAMRAI::hier::IntVector<NDIM>&
    getPeriodicOffset() const;

    /*!
     * \brief Get the periodic displacement.
     */
    const std::vector<double>&
    getPeriodicDisplacement() const;

    /*!
     * \return A constant reference to all additional data associated with the
     * node referenced by this LNodeIndex.
     */
    const std::vector<SAMRAI::tbox::Pointer<Streamable> >&
    getNodeData() const;

    /*!
     * \return A non-constant reference to all additional data associated with
     * the node referenced by this LNodeIndex.
     */
    std::vector<SAMRAI::tbox::Pointer<Streamable> >&
    getNodeData();

    /*!
     * \brief Reset the additional data associated with the node referenced by
     * this LNodeIndex.
     */
    void
    setNodeData(
        const std::vector<SAMRAI::tbox::Pointer<Streamable> >& node_data);

    /*!
     * \return A pointer to the first data object of subclass T associated with
     * the node referenced by the LNodeIndex.
     *
     * If no object of the specified type is encountered, this method returns a
     * null pointer.
     *
     * \note It is possible for multiple objects of the same sub-type to be
     * associated with each node.  This method returns only the \em first such
     * object encountered in the array of node objects.
     */
    template<class T>
    SAMRAI::tbox::Pointer<T>
    getNodeData() const;

    /*!
     * \return A vector of pointers to all data objects of subclass T associated
     * with the node referenced by the LNodeIndex.
     *
     * If no object of the specified type is encountered, this method returns an
     * empty vector.
     *
     * \note It is possible for multiple objects of the same sub-type to be
     * associated with each node.  This method returns a vector of \em all such
     * objects encountered in the array of node objects.
     */
    template<class T>
    std::vector<SAMRAI::tbox::Pointer<T> >
    getNodeDataVector() const;

    /*!
     * \name Deprecated methods.
     */
    //\{

    /*!
     * \return A constant reference to all additional data associated with the
     * node referenced by this LNodeIndex.
     *
     * \note This method is deprecated.  It should be replaced by calls to
     * getNodeData().
     */
    const std::vector<SAMRAI::tbox::Pointer<Streamable> >&
    getStashData() const;

    /*!
     * \return A non-constant reference to all additional data associated with
     * the node referenced by this LNodeIndex.
     *
     * \note This method is deprecated.  It should be replaced by calls to
     * getNodeData().
     */
    std::vector<SAMRAI::tbox::Pointer<Streamable> >&
    getStashData();

    /*!
     * \brief Reset the additional data associated with the node referenced by
     * this LNodeIndex.
     *
     * \note This method is deprecated.  It should be replaced by calls to
     * setNodeData().
     */
    void
    setStashData(
        const std::vector<SAMRAI::tbox::Pointer<Streamable> >& node_data);

    /*!
     * \return A pointer to the first data object of subclass T associated with
     * the node referenced by the LNodeIndex.
     *
     * If no object of the specified type is encountered, this method returns a
     * null pointer.
     *
     * \note It is possible for multiple objects of the same sub-type to be
     * associated with each node.  This method returns only the \em first such
     * object encountered in the array of node objects.
     *
     * \note This method is deprecated.  It should be replaced by calls to
     * getNodeData().
     */
    template<class T>
    SAMRAI::tbox::Pointer<T>
    getStashData() const;

    /*!
     * \return A vector of pointers to all data objects of subclass T associated
     * with the node referenced by the LNodeIndex.
     *
     * If no object of the specified type is encountered, this method returns an
     * empty vector.
     *
     * \note It is possible for multiple objects of the same sub-type to be
     * associated with each node.  This method returns a vector of \em all such
     * objects encountered in the array of node objects.
     *
     * \note This method is deprecated.  It should be replaced by calls to
     * getNodeData().
     */
    template<class T>
    std::vector<SAMRAI::tbox::Pointer<T> >
    getStashDataVector() const;

    //\}

    /*!
     * \brief Copy data from the source.
     *
     * \note The cell index of the destination object is src_index + src_offset.
     */
    void
    copySourceItem(
        const SAMRAI::hier::Index<NDIM>& src_index,
        const SAMRAI::hier::IntVector<NDIM>& src_offset,
        const LNodeIndex& src_item);

    /*!
     * \brief Return an upper bound on the amount of space required to pack the
     * object to a buffer.
     */
    size_t
    getDataStreamSize() const;

    /*!
     * \brief Pack data into the output stream.
     */
    void
    packStream(
        SAMRAI::tbox::AbstractStream& stream);

    /*!
     * \brief Unpack data from the input stream.
     */
    void
    unpackStream(
        SAMRAI::tbox::AbstractStream& stream,
        const SAMRAI::hier::IntVector<NDIM>& offset);

private:
    /*!
     * Assign that to this.
     */
    void
    assignThatToThis(
        const LNodeIndex& that);

    int d_lagrangian_nidx;  // the fixed global Lagrangian index
    int d_local_petsc_nidx; // the local PETSc index
    double* d_X_ptr;        // a pointer to the physical location of the node

    // the periodic offset and displacement
    SAMRAI::hier::IntVector<NDIM> d_offset;
    std::vector<double> d_displacement;

    // a (possibly empty) collection of data objects that are associated with
    // the node
    std::vector<SAMRAI::tbox::Pointer<Streamable> > d_node_data;
};

/*!
 * \brief Less-than comparison operator.
 *
 * \return Whether lhs < rhs.
 *
 * The ordering is determined on the physical locations of the nodes.  When a
 * set of indices is sorted according to operator<(), the nodes are in the
 * "Fortan" ordering according to their physical location.
 */
bool
operator<(
    const LNodeIndex& lhs,
    const LNodeIndex& rhs);

}// namespace IBTK

/////////////////////////////// INLINE ///////////////////////////////////////

#include <ibtk/LNodeIndex.I>

//////////////////////////////////////////////////////////////////////////////

#endif //#ifndef included_LNodeIndex