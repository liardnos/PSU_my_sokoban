##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile for bistro-matic
##

#http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html

SRC		=		main.c

SRCT 	=		./tests/

NAME	=		a.out

FLAGS	=		-L./lib/my -lmy -I./include/ -lncurses

TFLAG 	= 		-lcriterion --coverage -fprofile-arcs

COV 	=		--exclude tests/ -o coverage.html



all:
		make -C ./lib/my re
		gcc -o $(NAME) $(SRC) $(FLAGS)

clean:
		rm -f $(OBJ)
		make -C ./lib/my clean
		rm -f *.html
		rm -f *.gcno
		rm -f *.gcda

fclean:	clean
		rm -f $(NAME)
		make -C ./lib/my fclean
		rm -f *.gcno
		rm -f *.gcda
		rm -f *.html
		rm -f vgcore.*

clear:
		clear

re: clear fclean all

run: fclean all
	./$(NAME)

tests_run:
		make -C ./lib/my re
		gcc -o $(NAME) $(SRC) $(SRCT) $(TFLAG) $(FLAGS)
		-./$(NAME)
		gcovr --exclude tests/
		gcovr --html $(COV) --html-title $(NAME) --html-details
		rm -f *.gcno
		rm -f *.gcda

vaslgrind: fclean
	clear
	make -C ./lib/my valgrind
	gcc -g -o $(NAME) $(SRC) $(FLAGS)
	valgrind -s --leak-check=full --track-origins=yes ./$(NAME) map #&> valgrind_log

#-s --leak-check=full

#563434*232323%(233424+23423423-23482347)

COPY_REPO:
