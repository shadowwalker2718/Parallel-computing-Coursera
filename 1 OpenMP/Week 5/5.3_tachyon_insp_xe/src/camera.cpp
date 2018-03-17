/*
    Copyright (C) 2013 Intel Corporation. All rights reserved.

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
 * camera.c - This file contains all of the functions for doing camera work.
 *
 *  $Id: camera.cpp,v 1.2 2007-02-22 17:54:15  Exp $
 */

#include "machine.h"
#include "types.h"
#include "macros.h"
#include "vector.h"
#include "camera.h"
#include "util.h"

ray camray(scenedef *scene, int x, int y) {
  ray ray1, newray;
  vector projcent;
  vector projpixel;
  flt px, py, sx, sy;

  sx = (flt) scene->hres; 
  sy = (flt) scene->vres;

  /* calculate the width and height of the image plane given the */
  /* aspect ratio, image resolution, and zoom factor */

  px=((sx / sy) / scene->aspectratio) / scene->camzoom;
  py=1.0 / scene->camzoom;    

  /* assuming viewvec is a unit vector, then the center of the */
  /* image plane is the camera center + vievec                 */
  projcent.x = scene->camcent.x + scene->camviewvec.x;
  projcent.y = scene->camcent.y + scene->camviewvec.y;
  projcent.z = scene->camcent.z + scene->camviewvec.z;

  /* starting from the center of the image plane, we move the   */
  /* center of the pel we're calculating, to                    */ 
  /* projcent + (rightvec * x distance)                         */
  ray1.o=projcent;
  ray1.d=scene->camrightvec;
  projpixel=Raypnt(&ray1, ((x*px/sx) - (px / 2.0))); 

  /* starting from the horizontally translated pel, we move the */
  /* center of the pel we're calculating, to                    */ 
  /* projcent + (upvec * y distance)                            */
  ray1.o=projpixel;
  ray1.d=scene->camupvec;
  projpixel=Raypnt(&ray1, ((y*py/sy) - (py / 2.0)));

  /* now that we have the exact pel center in the image plane */
  /* we create the real primary ray that will be used by the  */
  /* rest of the system.                                      */
  /* The ray is expected to be re-normalized elsewhere, we're */
  /* only really concerned about getting its direction right. */
  newray.o=scene->camcent;
  VSub(&projpixel, &scene->camcent, &newray.d);
  newray.depth = scene->raydepth;
  newray.flags = RT_RAY_REGULAR;  /* camera only generates primary rays */

  return newray;
}


