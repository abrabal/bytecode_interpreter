typedef enum InstructionSet {
    OR = 64, 
    NAND = 65, 
    NOR = 66, 
    AND = 67, 
    ADD = 68, 
    SUB = 69, 
    NEVER = 192, 
    EQUAL_ZERO = 193,             
    LESS_THEN_ZERO = 194, 
    LESS_EQUAL_ZERO = 195, 
    ALWAYS = 196, 
    NOT_EQUAL_ZERO = 197, 
    GREATER_EQUAL_THEN_ZERO = 198,
    GREATER_THEN_ZERO = 199} InstructionSet;

    #define COPY_MODE 128
    #define IMMEDIATE_MODE 0
