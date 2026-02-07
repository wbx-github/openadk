\ OLPC boot script
visible
" rw root=/dev/mmcblk0p1 loglevel=9 fbcon=font:SUN12x22 console=tty0 net.ifnames=0 iommu=off" expand$ to boot-file
" last:\boot\kernel" expand$ to boot-device
unfreeze
boot
