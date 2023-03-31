// Damian Mihai-Robert, 312CA
#define MOD 10007

typedef struct {
	int nr_lines;
	int nr_cols;
} dims;

void L_task(int ****v, dims **dimensions, int *last_index);
void D_task(dims *dimensions, int last_index);
void P_task(int ***v, dims *dimensions, int last_index);
void C_task(int ****v, int *last_index, dims **dimensions);
void M_task(int ****v, dims **dimensions, int *last_index);
void T_task(int ****v, dims **dimensions, int *last_index);
void R_task(int ****v, dims *dimensions, int last_index);
void F_task(int ****v, dims **dimensions, int *last_index);
void alloc_collection(int ****v, int last_index);
void alloc_col(int **v, int nr_cols);
void read_matrix(int ****v, int last_index,
				 int nr_lines, int nr_cols);
int **alloc_matrix(int nr_lines, int nr_cols);
void dealloc_matrix(int ***v, int nr_lines);
void dealloc_all(int ****v, dims **dimensions, int *last_index);
void update_dimensions_at_index(dims **dimensions, int last_index,
								int nr_lines, int nr_cols, int index);
void print_matrix_at_index(int ***v, dims *dimensions, int index);
void add_matrix_at_index(int ****v, int *last_index, dims **dimensions,
						 int ***b, int nr_lines, int nr_cols, int index);
void transpose_at_index(int ****v, dims **dimensions,
						int *last_index, int index);
void trim_matrix(int ***v, int index, int ***b, int nr_lines,
				 int nr_cols, int *l_list, int *c_list);
void resize_matrix_at_index(int ****v, int *last_index, int index,
							int nr_lines, int nr_cols, int *l_list,
							int *c_list, dims **dimensions);
int **multiply_matrices(int **v, int **b, dims A_dimension, dims B_dimension);
void multiply_matrices_in_place(int ***v, int **b,
								dims A_dimension, dims B_dimension);
int condition(int index1, int index2, int last_index);
void sort_matrices(int ***v, dims *dimensions, int last_index);
void shift_left_from_index(int ****v, dims **dimensions,
						   int *last_index, int start_index);
