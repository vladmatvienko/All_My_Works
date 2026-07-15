all: Quest_1 Quest_2 Quest_3
Quest_1:
	gcc -Werror -Wextra -Wall -o ../build/Quest_1 dmanager_module.c
Quest_2:
	gcc -Werror -Wextra -Wall -o ../build/Quest_2 list.c list_test.c
Quest_3:
	gcc -Werror -Wextra -Wall -o ../build/Quest_3 stack.c stack_test.c
clean:
	rm -rf *.o
rebuild: clean all
