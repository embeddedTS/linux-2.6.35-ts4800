/* RCSid: $Header: /cvsroot/ts-4800/dist/linux-2.6.35-ts/drivers/staging/cxt1e1/pmcc4_ioctls.h,v 1.1.1.1 2011/08/19 02:09:02 ronald Exp $
 */

#ifndef _INC_PMCC4_IOCTLS_H_
#define _INC_PMCC4_IOCTLS_H_

/*-----------------------------------------------------------------------------
 * pmcc4_ioctls.h -
 *
 * Copyright (C) 2005  SBE, Inc.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 * For further information, contact via email: support@sbei.com
 * SBE, Inc.  San Ramon, California  U.S.A.
 *-----------------------------------------------------------------------------
 * RCS info:
 * RCS revision: $Revision: 1.1.1.1 $
 * Last changed on $Date: 2011/08/19 02:09:02 $
 * Changed by $Author: ronald $
 *-----------------------------------------------------------------------------
 * $Log: pmcc4_ioctls.h,v $
 * Revision 1.1.1.1  2011/08/19 02:09:02  ronald
 * RG: Kernel 2.6.35 Initial CVS tree for TS-4800
 *
 *
 * Revision 2.0  2005/09/28 00:10:09  rickd
 * Add GNU license info. Switch Ioctls to sbe_ioc.h usage.
 *
 * Revision 1.2  2005/04/28 23:43:03  rickd
 * Add RCS tracking heading.
 *
 *-----------------------------------------------------------------------------
 */

#include "sbew_ioc.h"

enum
{
    // C4_GET_PORT = 0,
    // C4_SET_PORT,
    // C4_GET_CHAN,
    // C4_SET_CHAN,
    C4_DEL_CHAN = 0,
    // C4_CREATE_CHAN,
    // C4_GET_CHAN_STATS,
    // C4_RESET,
    // C4_DEBUG,
    C4_RESET_STATS,
    C4_LOOP_PORT,
    C4_RW_FRMR,
    C4_RW_MSYC,
    C4_RW_PLD
};

#define C4_GET_PORT          SBE_IOC_PORT_GET
#define C4_SET_PORT          SBE_IOC_PORT_SET
#define C4_GET_CHAN          SBE_IOC_CHAN_GET
#define C4_SET_CHAN          SBE_IOC_CHAN_SET
// #define C4_DEL_CHAN          XXX
#define C4_CREATE_CHAN       SBE_IOC_CHAN_NEW
#define C4_GET_CHAN_STATS    SBE_IOC_CHAN_GET_STAT
#define C4_RESET             SBE_IOC_RESET_DEV
#define C4_DEBUG             SBE_IOC_LOGLEVEL
// #define C4_RESET_STATS       XXX
// #define C4_LOOP_PORT         XXX
// #define C4_RW_FRMR           XXX
// #define C4_RW_MSYC           XXX
// #define C4_RW_PLD            XXX

struct c4_chan_stats_wrap
{
    int         channum;
    struct sbecom_chan_stats stats;
};

#endif   /* _INC_PMCC4_IOCTLS_H_ */
