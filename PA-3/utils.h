#include <iostream>

using namespace std;

class Instruction
{
public:
    void setCommand(string cmd);
    void setValue(int val);

    string getCommand();
    int getValue();

private:
    string command;
    int value;
};

class InstructionSequence
{
public:
    InstructionSequence();
    ~InstructionSequence();

    int getLength();
    Instruction &getInstruction(int index);

    void parseInstructions(const char *arg);
    void printInstructions();

private:
    Instruction *instructions;
    int length;
};

const char *const TASK_1_DEFAULT_ARGUMENT =
    "[('insertion',42), ('insertion',20), ('insertion',17), ('insertion',13), "
    "('insertion',28), ('insertion',14), ('bubbleSort',NULL)]";
const char *const TASK_2_DEFAULT_ARGUMENT =
    "[('insertion',56),('insertion',42), ('insertion',20),('insertion',17), "
    "('insertion',13),('insertion',28), ('insertion',14),('mergeSort',NULL)]";
const char *const TASK_3_DEFAULT_ARGUMENT = "[('insertion',4), ('insertion',6), ('insertion',6), ('insertion',7), ('deletion',7),('sum', 2)]";
const char *const TASK_4_DEFAULT_ARGUMENT = "aabbbccccddddd";
const char *const TASK_5_DEFAULT_ARGUMENT = "[('M',4), ('insertion',32615)]";
const char *const TASK_6_DEFAULT_ARGUMENT = "[('M',4), ('k',3), ('d',2), ('insertion',32615), ('insertion',315), ('insertion',6468), ('insertion',94833)]";
