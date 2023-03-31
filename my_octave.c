// Damian Mihai-Robert, 312CA
#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

int main(void)
{
	int last_index = -1;
	int ***v = NULL;
	dims *dimensions = NULL;
	char ch;

	while (scanf("%c", &ch) && ch != 'Q') {
		switch (ch) {
		case 'L':
			L_task(&v, &dimensions, &last_index);
			break;
		case 'D':
			D_task(dimensions, last_index);
			break;
		case 'P':
			P_task(v, dimensions, last_index);
			break;
		case 'C':
			C_task(&v, &last_index, &dimensions);
			break;
		case 'M':
		case 'S':
			// Nu am Strassen, sorry :(((((
			M_task(&v, &dimensions, &last_index);
			break;
		case 'O':
			sort_matrices(v, dimensions, last_index);
			break;
		case 'T':
			T_task(&v, &dimensions, &last_index);
			break;
		case 'R':
			R_task(&v, dimensions, last_index);
			break;
		case 'F':
			F_task(&v, &dimensions, &last_index);
			break;
		default:
			// Ca sa nu afisez atunci cand ch e spatiu sau new line.
			if (ch != ' ' && ch != '\n')
				printf("Unrecognized command\n");
			break;
		}
	}
	// Cazul Q, cand toata memoria trebuie eliberata.
	dealloc_all(&v, &dimensions, &last_index);
	return 0;
}
