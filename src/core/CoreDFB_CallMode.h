/*
   (c) Copyright 2001-2012  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include <core/core.h>
#include <fusion/conf.h>
#include <fusion/fusion.h>

typedef enum {
     COREDFB_CALL_DENY,
     COREDFB_CALL_DIRECT,
     COREDFB_CALL_INDIRECT
} CoreDFBCallMode;

static __inline__ CoreDFBCallMode
CoreDFB_CallMode( CoreDFB *core )
{
     printf("CallMode: core->shutdown_tid = %d  direct_gettid = %d  fusion_dispatcher_tid = %d\n", core->shutdown_tid, direct_gettid(), fusion_dispatcher_tid(core->world));
     if (core->shutdown_tid && core->shutdown_tid != direct_gettid() && core->shutdown_tid != fusion_dispatcher_tid(core->world)) {
          while (core_dfb)
               direct_thread_sleep(10000);

          return COREDFB_CALL_DENY;
     }

     if (dfb_core_is_master( core ) || !fusion_config->secure_fusion)
          return COREDFB_CALL_DIRECT;

     return COREDFB_CALL_INDIRECT;
}
