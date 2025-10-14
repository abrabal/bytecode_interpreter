CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -fsanitize=address -I../bytecode_interpreter -Ithird_party/unity

TARGETS = bin/test/test_vm.elf bin/dump_program.elf bin/sandbox.elf bin/code_generator.elf bin/tasks/task_1_add_five.elf bin/tasks/task_2_find_match.elf

SRCS_VM = test/test_vm.c vm.c third_party/unity/unity.c
SRCS_PARS = code_parser.c utilities/dump_program.c vm.c
SRCS_RUN = code_parser.c vm.c sandbox/sandbox.c
SRCS_CODE_GEN = code_parser.c vm.c utilities/code_generator.c
SRCS_TASK_ADD_FIVE =  tasks/task_1_add_five/add_five.c vm.c third_party/unity/unity.c code_parser.c
SRCS_TASK_FIND_MATCH =  tasks/task_2_find_match/task_2_find_match.c vm.c third_party/unity/unity.c code_parser.c

all: $(TARGETS)

bin/test/test_vm.elf: $(SRCS_VM)
	$(CC) $(CFLAGS) $^ -o $@

bin/dump_program.elf: $(SRCS_PARS)
	$(CC) $(CFLAGS) $^ -o $@

bin/sandbox.elf: $(SRCS_RUN)
	$(CC) $(CFLAGS) $^ -o $@

bin/code_generator.elf: $(SRCS_CODE_GEN)
	$(CC) $(CFLAGS) $^ -o $@

bin/tasks/task_1_add_five.elf: $(SRCS_TASK_ADD_FIVE)
	$(CC) $(CFLAGS) $^ -o $@

bin/tasks/task_2_find_match.elf: $(SRCS_TASK_FIND_MATCH)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGETS)