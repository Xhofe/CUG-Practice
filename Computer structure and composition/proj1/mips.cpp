// mips.cpp
#include "mips.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;
char res[100];

/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments all govern how the program interacts with the user.
 */
 //����һ����ʼ���ļ���������ջָ������Ϊ���ݴ洢��ĩβ�ĵ�ַ��
 //����Ĵ�����ʼ��Ϊ�㣬����ָ��Ӹ����ļ���ȡ���������������Ƴ���������û�������
Computer* newComputer(FILE* filein, int printingRegisters, int printingMemory, int debugging, int interactive) {
	int k;
	unsigned int instr;
	Computer* mips = (Computer*)malloc(sizeof(Computer));

	for (k = 0; k < 32; k++) mips->registers[k] = 0;

	/* stack pointer starts at end of data area and grows down */
	// 29�żĴ�����sp��spָ�뿪ʼʱָ���ڴ������ַλ�ã�
	// �����ƶ���ʾ�����ڴ�ջ�Ŀռ䡣
	mips->registers[29] = 0x00400000 + (MAXNUMINSTRS + MAXNUMDATA) * 4;

	k = 0;
	while (1) {
		instr = 0;
		unsigned char temp = 0;
		int i;
		for (i = 0; i < 4; i++) {
			if (!fread(&temp, 1, 1, filein)) {
				i = -1;
				break;
			}
			instr |= temp << (i << 3);
		}
		if (i == -1) break;
		mips->memory[k] = instr;
		k++;

		if (k > MAXNUMINSTRS) {
			fprintf(stderr, "Program is too big (%d instructions, only %d allowed).\n", k, MAXNUMINSTRS);
			exit(1);
		}
	}

	mips->printingRegisters = printingRegisters;
	mips->printingMemory = printingMemory;
	mips->interactive = interactive;
	mips->debugging = debugging;
}

/*
 *  Run the simulation.����ģ�⡣
 */
void simulate(Computer* mips) {
	char s[10];  /* used for handling interactive input *///���ڴ�����ʽ����
	unsigned int instr;
	int changedReg, changedMem;

	mips->pc = 0x00400000;
	while (1) {
		if (mips->interactive) {
			printf("> ");
			fgets(s, 10, stdin);
			if (s[0] == 'q') return;
		}

		instr = contents(mips, mips->pc);
		printf("Executing instruction at %8.8x: %8.8x\n", mips->pc, instr);

		printf("\t%s\n", disassembled(instr, mips->pc));
		//cout << '\t' << disassembled(instr, mips->pc) << endl;
		simulateInstruction(mips, instr, &changedReg, &changedMem);
		printInfo(mips, changedReg, changedMem);
	}
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated.  If changedReg is -1, no register was updated by
 *  the simulated instruction, i.e. it was a branch, a jump, or a store).
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction.  For anything but a store, changedMem will be -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
 /*	��ӡ�йؼ����״̬�������Ϣ.changedReg��������ģ���ָ����ĵļĴ�����������
 *	���changedRegΪ-1����ģ��ָ��û�и��¼Ĵ����������Ƿ�֧����ת��洢��
 *	changedMem��ģ��ָ����ĵ��ڴ�λ�õĵ�ַ�� ���ڳ��̵�֮����κζ�����changedMem��Ϊ-1��
 *	��ǰ��ʼ���ı�־ָʾ�Ǵ�ӡ���мĴ������ǽ���ӡ���ĵļĴ������Լ��Ǵ�ӡ���з���洢�����ǽ���ӡ���ĵĴ洢��λ�á�*/
void printInfo(Computer* mips, int changedReg, int changedMem) {
	int k, addr;
	printf("New pc = %8.8x\n", mips->pc);
	if (!mips->printingRegisters && changedReg == -1) printf("No register was updated.\n");
	else if (!mips->printingRegisters) printf("Updated r%d to %8.8x\n", changedReg, mips->registers[changedReg]);
	else {
		for (k = 0; k < 32; k++) {
			printf("r%2d: %8.8x  ", k, mips->registers[k]);
			if ((k + 1) % 4 == 0) printf("\n");
		}
	}

	if (!mips->printingMemory && changedMem == -1) printf("No memory location was updated.\n");
	else if (!mips->printingMemory) printf("Updated memory at address %8.8x to %8.8x\n", changedMem, contents(mips, changedMem));
	else {
		printf("Nonzero memory\n");
		printf("ADDR     CONTENTS\n");

		for (addr = 0x00400000 + (MAXNUMINSTRS << 2); addr < 0x00400000 + ((MAXNUMINSTRS + MAXNUMDATA) << 2); addr = addr + 4) {
			if (contents(mips, addr) != 0) printf("%8.8x  %8.8x\n", addr, contents(mips, addr));
		}
	}
	printf("\n");
}

/*
 *  Return the contents of memory at the given address.
 *	���ظ�����ַ���ڴ����ݡ�
 */
unsigned int contents(Computer* mips, int addr) {
	int index = (addr - 0x00400000) / 4;
	if (((addr & 0x3) != 0) || (index < 0) || (index >= (MAXNUMINSTRS + MAXNUMDATA))) {
		printf("Invalid Address: %8.8x", addr);
		exit(0);
	}
	return mips->memory[index];
}


/*
 *  Return a string containing the disassembled version of the given
 *  instruction.  You absolutely MUST follow the formatting instructions
 *  given in the assignment.  Note that the string your return should
 *  not include a tab at the beginning or a newline at the end since
 *  those are added in computer.c where this function is called.
 *
 *  Finally you are responsible for managing the memory associated with
 *  any string you return.  If you use malloc, you will somehow need to
 *  free the memory later (note that you cannot modify computer.c).
 *  Hint: static or global variables.
 */
 /*	���ذ�������ָ��ķ����汾���ַ�����
 *	����Ա�����ѭ��ҵ�и����ĸ�ʽ��˵����
 *	��ע�⣬���ص��ַ�����Ӧ������ͷ��ѡ����β���Ļ��з���
 *	��Ϊ��Щ�ַ�������ӵ�computer.c�У��˴����ô˺�����
 *	�������������������ص��κ��ַ�����������ڴ档
 *	�����ʹ��malloc���㽫��ĳ�ַ�ʽ��Ҫ�ͷ��ڴ棨ע���㲻���޸�computer.c����
 *	��ʾ����̬��ȫ�ֱ�����*/
