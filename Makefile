obj-m += klsp.o

all: klsp ulsp

klsp:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

ulsp: ulsp.c
	gcc ulsp.c -o procprint

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm procprint
