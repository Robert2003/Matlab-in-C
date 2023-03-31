// Damian Mihai-Robert, 312CA
#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

/*
Functia aloca memorie pentru o matrice noua, pe pozitia last_index, adica la
sfarsitul colectiei si ii citeste elementele.
*/
void read_matrix(int ****v, int last_index,
				 int nr_lines, int nr_cols)
{
	//Aloc spatiu in colectie pentru o matrice.
	alloc_collection(v, last_index);
	//Aloc matricea de la ultima pozitie
	(*v)[last_index] = alloc_matrix(nr_lines, nr_cols);

	if ((*v)[last_index])
		for (int i = 0; i < nr_lines; i++)
			for (int j = 0; j < nr_cols; j++)
				scanf("%d", &(*v)[last_index][i][j]);
}

//Functia printeaza matricea de la indexul dat.
void print_matrix_at_index(int ***v, dims *dimensions, int index)
{
	for (int i = 0; i < dimensions[index].nr_lines; i++) {
		for (int j = 0; j < dimensions[index].nr_cols; j++)
			printf("%d ", v[index][i][j]);
		printf("\n");
	}
}

/*
Functia primeste o lista de linii, o lista de coloane si construieste matriecea
b cu elementele din v aflate la intersectia liniilor si coloanelor din liste.
*/
void trim_matrix(int ***v, int index, int ***b, int nr_lines,
				 int nr_cols, int *l_list, int *c_list)
{
	(*b) = alloc_matrix(nr_lines, nr_cols);

	if ((*b))
		for (int i = 0; i < nr_lines; i++)
			for (int j = 0; j < nr_cols; j++)
				(*b)[i][j] = v[index][l_list[i]][c_list[j]];
}

/*
Functia adauga matricea b in colectia v, la indexul dat.
*/
void add_matrix_at_index(int ****v, int *last_index, dims **dimensions,
						 int ***b, int nr_lines, int nr_cols, int index)
{
	/*
	Daca indexul la care vreau sa adaug matricea e mai mic decat indexul
	ultimei matrice, atunci sterg matricea veche din memorie si o adaug
	pe cea dorita la acel index.
	*/
	if (index <= (*last_index)) {
		//Sterg matricea de pe pozitia index.
		dealloc_matrix(&(*v)[index], (*dimensions)[index].nr_lines);

		//v[index] primeste pointer spre zona de memorie unde se afla b.
		(*v)[index] = (*b);
		//Pe pozitia index in structul de dimensiuni, le modific cu cele noi.
		update_dimensions_at_index(dimensions, (*last_index),
								   nr_lines, nr_cols, index);
		//b nu va mai pointa la zona de memorie unde se afla matricea.
		(*b) = NULL;
	} else {
		//De data aceasta adaug dimensiunile matricii la finalul structului.
		update_dimensions_at_index(dimensions, (*last_index),
								   nr_lines, nr_cols, index);
		(*last_index)++;
		alloc_collection(v, (*last_index));
		(*v)[index] = (*b);
		(*b) = NULL;
	}
}

/*
Functia redimensioneaza matricea de la indexul dat.
*/
void resize_matrix_at_index(int ****v, int *last_index, int index,
							int nr_lines, int nr_cols, int *l_list,
							int *c_list, dims **dimensions)
{
	int **b;
	/*
	Creez in b matricea din v, cu elementele aflate la intersectia liniilor
	si coloanelor din listele c_list si l_list.
	*/
	trim_matrix((*v), index, &b, nr_lines, nr_cols, l_list, c_list);

	// Daca nu am putut aloca memorie pentru b.
	if (!b) {
		dealloc_all(v, dimensions, last_index);
		exit(-1);
	}
	/*
	Adaug matricea formata la indexul dat.
	*/
	add_matrix_at_index(v, last_index, dimensions, &b,
						nr_lines, nr_cols, index);
}

/*
Functia returneaza matricea obtinuta din inmultirea a doua matrice.
*/
int **multiply_matrices(int **v, int **b, dims A_dimension, dims B_dimension)
{
	if (A_dimension.nr_cols == B_dimension.nr_lines) {
		int **c, prod;
		c = alloc_matrix(A_dimension.nr_lines, B_dimension.nr_cols);
		for (int i = 0; i < A_dimension.nr_lines; i++)
			for (int j = 0; j < B_dimension.nr_cols; j++) {
				for (int k = 0; k < B_dimension.nr_lines; k++) {
					prod = (v[i][k] * b[k][j]);
					c[i][j] = (c[i][j] + prod) % MOD;
				}

				if (c[i][j] < 0)
					c[i][j] += MOD;
			}

		if (c)
			return c;
		return NULL;
	}

	return NULL;
}

