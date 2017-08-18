cc=gcc
bin=httpd
src=$(shell ls *.c)
ROOT_PATH=$(shell pwd)
LDFLAGS=-lpthread

.PHONY:all
all:$(bin)

$(bin):$(src)
	$(cc) -o $@ $^  $(LDFLAGS)

.PHONY:debug
debug:
	echo $(src)

