DEST = main
TEST = test
SRC = main.c
TEST_SRC = test.c $(SRC)
OPTIONS = -ansi -pedantic -Werror
TEST_OPTIONS = $(OPTIONS) -Dmain=ofeskoskdofskfodskofk
LIBS = -lm

$(DEST): $(SRC)
	gcc $(SRC) -o $(DEST) $(OPTIONS) $(LIBS)
	
$(TEST): $(TEST_SRC)
	gcc $(TEST_SRC) -o $(TEST) $(TEST_OPTIONS) $(LIBS)
