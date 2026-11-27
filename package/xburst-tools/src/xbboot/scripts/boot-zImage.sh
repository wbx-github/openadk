#!/bin/bash
../host-app/xbboot set_addr 0x80002000
../host-app/xbboot bulk_write ../target-stage1/stage1.bin
../host-app/xbboot start1 0x80002000
../host-app/xbboot get_info

../host-app/xbboot flush_cache

../host-app/xbboot set_addr 0x80600000
../host-app/xbboot bulk_write $1
../host-app/xbboot flush_cache
../host-app/xbboot start2 0x80600000
