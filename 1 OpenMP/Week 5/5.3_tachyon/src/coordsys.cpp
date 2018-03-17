/*
    Copyright 2005-2009 Intel Corporation.  All Rights Reserved.

    The source code contained or described herein and all documents related
    to the source code ("Material") are owned by Intel Corporation or its
    suppliers or licensors.  Title to the Material remains with Intel
    Corporation or its suppliers and licensors.  The Material is protected
    by worldwide copyright laws and treaty provisions.  No part of the
    Material may be used, copied, reproduced, modified, published, uploaded,
    posted, transmitted, distributed, or disclosed in any way without
    Intel's prior express written permission.

    No license under any patent, copyright, trade secret or other
    intellectual property right is granted to or conferred upon you by
    disclosure or delivery of the Materials, either expressly, by
    implication, inducement, estoppel or otherwise.  Any license under such
    intellectual property rights must be express and approved by Intel in
    writing.
*/

/*
    The original source for this example is
    Copyright (c) 1994-2008 John E. Stone
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote products
       derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/

/*
 * coordsys.c -  Routines to translate from one coordinate system to another.
 *
 *  $Id: coordsys.cpp,v 1.2 2007-02-22 17:54:15 dpoulsen Exp $
 */

#include "machine.h"
#include "types.h"
#include "coordsys.h"

void xytopolar(flt x, flt y, flt rad, flt * u, flt * v) {
  flt r1;
  r1=x*x + y*y;  
  *v=sqrt(r1 / (rad*rad));
  if (y<0.0) 
    *u=1.0 - acos(x/sqrt(r1))/TWOPI;
  else 
    *u= acos(x/sqrt(r1))/TWOPI; 
}

void xyztocyl(vector pnt, flt height, flt * u, flt * v) {
  flt r1;

  r1=pnt.x*pnt.x + pnt.y*pnt.y;

  *v=pnt.z / height;
  if (pnt.y<0.0) 
    *u=1.0 - acos(pnt.x/sqrt(r1))/TWOPI;
  else 
    *u=acos(pnt.x/sqrt(r1))/TWOPI;
}

void xyztospr(vector pnt, flt * u, flt * v) {
  flt r1, phi, theta;
 
  r1=sqrt(pnt.x*pnt.x + pnt.y*pnt.y + pnt.z*pnt.z);

  phi=acos(-pnt.y/r1);   
  *v=phi/3.1415926;

  theta=acos((pnt.x/r1)/sin(phi))/TWOPI;

  if (pnt.z > 0.0) 
    *u = theta;
  else 
    *u = 1 - theta; 
}


