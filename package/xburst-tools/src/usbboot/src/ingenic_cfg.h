/*
 * Copyright(C) 2009  Qi Hardware Inc.,
 * Authors: Xiangfu Liu <xiangfu@sharism.cc>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __INGENIC_CFG_H__
#define __INGENIC_CFG_H__

#include "usb_boot_defines.h"
#include "ingenic_usb.h"

int hand_init_def(struct hand *hand);
int check_dump_cfg(struct hand *hand);
int parse_configure(struct hand *hand, char * file_path);

#endif	/*__INGENIC_CFG_H__ */
