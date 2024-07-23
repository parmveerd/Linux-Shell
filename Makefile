all: my_userid my_storage_use my_shells

my_userid: my_userid.c
	gcc -o my_userid my_userid.c

my_storage_use: my_storage_use.c
	gcc -o my_storage_use my_storage_use.c

my_shells: my_shells.c 
	gcc -o my_shells my_shells.c

clean:
	rm -f my_userid my_storage_use my_shells *.o