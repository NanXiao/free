# free
[free](https://linux.die.net/man/1/free) command for `OpenBSD`:

	# ./free
	                     total              used              free
	Mem:                 4032M               28M             4004M
	Swap:                   0B                0B                0B
P.S, I use [uvmexp.active](https://github.com/openbsd/src/blob/dbdab68da3b0b11846f6b023c8e069c40aa1fd71/sys/uvm/uvmexp.h#L50) to denote "`used`" memory, not "[uvmexp.npages](https://github.com/openbsd/src/blob/dbdab68da3b0b11846f6b023c8e069c40aa1fd71/sys/uvm/uvmexp.h#L48) - [uvmexp.free](https://github.com/openbsd/src/blob/dbdab68da3b0b11846f6b023c8e069c40aa1fd71/sys/uvm/uvmexp.h#L49)".
## Usage  

	# git clone https://github.com/NanXiao/free.git
	# cd free
	# make
	# ./free