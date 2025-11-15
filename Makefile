CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -fsanitize=address -I../bytecode_interpreter -Ithird_party/unity

TARGETS = bin/test_vm.elf bin/dump_program.elf

SRCS_VM = test/test_vm.c vm.c third_party/unity/unity.c
SRCS_PARS = code_parser.c utilities/dump_program.c vm.c

all: $(TARGETS)

bin/test_vm.elf: $(SRCS_VM)
	$(CC) $(CFLAGS) $^ -o $@

bin/dump_program.elf: $(SRCS_PARS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGETS)