\ OLPC boot script
visible
" rw root=/dev/sda1 loglevel=9 fbcon=font:SUN12x22 console=tty0 iommu=off" expand$ to boot-file
" last:\boot\kernel" expand$ to boot-device
unfreeze
boot