char *disassembled(unsigned int instr, unsigned int pc) {
	/* You replace this code by the right stuff. */
	//if (/*instruction isn't supported */) exit (0); // Your program must exit when an unsupported instruction is detected
	int opcode, rs, rt, rd, shamt, func, immediate; 
	opcode = instr >> 26;
	if (opcode == 0) {//R��ʽָ��
		rs = (instr << 6) >> 27;
		rt = (instr << 11) >> 27;
		rd = (instr << 16) >> 27;
		shamt = (instr << 21) >> 27;
		func = (instr << 26) >> 26;
		if (func == 32 || func == 33 || func == 34 || func == 35 || func == 36 || func == 37 || func == 42) {
			char str1[10], str2[10] = "\t$", str3[10] = ", $", str4[10] = ", $";
			switch (func)
			{
			case 32:
				strcpy_s(str1, "add"); strcpy_s(res, str1); break;
			case 33:
				strcpy_s(str1, "addu"); strcpy_s(res, str1); break;
			case 34:
				strcpy_s(str1, "sub"); strcpy_s(res, str1); break;
			case 35:
				strcpy_s(str1, "subu"); strcpy_s(res, str1); break;
			case 36:
				strcpy_s(str1, "and"); strcpy_s(res, str1); break;
			case 37:
				strcpy_s(str1, "or"); strcpy_s(res, str1); break;
			case 42:
				strcpy_s(str1, "slt"); strcpy_s(res, str1); break;
			default:break;
			}
			strcat_s(str2, to_string(rd).c_str()); strcat_s(res, str2);
			strcat_s(str3, to_string(rs).c_str()); strcat_s(res, str3);
			strcat_s(str4, to_string(rt).c_str()); strcat_s(res, str4);
		}
		else if (func == 0 || func == 2) {

			char str1[10], str2[10] = "\t$", str3[10] = ", $", str4[10] = ", ";
			switch (func)
			{
			case 0:
				strcpy_s(str1, "sll"); strcpy_s(res, str1); break;
			case 2:
				strcpy_s(str1, "srl"); strcpy_s(res, str1); break;
			default:break;
			}
			strcat_s(str2, to_string(rd).c_str()); strcat_s(res, str2);
			strcat_s(str3, to_string(rt).c_str()); strcat_s(res, str3);
			strcat_s(str4, to_string(ImmediatelyConvertToDecimal(shamt)).c_str()); strcat_s(res, str4);
		}
		else if (func == 8)
		{
			char str1[10] = "jr\t$"; strcat_s(str1, to_string(rs).c_str());
			strcpy_s(res, str1);
		}
		else
		{
			exit(0);
		}
	}
	else if (opcode == 8 || opcode == 9 || opcode == 12 || opcode == 13 || opcode == 4 || opcode == 5)
	{
		rs = (instr << 6) >> 27;
		rt = (instr << 11) >> 27;
		immediate = (instr << 16) >> 16;
		immediate = ImmediatelyConvertToDecimal(immediate);
		char str1[10], str2[10] = "\t$", str3[10] = ", $", str4[30] = ", ";
		switch (opcode)
		{
		case 8:
			strcat_s(str2, to_string(rt).c_str()); strcat_s(str3, to_string(rs).c_str());
			strcpy_s(str1, "addi"); strcat_s(str4, to_string(immediate).c_str()); break;
		case 9:
			strcat_s(str2, to_string(rt).c_str()); strcat_s(str3, to_string(rs).c_str());
			strcpy_s(str1, "addiu"); strcat_s(str4, to_string(immediate).c_str()); break;
		case 12:
			strcat_s(str2, to_string(rt).c_str()); strcat_s(str3, to_string(rs).c_str());
			strcpy_s(str1, "andi"); strcat_s(str4, "0x"); strcat_s(str4, tentohex(immediate).c_str()); break;
		case 13:
			strcat_s(str2, to_string(rt).c_str()); strcat_s(str3, to_string(rs).c_str());
			strcpy_s(str1, "ori");  strcat_s(str4, "0x"); strcat_s(str4, tentohex(immediate).c_str()); break;
		case 4:
			strcat_s(str2, to_string(rs).c_str()); strcat_s(str3, to_string(rt).c_str());
			strcpy_s(str1, "beq"); strcat_s(str4, "0x"); strcat_s(str4, tentohex(pc + immediate * 4 + 4).c_str()); break;
		case 5:
			strcat_s(str2, to_string(rs).c_str()); strcat_s(str3, to_string(rt).c_str());
			strcpy_s(str1, "bne"); strcat_s(str4, "0x"); strcat_s(str4, tentohex(pc + immediate * 4 + 4).c_str()); break;
		default:break;
		}strcpy_s(res, str1);
		strcat_s(res, str2);
		strcat_s(res, str3);
		strcat_s(res, str4);
	}
	else if (opcode == 15)
	{
		rt = (instr << 11) >> 27;
		immediate = (instr << 16) >> 16;
		immediate = ImmediatelyConvertToDecimal(immediate);
		char str1[] = "lui", str2[10] = "\t$", str3[7] = ", 0x"; strcpy_s(res, str1);
		strcat_s(str2, to_string(rt).c_str());
		strcat_s(res, str2);
		strcat_s(str3, tentohex(immediate).c_str());
		strcat_s(res, str3);
	}
	else if (opcode == 35 || opcode == 43) {
		rs = (instr << 6) >> 27;
		rt = (instr << 11) >> 27;
		immediate = (instr << 16) >> 16;
		immediate = ImmediatelyConvertToDecimal(immediate);
		char str1[10], str2[10] = "\t$", str3[10] = " ,", str4[10] = "($";
		if (opcode == 35) { strcpy_s(str1, "lw"); }
		else { strcpy_s(str1, "sw"); }
		strcpy_s(res, str1); strcat_s(str2, to_string(rt).c_str()); strcat_s(res, str2);
		strcat_s(str3, to_string(immediate).c_str()); strcat_s(res, str3);
		strcat_s(str4, to_string(rs).c_str()); strcat_s(str4, ")"); strcat_s(res, str4); \
	}
	else if (opcode == 2 || opcode == 3) {
		int address = (instr << 6) >> 6;
		char str1[10], str2[30] = "\t0x";
		if (opcode == 2) { strcpy_s(str1, "j"); }
		else { strcpy_s(str1, "jal"); }
		strcat_s(str2, tentohex(address).c_str());
		strcpy_s(res, str1); strcat_s(res, str2);
	}
	else exit(0);
	//cout << res;
	//cout << res;
	return (res);
}

