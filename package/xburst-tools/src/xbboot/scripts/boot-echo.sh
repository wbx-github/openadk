#!/bin/bash
../host-app/xbboot set_addr 0x80002000
../host-app/xbboot bulk_write ../target-stage1/stage1.bin
../host-app/xbboot start1 0x80002000
../host-app/xbboot get_info
../host-app/xbboot set_addr 0x81c00000
../host-app/xbboot bulk_write ../target-echokernel/echo-kernel.bin
../host-app/xbboot flush_cache
../host-app/xbboot start2 0x81c00000
