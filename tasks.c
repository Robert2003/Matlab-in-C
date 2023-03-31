// Damian Mihai-Robert, 312CA
#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

/*
Functia este utilizata pentru taskul L, care citeste o matrice noua.
*/
void L_task(int ****v, dims **dimensions, int *last_index)
{
	int nr_lines, nr_cols;
	scanf("%d%d", &nr_lines, &nr_cols);
	// Adaug dimensiunile matricei la final.
	update_dimensions_at_index(dimensions, (*last_index),
							   nr_lines, nr_cols, (*last_index) + 1);
	(*last_index)++;
	// Citesc matricea pe ultima pozitie.
	read_matrix(v, (*last_index), nr_lines, nr_cols);
	// Daca nu am putut aloca memorie pentru o noua matrice.
	if (!(*v)[(*last_index)]) {
		dealloc_all(v, dimensions, last_index);
		exit(-1);
	}
}

/*
Functia este utilizata pentru taskul D, care printeazaa dimensiunile unei
matrice care se afla la un index dat.
*/
void D_task(dims *dimensions, int last_index)
{
	int index, nr_lines, nr_cols;
	scanf("%d", &index);
	// Daca indexul nu este negativ si nu este nici prea mare.
	if (index <= last_index && index >= 0) {
		nr_lines = dimensions[index].nr_lines;
		nr_cols = dimensions[index].nr_cols;
		printf("%d %d\n", nr_lines, nr_cols);
	} else {
		printf("No matrix with the given index\n");
	}
}

/*
Functia este utilizata pentru taskul  P, care printeaza o matrice de la un
index dat.
*/
void P_task(int ***v, dims *dimensions, int last_index)
{
	int index;
	scanf("%d", &index);
	if (index <= last_index && index >= 0)
		print_matrix_at_index(v, dimensions, index);
	else
		printf("No matrix with the given index\n");
}

/*
Functia este utilizata pentru taskul C, care redimensioneaza o matrice.
*/
void C_task(int ****v, int *last_index, dims **dimensions)
{
	int index, nr_lines, nr_cols;
	int *l_list = NULL, *c_list = NULL;
	scanf("%d", &index);
	scanf("%d", &nr_lines);

	// Citesc lista de linii dupa care se face redimensionarea.
	l_list = (int *)malloc(nr_lines * sizeof(int));
	for (int i = 0; i < nr_lines; i++)
		scanf("%d", &(l_list)[i]);
	scanf("%d", &nr_cols);
	// Citesc lista de coloane dupa care se face redimensionarea.
	c_list = (int *)malloc(nr_cols * sizeof(int));
	for (int i = 0; i < nr_cols; i++)
		scanf("%d", &(c_list)[i]);
	// Daca este un index valid.
	if (index <= (*last_index) && index >= 0) {
		// Redimensionez matricea.
		resize_matrix_at_index(v, &(*last_index), index, nr_lines,
							   nr_cols, l_list, c_list, &(*dimensions));
		// Sterg listele de linii si coloane
		if (l_list) {
			free(l_list);
			l_list = NULL;
		}

		if (c_list) {
			free(c_list);
			c_list = NULL;
		}

		if (!(*v)[index]) {
			dealloc_all(v, dimensions, last_index);
			exit(-1);
		}
	} else {
		printf("No matrix with the given index\n");
		if (l_list) {
			free(l_list);
			l_list = NULL;
		}

		if (c_list) {
			free(c_list);
			c_list = NULL;
		}
	}
}

/*
Functia este utilizata in M_task, deoarece depaseam 80 de caractere daca scriam
totul in paranteza de la if.
*/
int condition(int index1, int index2, int last_index)
{
	if (index1 > last_index || index2 > last_index)
		return 0;
	if (index1 < 0 || index2 < 0)
		return 0;
	return 1;
}