/*
Functia calculeaza produsul dintre matricea v si matricea b, iar rezultatul
este stocat in v.
Este folosita la exponentierea rapida, acolo unde am nevoie de calcule pe
pe aceeasi matrice, nu de una noua.
*/
void multiply_matrices_in_place(int ***v, int **b,
								dims A_dimension, dims B_dimension)
{
	if (A_dimension.nr_cols == B_dimension.nr_lines) {
		int **c, prod;
		c = alloc_matrix(A_dimension.nr_lines, B_dimension.nr_cols);
		for (int i = 0; i < A_dimension.nr_lines; i++)
			for (int j = 0; j < B_dimension.nr_cols; j++) {
				for (int k = 0; k < B_dimension.nr_lines; k++) {
					prod = ((*v)[i][k] * b[k][j]);
					c[i][j] = (c[i][j] + prod) % MOD;
				}
				/*
				Daca este un numar negativ dupa inmultiri si adunari,
				adun 10007, conform cerintei.
				*/
				if (c[i][j] < 0)
					c[i][j] += MOD;
			}

		//Sterg matricea veche din colectie
		for (int i = 0; i < A_dimension.nr_lines; i++)
			free((*v)[i]);
		free((*v));
		//(*v) va pointa la zona de memorie unde se afla matricea auxiliara.
		(*v) = c;
		c = NULL;
	}
}

/*
Functia sorteaza matricile crescator dupa suma elementelor lor.
*/
void sort_matrices(int ***v, dims *dimensions, int last_index)
{
	int nr_lines, nr_cols;
	int **aux_mat, aux_nr;
	dims aux_dim;
	/*
	sums este un vector in care pe pozitia i se afla suma elementelor
	matricei de pe pozitia i.
	*/
	int *sums = (int *)calloc(last_index + 1, sizeof(int));
	for (int k = 0; k <= last_index; k++) {
		//nr_lines si nr_cols sunt dimensiunile matricei.
		//Utilizez variabilele pentru a scurta liniile de cod.
		nr_lines = dimensions[k].nr_lines;
		nr_cols = dimensions[k].nr_cols;
		for (int i = 0; i < nr_lines; i++)
			for (int j = 0; j < nr_cols; j++)
				sums[k] = (sums[k] + v[k][i][j]) % MOD;
		/*
		Daca este un numar negativ dupa inmultiri si adunari,
		adun 10007, conform cerintei.
		*/
		if (sums[k] < 0)
			sums[k] += MOD;
	}

	for (int i = 0; i < last_index; i++)
		for (int j = i + 1; j <= last_index; j++)
			if (sums[i] > sums[j]) {
				/*
				In continuare fac 3 interschimbari, dar pe 3 tipuri de date
				diferite, ceea ce inseamna ca nu puteam sa fac o singura
				fucntie care sa interschimbe. Sau cel putin nu stiu eu :(((

				Aici este interschimbare de pointer de matrici. Practic, nu se
				interschimba valorile matricelor, ci doar zona de memorie la
				care arata pointerii.
				*/
				aux_mat = v[i];
				v[i] = v[j];
				v[j] = aux_mat;

				/*
				Aici se interschimba pointerii de tipul dims, adica un struct.
				*/
				aux_dim = dimensions[i];
				dimensions[i] = dimensions[j];
				dimensions[j] = aux_dim;

				/*
				Aici se interschimba valorile din vectorul de sume.
				*/
				aux_nr = sums[i];
				sums[i] = sums[j];
				sums[j] = aux_nr;
			}

	//Dau free la vectorul de sume.
	free(sums);
}

/*
Functia creeaza transpusa matricei si o adauga la indexul dat.
*/
void transpose_at_index(int ****v, dims **dimensions,
						int *last_index, int index)
{
	int **transpose;
	int nr_lines, nr_cols;

	if (index > (*last_index)) {
		printf("No matrix with the given index\n");
	} else {
		nr_lines = (*dimensions)[index].nr_cols;
		nr_cols = (*dimensions)[index].nr_lines;

		transpose = alloc_matrix(nr_lines, nr_cols);
		for (int i = 0; i < nr_lines; i++)
			for (int j = 0; j < nr_cols; j++)
				transpose[i][j] = (*v)[index][j][i];
	}
	if (!transpose) {
		dealloc_all(v, dimensions, last_index);
		exit(-1);
	}
	// Adaug matricea pe pozitia index.
	add_matrix_at_index(v, last_index, dimensions, &transpose,
						nr_lines, nr_cols, index);
}

/*
Functia muta toate matricile cu o pozitie la stanga si realoca colectia cu
1 in minus. Nu trebuie sa mai dau free la matricea de pe ultima pozitie,
deoarece realloc se ocupa de acest lucru.
*/
void shift_left_from_index(int ****v, dims **dimensions,
						   int *last_index, int start_index)
{
	int ***aux_v = NULL;
	dims *aux_dimensions = NULL;
	/*
	Fircare (*v)[i] primeste pointer spre zona urmatoarei matrice din memorie
	La fel se procedeaza si pentru structura de dimensiuni
	*/
	for (int i = start_index; i < (*last_index); i++) {
		(*v)[i] = (*v)[i + 1];
		(*dimensions)[i] = (*dimensions)[i + 1];
	}

	aux_v = (int ***)realloc((*v), (*last_index) * sizeof(int **));
	if (aux_v) {
		(*v) = aux_v;
		aux_v = NULL;
	}

	aux_dimensions = (dims *)realloc((*dimensions),
									(*last_index) * sizeof(dims));
	if (aux_dimensions) {
		(*dimensions) = aux_dimensions;
		aux_dimensions = NULL;
	}
	(*last_index)--;
}
