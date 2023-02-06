#!/bin/bash

arch=$1
kernel=$2

if [ ! -f $kernel ]; then
  echo "Kernel $kernel not found"
  exit 1
fi

if [ "$arch" = "arcv1" ]; then
  nsimdrv -prop=nsim_isa_family=a700 -prop=nsim_isa_atomic_option=1 -prop=nsim_mmu=3 -prop=icache=32768,64,2,0 -prop=dcache=32768,64,4,0 -prop=nsim_isa_dpfp=none -prop=nsim_isa_shift_option=2 -prop=nsim_isa_swap_option=1 -prop=nsim_isa_bitscan_option=1 -prop=nsim_isa_sat=1 -prop=nsim_isa_mpy32=1 -prop=nsim_isa_enable_timer_0=1 -prop=nsim_isa_enable_timer_1=1 -prop=nsim_mem-dev=uart0 $kernel
fi
if [ "$arch" = "arcv2" ]; then
  nsimdrv -prop=nsim_isa_family=av2hs -prop=nsim_isa_core=1 -prop=chipid=0xffff -prop=nsim_isa_atomic_option=1 -prop=nsim_isa_ll64_option=1 -prop=nsim_mmu=4 -prop=mmu_pagesize=8192 -prop=mmu_super_pagesize=2097152 -prop=mmu_stlb_entries=16 -prop=mmu_ntlb_ways=4 -prop=mmu_ntlb_sets=128 -prop=icache=32768,64,4,0 -prop=dcache=16384,64,2,0 -prop=nsim_isa_shift_option=2 -prop=nsim_isa_swap_option=1 -prop=nsim_isa_bitscan_option=1 -prop=nsim_isa_sat=1 -prop=nsim_isa_div_rem_option=1 -prop=nsim_isa_mpy_option=9 -prop=nsim_isa_enable_timer_0=1 -prop=nsim_isa_enable_timer_1=1 -prop=nsim_isa_number_of_interrupts=32 -prop=nsim_isa_number_of_external_interrupts=32 -prop=isa_counters=1 -prop=nsim_isa_pct_counters=8 -prop=nsim_isa_pct_size=48 -prop=nsim_isa_pct_interrupt=0 -prop=nsim_mem-dev=uart0,kind=dwuart,base=0xf0000000,irq=24 -prop=nsim_isa_aps_feature=1 -prop=nsim_isa_num_actionpoints=4 $kernel
fi
if [ "$arch" = "arcv1-be" ]; then
  nsimdrv -prop=nsim_isa_big_endian=1 -prop=nsim_isa_family=a700 -prop=nsim_isa_atomic_option=1 -prop=nsim_mmu=3 -prop=icache=32768,64,2,0 -prop=dcache=32768,64,4,0 -prop=nsim_isa_dpfp=none -prop=nsim_isa_shift_option=2 -prop=nsim_isa_swap_option=1 -prop=nsim_isa_bitscan_option=1 -prop=nsim_isa_sat=1 -prop=nsim_isa_mpy32=1 -prop=nsim_isa_enable_timer_0=1 -prop=nsim_isa_enable_timer_1=1 -prop=nsim_mem-dev=uart0 $kernel
fi
if [ "$arch" = "arcv2-be" ]; then
  nsimdrv -prop=nsim_isa_big_endian=1 -prop=nsim_isa_family=av2hs -prop=nsim_isa_core=1 -prop=chipid=0xffff -prop=nsim_isa_atomic_option=1 -prop=nsim_isa_ll64_option=1 -prop=nsim_mmu=4 -prop=mmu_pagesize=8192 -prop=mmu_super_pagesize=2097152 -prop=mmu_stlb_entries=16 -prop=mmu_ntlb_ways=4 -prop=mmu_ntlb_sets=128 -prop=icache=32768,64,4,0 -prop=dcache=16384,64,2,0 -prop=nsim_isa_shift_option=2 -prop=nsim_isa_swap_option=1 -prop=nsim_isa_bitscan_option=1 -prop=nsim_isa_sat=1 -prop=nsim_isa_div_rem_option=1 -prop=nsim_isa_mpy_option=9 -prop=nsim_isa_enable_timer_0=1 -prop=nsim_isa_enable_timer_1=1 -prop=nsim_isa_number_of_interrupts=32 -prop=nsim_isa_number_of_external_interrupts=32 -prop=isa_counters=1 -prop=nsim_isa_pct_counters=8 -prop=nsim_isa_pct_size=48 -prop=nsim_isa_pct_interrupt=0 -prop=nsim_mem-dev=uart0,kind=dwuart,base=0xf0000000,irq=24 -prop=nsim_isa_aps_feature=1 -prop=nsim_isa_num_actionpoints=4 $kernel
fi