/*
 *  Simulate the execution of the given instruction, updating the
 *  pc appropriately.
 *
 *  If the instruction modified a register--i.e. if it was lw,
 *  addu, addiu, subu, sll, srl, and, andi, or, ori, lui, or slt
 *  to list a few examples-- return the index of the modified
 *  register in *changedReg, otherwise return -1 in *changedReg.
 *  Note that you should never return 0 in *changedReg, since
 *  $0 cannot be changed!  Note that even if the instruction
 *  changes the register back to it's old value
 *  (e.g. addu $3, $3, $0) the destination register ($3 in the
 *  example) should be marked changed!
 *
 *  If the instruction was sw, return the address of the
 *  updated memory location in *changedMem, otherwise return -1
 *  in *changedMem.
 */
 /*	ģ�����ָ���ִ�У��ʵ�����pc�� ���ָ���޸���һ���Ĵ��� - ����
 *	�������lw��addu��addiu��subu��sll��srl�ͣ�andi��or��ori��lui��slt
 *	�г�һЩ���� - ��changedReg�з����޸ĺ�ļĴ����������������� *changedReg����-1 ��
 *	��ע�⣬����Զ��Ӧ����* changedReg�з���0����Ϊ$ 0�޷����ģ�
 *	��ע�⣬��ʹָ��Ĵ������Ļؾ�ֵ������addu $ 3��$ 3��$ 0����
 *	Ŀ��Ĵ�����ʾ����Ϊ$ 3��ҲӦ���Ϊ�Ѹ��ģ����ָ��Ϊsw���򷵻ظ����ڴ�ĵ�ַ
 *	��* changedMem�е�λ�ã�������* changedMem�з���-1��*/
