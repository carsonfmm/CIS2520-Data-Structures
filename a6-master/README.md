
Date: Tuesday, November 17, 2020
Program Description: This collection of files is a small database system,
		     consisting of 4 programs. These .c programs use hash
                     tables and binary files.

"make all": Used to compile the 5 programs called:
buildidx.c, key2val.c, val2key.c, actors.c

"make clean": This target will delete all .o files

"./buildidx filename.kv capacity": This will execute the buildidx file with
				   a given .kv file and capacity

"./key2val filename.kv 'search term'": This will execute the key2val file
				      with a given .kv file and search term

"./val2key filename.kv 'search term'": This will execute the val2key file
				      with a given .kv file and search term

"./actors 'search term'": This will print all the actors for a given title
