// Filename: interrogateMakeSeq.cxx
// Created by:  drose (15Sep09)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#include "interrogateMakeSeq.h"
#include "indexRemapper.h"
#include "interrogate_datafile.h"

////////////////////////////////////////////////////////////////////
//     Function: InterrogateMakeSeq::output
//       Access: Public
//  Description: Formats the InterrogateMakeSeq data for output to a data
//               file.
////////////////////////////////////////////////////////////////////
void InterrogateMakeSeq::
output(ostream &out) const {
  InterrogateComponent::output(out);
  out << _length_getter << " "
      << _element_getter << " ";
  idf_output_string(out, _scoped_name);
  idf_output_string(out, _comment, '\n');
}

////////////////////////////////////////////////////////////////////
//     Function: InterrogateMakeSeq::input
//       Access: Public
//  Description: Reads the data file as previously formatted by
//               output().
////////////////////////////////////////////////////////////////////
void InterrogateMakeSeq::
input(istream &in) {
  InterrogateComponent::input(in);

  in >> _length_getter >> _element_getter;
  idf_input_string(in, _scoped_name);
  idf_input_string(in, _comment);
}

////////////////////////////////////////////////////////////////////
//     Function: InterrogateMakeSeq::remap_indices
//       Access: Public
//  Description: Remaps all internal index numbers according to the
//               indicated map.  This called from
//               InterrogateDatabase::remap_indices().
////////////////////////////////////////////////////////////////////
void InterrogateMakeSeq::
remap_indices(const IndexRemapper &remap) {
  _length_getter = remap.map_from(_length_getter);
  _element_getter = remap.map_from(_element_getter);
}