void simulateInstruction(Computer* mips, unsigned int instr, int *changedReg, int *changedMem) {
	/* You replace this code by the right stuff. */
	mips->pc = mips->pc + 4;
	*changedReg = -1;
	*changedMem = -1;
	int opcode, rs, rt, rd, shamt, func, immediate; char res[100];
	opcode = instr >> 26;
	if (opcode == 0) {//R��ʽָ��
		rs = (instr << 6) >> 27;
		rt = (instr << 11) >> 27;
		rd = (instr << 16) >> 27;
		shamt = (instr << 21) >> 27;
		func = (instr << 26) >> 26;
		if (func == 32 || func == 33 || func == 34 || func == 35 || func == 36 || func == 37 || func == 42) {
			//char str1[5], str2[5] = "\t$", str3[5] = ", $", str4[5] = ", $";
			switch (func)
			{
			case 32://add
				*changedReg = rd;
				mips->registers[rd] = mips->registers[rs] + mips->registers[rt]; break;
			case 33://addu
				*changedReg = rd;
				mips->registers[rd] = mips->registers[rs] + mips->registers[rt]; break;
			case 34://sub
				*changedReg = rd;
				mips->registers[rd] = mips->registers[rs] - mips->registers[rt]; break;
			case 35://subu
				*changedReg = rd;
				mips->registers[rd] = mips->registers[rs] - mips->registers[rt]; break;
			case 36://and
				*changedReg = rd;
				mips->registers[rd] = mips->registers[rs] & mips->registers[rt]; break;
			case 37://or
				*changedReg = rd;
				mips->registers[rd] = mips->registers[rs] | mips->registers[rt]; break;
			case 42://slt
				*changedReg = rd;
				mips->registers[rd] = (mips->registers[rs] < mips->registers[rt]); break;
			default:break;
			}
		}
		else if (func == 0 || func == 2) {
			//char str1[5], str2[5] = "\t$", str3[5] = ", $", str4[5] = ", ";
			switch (func)
			{
			case 0://sll
				*changedReg = rd;
				mips->registers[rd] = (mips->registers[rt] << ImmediatelyConvertToDecimal(shamt)); break;
			case 2://srl
				*changedReg = rd;
				mips->registers[rd] = (mips->registers[rt] >> ImmediatelyConvertToDecimal(shamt)); break;
			default:break;
			}
		}
		else if (func == 8)
		{
			mips->pc = mips->registers[rs];
		}
		else
		{
			exit(0);
		}
	}
	else if (opcode == 8 || opcode == 9 || opcode == 12 || opcode == 13 || opcode == 4 || opcode == 5)
	{
		rs = (instr << 6) >> 27;
		rt = (instr << 11) >> 27;
		immediate = (instr << 16) >> 16;
		immediate = ImmediatelyConvertToDecimal(immediate);
		char str1[10], str2[10] = "\t$", str3[10] = ", $", str4[10] = ", ";
		strcat_s(str2, to_string(rs).c_str()); strcat_s(str3, to_string(rt).c_str());
		switch (opcode)
		{
		case 8://addi
			*changedReg = rt;
			mips->registers[rt] = mips->registers[rs] + ImmediatelyConvertToDecimal(immediate); break;
		case 9://addiu
			*changedReg = rt;
			mips->registers[rt] = mips->registers[rs] + ImmediatelyConvertToDecimal(immediate); break;
		case 12://andi
			*changedReg = rt;
			mips->registers[rt] = mips->registers[rs] & ImmediatelyConvertToDecimal(immediate); break;
		case 13://ori
			*changedReg = rt;
			mips->registers[rt] = mips->registers[rs] | ImmediatelyConvertToDecimal(immediate); break;
		case 4://beq
			if (mips->registers[rs] == mips->registers[rt]) { mips->pc = mips->pc + immediate * 4; }break;
		case 5://bne
			if (mips->registers[rs] != mips->registers[rt]) { mips->pc = mips->pc + immediate * 4; }break;
		default:break;
		}
	}
	else if (opcode == 15)//lui
	{
		rt = (instr << 11) >> 27;
		immediate = (instr << 16) >> 16;
		immediate = ImmediatelyConvertToDecimal(immediate);
		*changedReg = rt;
		mips->registers[rt] = immediate * 65536;
	}
	else if (opcode == 35 || opcode == 43) {
		rs = (instr << 6) >> 27;
		rt = (instr << 11) >> 27;
		immediate = (instr << 16) >> 16;
		immediate = ImmediatelyConvertToDecimal(immediate);
		if (opcode == 35) {
			*changedReg = rt;
			mips->registers[rt] = contents(mips, mips->registers[rs] + immediate);
		}
		else {
			*changedMem = mips->registers[rs] + immediate;
			int index = (*changedMem - 0x00400000) / 4;
			if (((*changedMem & 0x3) != 0) || (index < 0) || (index >= (MAXNUMINSTRS + MAXNUMDATA))) {
				printf("Invalid Address: %8.8x", *changedMem);
				exit(0);
			}
			mips->memory[index] = mips->registers[rt];
		}
	}
	else if (opcode == 2 || opcode == 3) {
		int address = (instr << 6) >> 6;
		char str1[5], str2[27] = "\t";
		if (opcode == 2) { mips->pc = address * 4; }
		else {
			*changedReg = 31;
			mips->registers[31] = mips->pc + 4;
			mips->pc = address * 4;
		}
	}
}


int main (int argc, char *argv[]) {
	int argIndex;
	int printingRegisters = FALSE;
	int printingMemory = FALSE;
	int debugging = FALSE;
	int interactive = FALSE;
	FILE *filein;
	Computer* computer;

	if (argc < 2) {
		cerr << "Not enough arguments.\n";
		return 1;
	}

	for (argIndex=1; argIndex<argc && argv[argIndex][0]=='-'; argIndex++) {
		/* Argument is an option, we hope one of -r, -m, -i, -d. */
		switch (argv[argIndex][1]) {
		case 'r':
			printingRegisters = TRUE;
			break;
		case 'm':
			printingMemory = TRUE;
			break;
		case 'i':
			interactive = TRUE;
			break;
		case 'd':
			debugging = TRUE;
			break;
		default:
			fprintf (stderr, "Invalid option \"%s\".\n", argv[argIndex]);
			fprintf (stderr, "Correct options are -r, -m, -i, -d.\n");
			return 1;
		}
	}

	if (argIndex == argc) {
		fprintf (stderr, "No file name given.\n");
		return 1;
	} else if (argIndex < argc-1) {
		fprintf (stderr, "Too many arguments.\n");
		return 1;
	}

	filein = fopen (argv[argIndex], "rb");
	if (filein == NULL) {
		fprintf (stderr, "Can't open file: %s\n", argv[argIndex]);
		return 1;
	}

	computer = newComputer (filein, printingRegisters, printingMemory, debugging, interactive);
	simulate (computer);
	return 0;
}