/*
Functia este utilizata pentru taskul M, care are ca scop inmultirea a 2 matrice
*/
void M_task(int ****v, dims **dimensions, int *last_index)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);
	// Daca sunt 2 indecsi valizi
	if (condition(index1, index2, (*last_index))) {
		if ((*dimensions)[index1].nr_cols == (*dimensions)[index2].nr_lines) {
			int **c;
			// c va fi pointer la zona de memorie unde se inmultesc matricele.
			c = multiply_matrices((*v)[index1], (*v)[index2],
								  (*dimensions)[index1], (*dimensions)[index2]);
			int nr_lines = (*dimensions)[index1].nr_lines;
			int nr_cols = (*dimensions)[index2].nr_cols;

			// Adaug matricea la finalul colectiei.
			if (c) {
				add_matrix_at_index(v, last_index, dimensions, &c, nr_lines,
									nr_cols, (*last_index) + 1);
			} else {
				dealloc_all(v, dimensions, last_index);
				exit(-1);
			}
		} else {
			printf("Cannot perform matrix multiplication\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

/*
Functia este utilizata pentru taskul T, care pune transpusa unei matrice in
locul ei.
*/
void T_task(int ****v, dims **dimensions, int *last_index)
{
	int index;
	scanf("%d", &index);
	if (index <= (*last_index) && index >= 0)
		transpose_at_index(v, dimensions, last_index, index);
	else
		printf("No matrix with the given index\n");
}

/*
Functia este utilizata pentru taskul R, care realizeaza exponentierea rapida,
in timp logaritmic a unei matrice. Se utilizeaza functia de inmultire, care
pastreaza rezultatul in una din matrice.
*/
void R_task(int ****v, dims *dimensions, int last_index)
{
	int index, exponent;
	scanf("%d%d", &index, &exponent);
	int nr_lines, nr_cols, **helper_matrix;
	if (index > last_index || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		if (exponent < 0) {
			printf("Power should be positive\n");
		} else {
			nr_lines = dimensions[index].nr_lines;
			nr_cols = dimensions[index].nr_cols;
			if (nr_lines != nr_cols) {
				printf("Cannot perform matrix multiplication\n");
			} else {
				// helper_matrix este In, adica matricea unitate.
				helper_matrix = alloc_matrix(nr_lines, nr_cols);
				for (int i = 0; i < nr_lines; i++)
					helper_matrix[i][i] = 1;
				while (exponent) {
					if (exponent % 2 == 1) {
						/*
						Daca exponentul e numar impar, inmultirea se face in
						helper_matrix.
						*/
						multiply_matrices_in_place(&helper_matrix, (*v)[index],
												   dimensions[index],
												   dimensions[index]);
					if (!helper_matrix) {
						dealloc_all(v, &dimensions, &last_index);
						exit(-1);
					}
					}
					/*
					Se mai face o inmultire, de data aceasta rezultatul ramane
					in matricea pe care o ridicam la putere.
					*/
					multiply_matrices_in_place(&(*v)[index], (*v)[index],
											   dimensions[index],
											   dimensions[index]);
					if (!(*v)[index]) {
						dealloc_all(v, &dimensions, &last_index);
						exit(-1);
					}
					exponent /= 2;
				}
				/*
				Rezultatul exponentierii este de fapt in helper_matrix, deci o
				adaug in locul celei vechi.
				*/
				dealloc_matrix(&(*v)[index], nr_lines);
				(*v)[index] = helper_matrix;
			}
		}
	}
}

/*
Functia este utilizata pentru taskul F, care are ca scop eliminarea unei
matrice din colectie.
*/
void F_task(int ****v, dims **dimensions, int *last_index)
{
	int index;
	scanf("%d", &index);
	if (index <= (*last_index) && index >= 0) {
		/*
		Sterge matricea de la pozitia index si deplaseaza stanga toate
		matricele de dupa
		*/
		dealloc_matrix(&(*v)[index], (*dimensions)[index].nr_lines);
		shift_left_from_index(v, dimensions, last_index, index);
	} else {
		printf("No matrix with the given index\n");
	}
}
