/*
 * Copyright (c) 2013 Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef UTILS_H
#define UTILS_H


#include <string>
#include <map>

using std::string;
using std::map;


namespace storage
{

    /**
     * Lightweight function to get existing disks without full probing.
     *
     * @return list of device names of present disk devices
     */
    list<string> getPresentDisks();


    /**
     * Lightweight function to get mapping from dmraid names to mdadm uuids.
     *
     * @return mapping from dmraid names to mdadm uuids
     */
    map<string, string> DmraidToMdadm();

}


#endif
