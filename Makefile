SRCS = ./src/main.c ./src/srm.c
OBJS = $(patsubst ./src/%.c,/tmp/%.o,$(SRCS))

all: setup clean srm

setup:
	mkdir -p ./dist

clean:
	rm -rf $(OBJS) ./dist/srm

/tmp/%.o: ./src/%.c
	gcc -Wall -Wextra -std=c11 -c $< -o $@

srm: $(OBJS)
	gcc -Wall -Wextra -std=c11 -o ./dist/srm $(OBJS)
