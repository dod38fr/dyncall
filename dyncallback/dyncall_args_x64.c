/*
 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_args_x64.c
 Description: Callback's Arguments VM - Implementation for x64
 License:
 Copyright (c) 2007-2009 Daniel Adler <dadler@uni-goettingen.de>,
                         Tassilo Philipp <tphilipp@potion-studios.com>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "dyncall_args_x64.h"


static int64* arg_i64(DCArgs* args)
{
  if (args->reg_count.i < numIntRegs)
    return &args->reg_data.i[args->reg_count.i++];
  else
    return args->stack_ptr++;
}


static double* arg_f64(DCArgs* args)
{
  if (args->reg_count.f < numFloatRegs)
    return &args->reg_data.f[args->reg_count.f++];
  else
  {
    return (double*)args->stack_ptr++;
  }
}


// ----------------------------------------------------------------------------
// C API implementation:


// base operations:

DClonglong  dcArgs_longlong (DCArgs* p) { return *arg_i64(p); }
DCint       dcArgs_int      (DCArgs* p) { return (int)   dcArgs_longlong(p); }
DClong      dcArgs_long     (DCArgs* p) { return (long)  dcArgs_longlong(p); }
DCchar      dcArgs_char     (DCArgs* p) { return (char)  dcArgs_longlong(p); }
DCshort     dcArgs_short    (DCArgs* p) { return (short) dcArgs_longlong(p); }
DCbool      dcArgs_bool     (DCArgs* p) { return (dcArgs_int(p) == 0) ? 0 : 1; }

DCuint      dcArgs_uint     (DCArgs* p) { return (DCuint)      dcArgs_int(p);      }
DCuchar     dcArgs_uchar    (DCArgs* p) { return (DCuchar)     dcArgs_char(p);     }
DCushort    dcArgs_ushort   (DCArgs* p) { return (DCushort)    dcArgs_short(p);    }
DCulong     dcArgs_ulong    (DCArgs* p) { return (DCulong)     dcArgs_long(p);     }
DCulonglong dcArgs_ulonglong(DCArgs* p) { return (DCulonglong) dcArgs_longlong(p); }


DCpointer   dcArgs_pointer  (DCArgs* p) { return (DCpointer)   dcArgs_longlong(p); }

DCdouble    dcArgs_double   (DCArgs* p) { return *arg_f64(p); }
DCfloat     dcArgs_float    (DCArgs* p) { return *(float*)arg_f64(p); }
