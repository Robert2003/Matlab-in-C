// Damian Mihai-Robert, 312CA
#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

/*
Actualizez vectorul de dimensiuni.
*/
void update_dimensions_at_index(dims **dimensions, int last_index,
								int nr_lines, int nr_cols, int index)
{
	dims *aux_dimensions = NULL;
	/*
	Daca indexul la care doresc sa actualizez este mai mic decat indexul
	ultimei matrice, atunci doar schimb valorile.
	*/
	if (index <= last_index) {
		(*dimensions)[index].nr_lines = nr_lines;
		(*dimensions)[index].nr_cols = nr_cols;
	} else {
		// Daca nu exista nicio matrice inca, aloc spatiu pentru dimensiuni.
		if (last_index == -1) {
			aux_dimensions = (dims *)malloc((last_index + 2) * sizeof(dims));
			if (aux_dimensions)
				(*dimensions) = aux_dimensions;
		} else {
			// Daca exista vreo matrice, cresc vectorul de dimensiuni.
			aux_dimensions = (dims *)realloc((*dimensions),
							(last_index + 2) * sizeof(dims));
			if (aux_dimensions)
				(*dimensions) = aux_dimensions;
		}
		// Pun valorile pe noua pozitie.
		(*dimensions)[index].nr_lines = nr_lines;
		(*dimensions)[index].nr_cols = nr_cols;
	}
}

/*
Aloc sau realoc vectorul de matrici
In aceasta functie last_index este indexul matricii pe care vreau sa o adaug,
nu indexul ultimei matrici pe care am adaugat-o.
*/
void alloc_collection(int ****v, int last_index)
{
	// Daca vreau sa pun pe pozitia 0, adica prima, aloc memorie
	if (last_index == 0)
		(*v) = (int ***)malloc((last_index + 1) * sizeof(int **));
	//Daca exista deja o matrice, doar realoc.
	else
		(*v) = (int ***)realloc((*v), (last_index + 1) * sizeof(int **));
}

/*
Aloc liniile matricei, practic creez coloanele.
*/
void alloc_col(int **v, int nr_cols)
{
	(*v) = (int *)calloc(nr_cols, sizeof(int));
}

/*
Aloc memorie pentru o matrice si returnez pointer spre zona alocata.
*/
int **alloc_matrix(int nr_lines, int nr_cols)
{
	int **a = NULL;
	a = (int **)malloc(nr_lines * sizeof(int *));
	if (!a) {
		free(a);
		return NULL;
	}

	for (int i = 0; i < nr_lines; i++) {
		a[i] = (int *)calloc(nr_cols, sizeof(int));
		if (!a[i]) {
			dealloc_matrix(&a, i);
			return NULL;
		}
	}

	return a;
}

/*
Elibereaza memoria pentru o matrice.
*/
void dealloc_matrix(int ***v, int nr_lines)
{
	for (int i = 0; i < nr_lines; i++)
		free((*v)[i]);
	free((*v));
	(*v) = NULL;
}

/*
Elibereaza toata memoria alocata de program.
*/
void dealloc_all(int ****v, dims **dimensions, int *last_index)
{
	if ((*last_index) >= 0) {
		for (int k = 0; k <= (*last_index); k++) {
			for (int i = 0; i < (*dimensions)[k].nr_lines; i++) {
				if ((*v)[k][i])
					free((*v)[k][i]);
			}

			if ((*v)[k])
				free((*v)[k]);
		}

		if ((*v))
			free((*v));
		if ((*dimensions))
			free((*dimensions));
	}
}
