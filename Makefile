version = 1.0

all: sfppsctrl

dist: sfppsctrl.c sfppsctrl.init sfppsctrl.sysconfig Makefile
	rm -Rf sfppsctrl-$(version)
	mkdir -p sfppsctrl-$(version)
	cp $^ sfppsctrl-$(version)
	tar -cvzf sfppsctrl-$(version).tar.gz sfppsctrl-$(version)
	rm -Rf sfppsctrl-$(version)

sfppsctrl: sfppsctrl.c
	gcc -o sfppsctrl sfppsctrl.c
