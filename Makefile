CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -fsanitize=address

TARGETS = binaries/test_vm.elf binaries/dump_program.elf

SRCS_VM = test/test_vm.c vm.c third_party/unity/unity.c
SRCS_PARS = code_parser.c utilities/dump_program.c vm.c

all: $(TARGETS)

binaries/test_vm.elf: $(SRCS_VM)
	$(CC) $(CFLAGS) $^ -o $@

binaries/dump_program.elf: $(SRCS_PARS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGETS)