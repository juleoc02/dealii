//----------------------------  dof_tools_1b.cc  ---------------------------
//    $Id$
//    Version: $Name$ 
//
//    Copyright (C) 2003, 2004, 2007 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------  dof_tools_1b.cc  ---------------------------

#include "../tests.h"
#include "dof_tools_common.h"
#include <deal.II/lac/compressed_set_sparsity_pattern.h>

// check
//   DoFTools::
//   make_boundary_sparsity_pattern (const DoFHandler<dim>     &,
//                                   const typename FunctionMap<dim>::type &
//                                   const std::vector<unsigned int> &
//	                             CompressedSetSparsityPattern &);

std::string output_file_name = "dof_tools_16b_x/output";


template <int dim>
void
check_this (const DoFHandler<dim> &dof_handler)
{
                                   // test doesn't make much sense if
                                   // no boundary dofs exist
  if (dof_handler.get_fe().dofs_per_face == 0)
    return;
  
  std::vector<types::global_dof_index> map (dof_handler.n_dofs());
  std::set<types::boundary_id> set;
  set.insert (0);
  DoFTools::map_dof_to_boundary_indices (dof_handler, set, map);
  
                                   // create sparsity pattern
  typename FunctionMap<dim>::type boundary_ids;
  boundary_ids[0] = 0;
  CompressedSetSparsityPattern sp (dof_handler.n_boundary_dofs(boundary_ids));
  DoFTools::make_boundary_sparsity_pattern (dof_handler, boundary_ids,
                                            map, sp);
  sp.compress ();
  
                                   // write out 20 lines of this
                                   // pattern (if we write out the
                                   // whole pattern, the output file
                                   // would be in the range of 40 MB)
  for (unsigned int l=0; l<20; ++l)
    {
      const unsigned int line = l*(sp.n_rows()/20);
      for (CompressedSetSparsityPattern::row_iterator
	     c = sp.row_begin(line); c!=sp.row_end(line); ++c)
        deallog << *c << " ";
      deallog << std::endl;
    }

                                   // write out some other indicators
  deallog << sp.bandwidth () << std::endl
          << sp.max_entries_per_row () << std::endl
          << sp.n_nonzero_elements () << std::endl;

  unsigned int hash = 0;
  for (unsigned int l=0; l<sp.n_rows(); ++l)
    hash += l*sp.row_length(l);
  deallog << hash << std::endl;
}
