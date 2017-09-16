//-----------------------------------------------------------
//
//    Copyright (C) 2015 by the deal.II authors
//
//    This file is part of the deal.II library.
//
//    The deal.II library is free software; you can use it, redistribute
//    it, and/or modify it under the terms of the GNU Lesser General
//    Public License as published by the Free Software Foundation; either
//    version 2.1 of the License, or (at your option) any later version.
//    The full text of the license can be found in the file LICENSE at
//    the top level of the deal.II distribution.
//
//-----------------------------------------------------------

#include <deal.II/sundials/copy.h>

#ifdef DEAL_II_WITH_SUNDIALS

DEAL_II_NAMESPACE_OPEN
namespace SUNDIALS
{
  namespace internal
  {

#ifdef DEAL_II_WITH_MPI

#ifdef DEAL_II_WITH_TRILINOS


    void copy(TrilinosWrappers::MPI::Vector &dst, const N_Vector &src)
    {
      IndexSet is = dst.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(src));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          dst[is.nth_index_in_set(i)] = NV_Ith_P(src, i);
        }
      dst.compress(VectorOperation::insert);
    }

    void copy(N_Vector &dst, const TrilinosWrappers::MPI::Vector &src)
    {
      IndexSet is = src.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(dst));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          NV_Ith_P(dst, i) = src[is.nth_index_in_set(i)];
        }
    }

    void copy(TrilinosWrappers::MPI::BlockVector &dst, const N_Vector &src)
    {
      IndexSet is = dst.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(src));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          dst[is.nth_index_in_set(i)] = NV_Ith_P(src, i);
        }
      dst.compress(VectorOperation::insert);
    }

    void copy(N_Vector &dst, const TrilinosWrappers::MPI::BlockVector &src)
    {
      IndexSet is = src.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(dst));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          NV_Ith_P(dst, i) = src[is.nth_index_in_set(i)];
        }
    }

#endif //DEAL_II_WITH_TRILINOS

#ifdef DEAL_II_WITH_PETSC

    void copy(PETScWrappers::MPI::Vector &dst, const N_Vector &src)
    {
      IndexSet is = dst.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(src));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          dst[is.nth_index_in_set(i)] = NV_Ith_P(src, i);
        }
      dst.compress(VectorOperation::insert);
    }

    void copy(N_Vector &dst, const PETScWrappers::MPI::Vector &src)
    {
      IndexSet is = src.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(dst));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          NV_Ith_P(dst, i) = src[is.nth_index_in_set(i)];
        }
    }

    void copy(PETScWrappers::MPI::BlockVector &dst, const N_Vector &src)
    {
      IndexSet is = dst.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(src));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          dst[is.nth_index_in_set(i)] = NV_Ith_P(src, i);
        }
      dst.compress(VectorOperation::insert);
    }

    void copy(N_Vector &dst, const PETScWrappers::MPI::BlockVector &src)
    {
      IndexSet is = src.locally_owned_elements();
      AssertDimension(is.n_elements(), NV_LOCLENGTH_P(dst));
      for (unsigned int i=0; i<is.n_elements(); ++i)
        {
          NV_Ith_P(dst, i) = src[is.nth_index_in_set(i)];
        }
    }

#endif //DEAL_II_WITH_PETSC

#endif //mpi

    void copy(BlockVector<double> &dst, const N_Vector &src)
    {
      AssertDimension((unsigned int)NV_LENGTH_S(src), dst.size());
      for (unsigned int i=0; i<dst.size(); ++i)
        {
          dst[i] = NV_Ith_S(src, i);
        }
    }

    void copy(N_Vector &dst, const BlockVector<double> &src)
    {
      AssertDimension((unsigned int)NV_LENGTH_S(dst), src.size());
      for (unsigned int i=0; i<src.size(); ++i)
        {
          NV_Ith_S(dst, i) = src[i];
        }
    }

    void copy(Vector<double> &dst, const N_Vector &src)
    {
      AssertDimension((unsigned int)NV_LENGTH_S(src), dst.size());
      for (unsigned int i=0; i<dst.size(); ++i)
        {
          dst[i] = NV_Ith_S(src, i);
        }
    }

    void copy(N_Vector &dst, const Vector<double> &src)
    {
      AssertDimension((unsigned int)NV_LENGTH_S(dst), src.size());
      for (unsigned int i=0; i<src.size(); ++i)
        {
          NV_Ith_S(dst, i) = src[i];
        }
    }
  }
}
DEAL_II_NAMESPACE_CLOSE

#endif
