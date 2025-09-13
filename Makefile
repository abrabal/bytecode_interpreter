CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -fsanitize=address

TARGETS = test_vm.elf test_parser.elf

SRCS_VM = test_vm.c vm.c third_party/unity/unity.c
SRCS_PARS = code_parser.c test_parser.c vm.c

all: $(TARGETS)

test_vm.elf: $(SRCS_VM)
	$(CC) $(CFLAGS) $^ -o $@

test_parser.elf: $(SRCS_PARS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGETS)