// Filename: buffered_datagramconnection.cxx
// Created by:  drose (05Mar07)
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

#include "buffered_datagramconnection.h"

#ifdef HAVE_PYTHON
#include "py_panda.h"
#endif

TypeHandle Buffered_DatagramConnection::_type_handle;

////////////////////////////////////////////////////////////////////
// Function name    :  Buffered_DatagramConnection::SendMessage
// Description      : send the message
//
// Return type      : bool
// Argument         : DataGram &msg
////////////////////////////////////////////////////////////////////
bool Buffered_DatagramConnection::
SendMessage(const Datagram &msg) {
  if (IsConnected()) {
    //printf(" DO SendMessage %d\n",msg.get_length());

    int val = _Writer.AddData(msg.get_data(), msg.get_length(), *this);
    if (val >= 0) {
      return true;
    }

    // Raise an exception to give us more information at the python level
    nativenet_cat.warning() << "Buffered_DatagramConnection::SendMessage->Error On Write--Out Buffer = " << _Writer.AmountBuffered() << "\n";
#ifdef HAVE_PYTHON
    ostringstream s;

#if PY_MAJOR_VERSION >= 3
    PyObject *exc_type = PyExc_ConnectionError;
#else
    PyObject *exc_type = PyExc_StandardError;
#endif

    s << endl << "Error sending message: " << endl;
    msg.dump_hex(s);
    s << "Message data: " << msg.get_data() << endl;

    string message = s.str();
    PyErr_SetString(exc_type, message.c_str());
#endif

    ClearAll();
  }

  return false;
}
