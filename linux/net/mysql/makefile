CC = gcc
target = main     # the final target 
src = $(wildcard *.c)    # the *.c file
objects =$(patsubst %.c,%.o,$(src))   # for create *.o
CPPFLAGES=-I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient    # the conditions 
CFLAGES = -wall -g

$(target):$(objects)     # to create the final target 
	$(CC) $(CPPFLAGES) $^ -o $@


%.o:%.c    # to create *.o
	$(CC) $(CPPFLAGES) -c $< -o $@

clean:   
	rm -f $(objects) $(target)

.PHONY:clean    # fake target
