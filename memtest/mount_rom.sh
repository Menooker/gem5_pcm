gcc -m64 -o memtest memtest.c
mount -o loop,offset=32256 -rw /home/menooker/gem5/disks/linux-x86.img /home/menooker/111

cp memtest /home/menooker/111

/bin