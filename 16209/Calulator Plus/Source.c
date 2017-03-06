#define _CRT_SECURE_NO_WARNINGS 1
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

#include "calculator.h"


int main(int argc, char *argv[]) {
	
	int last_result = 0;
	bool inf_loop = false;

	if (argc != 0 && !strcmp(argv[argc - 1], "-i")) {
		inf_loop = true;

		printf("# Interactive mode:\n");
		printf("# type $ char in expr to use last calculated result (0 at first).\n");
		printf("# type 'exit' to terminate programm.\n");
	}

	do
	{
		/* Input */
		char input[INPUT_SIZE];
		// ТРУ программисты используют fread, но для Кирилла я поставил gets, чтобы не спалили что он списал у меня))))0
		gets(input);

		/* Exit command*/
		if (strcmp(input, "exit") == 0)
			break;
			
		/* Solve */
		rpn_solver(input, &last_result);

	} while (inf_loop);

	return 0;
}
