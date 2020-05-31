#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

//this function will check input matrix and do the parsing
void parse(string str_matrix, double matrix[][100])
{
	/* ****checking if the number of columns is identical in each row**** */
	/* ================================================================== */

	int columns_num = 0;
	int ref_col_num = 0;
	int i;
	//determining the reference for columns number
	for (i = 0; i <= str_matrix.length() - 1; i++)
	{
		if (str_matrix[i] == ' ')
			ref_col_num++;
		if (str_matrix[i] == ';')
			break;
	}
	i++; // shifting the pointer by 1 place (bec. i++ in the header of the for loop didn't execute in the last iteration because of the break line)

	//comparing number of columns in each row with the referece
	while (i < str_matrix.length() - 1)
	{
		int j;
		for (j = i; j <= str_matrix.length() - 1; j++)
		{
			if (str_matrix[j] == ' ')
				columns_num++;
			if (str_matrix[j] == ';')
				break;
		}
		if (columns_num != ref_col_num)
		{
			cout << "ERROR";
			exit(0);
		}
		j++; //shifting pointer by 1 to point to the letter after the ';'
		i = j; //to carry out the process from where it stopped
		columns_num = 0;
	}



	/* ***parsing the numbers into the matrix*** */
	/* ========================================= */

	int c = 0; //columns counter
	int r = 0; //rows counter

	string str_mtx_ele;
	double flt_mtx_ele;

	for (int k = 0; k <= str_matrix.length(); k++)
	{
		if (str_matrix[k] == '0' || //checking if we are pointing to a number
			str_matrix[k] == '1' ||
			str_matrix[k] == '2' ||
			str_matrix[k] == '3' ||
			str_matrix[k] == '4' ||
			str_matrix[k] == '5' ||
			str_matrix[k] == '6' ||
			str_matrix[k] == '7' ||
			str_matrix[k] == '8' ||
			str_matrix[k] == '9' ||
			str_matrix[k] == '-') //is this a point(.) or dash(-)? 
		{
			str_mtx_ele = str_matrix[k];
			//concatenating the rest of digits constructing the number to the str_mtx_ele variable
			while (str_matrix[k + 1] != ' ' && str_matrix[k + 1] != ';' && str_matrix[k + 1] != ']') //we could put the condition that they are numbers(form 0 --> 9) and check for the decimal point also '.'
			{
				str_mtx_ele = str_mtx_ele + str_matrix[k + 1];
				k++;
			}
			flt_mtx_ele = atof(str_mtx_ele.c_str());
			matrix[r][c] = flt_mtx_ele;
			c++;
		}
		if (str_matrix[k] == ';')
		{
			r++;
			c = 0;

		}
	}
}


//determining ROWS function
int det_rows(string str_matrix)
{
	//number of rows = number of ';' + 1
	int rows_num = 0;
	for (int i = 0; i <= str_matrix.length() - 1; i++)
		if (str_matrix[i] == ';')
			rows_num++;
	rows_num++;
	return rows_num;
}


//determining COLUMNS function
int det_col(string str_matrix)
{
	//number of columns = number of spaces + 1
	int columns_num = 0;
	for (int i = 0; i <= str_matrix.length() - 1; i++)
	{
		if (str_matrix[i] == ' ')
			columns_num++;
		//stop counting if ';' is encountered
		if (str_matrix[i] == ';')
			break;
	}
	columns_num++;
	return columns_num;
}



//adding function
void add(double matrix_1[][100], int rows_num_1, int col_num_1, double res_matrix[][100])
{
	string str_matrix_2;
	getline(cin, str_matrix_2);

	double matrix_2[100][100];

	parse(str_matrix_2, matrix_2);

	int rows_num_2 = det_rows(str_matrix_2);
	int col_num_2 = det_col(str_matrix_2);

	//checking if we can do the sum operation on the two matrices
	if ((rows_num_1 == rows_num_2) && (col_num_1 == col_num_2))
	{
		//adding code
		for (int i = 0; i <= rows_num_1 - 1; i++)
		{
			for (int j = 0; j <= col_num_1 - 1; j++)
			{
				res_matrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
			}
		}
	}
	else
	{
		cout << "ERROR";
		exit(0); //can't exit program with "return 0" from a function other than main()
	}
}



//subtracting function
void subtract(double matrix_1[][100], int rows_num_1, int col_num_1, double res_matrix[][100])
{
	string str_matrix_2;
	getline(cin, str_matrix_2);

	double matrix_2[100][100];

	parse(str_matrix_2, matrix_2);

	int rows_num_2 = det_rows(str_matrix_2);
	int col_num_2 = det_col(str_matrix_2);

	//checking if we can do the subtraction operation on the two matrices
	if ((rows_num_1 == rows_num_2) && (col_num_1 == col_num_2))
	{
		//subtraction code
		for (int i = 0; i <= rows_num_1 - 1; i++)
		{
			for (int j = 0; j <= col_num_1 - 1; j++)
			{
				res_matrix[i][j] = matrix_1[i][j] - matrix_2[i][j];
			}
		}
	}
	else
	{
		cout << "ERROR";
		exit(0);
	}
}


//multiplication function
void multiply(double matrix_1[][100], int rows_num_1, int col_num_1, double res_matrix[][100], int* mult_out_rows, int* mult_out_col)
{
	string str_matrix_2;
	getline(cin, str_matrix_2);

	double matrix_2[100][100] = { 0 };
	parse(str_matrix_2, matrix_2);

	int rows_num_2 = det_rows(str_matrix_2);
	int col_num_2 = det_col(str_matrix_2);

	//checking if we can do the multiplication operation on the two matrices
	if (col_num_1 == rows_num_2)
	{
		//multiplication code
		double sum;
		for (int k = 0; k <= rows_num_1 - 1; k++)
		{
			for (int j = 0; j <= col_num_2 - 1; j++)
			{
				sum = 0;
				for (int i = 0; i <= col_num_1 - 1; i++)
				{
					sum = sum + matrix_1[k][i] * matrix_2[i][j];
				}
				res_matrix[k][j] = sum;
			}
		}

		*mult_out_rows = rows_num_1;
		*mult_out_col = col_num_2;
	}
	else
	{
		cout << "ERROR";
		exit(0);
	}
}

//multiplication without cin function
void multiply_without_cin(double matrix_1[][100], int rows_num_1, int col_num_1, double matrix_2[][100], int rows_num_2, int col_num_2, double res_matrix[][100])
{
	//checking if we can do the multiplication operation on the two matrices
	if (col_num_1 == rows_num_2)
	{
		//multiplication code
		double sum;
		for (int k = 0; k <= rows_num_1 - 1; k++)
		{
			for (int j = 0; j <= col_num_2 - 1; j++)
			{
				sum = 0;
				for (int i = 0; i <= col_num_1 - 1; i++)
				{
					sum = sum + matrix_1[k][i] * matrix_2[i][j];
				}
				res_matrix[k][j] = sum;
			}
		}
	}
	else
	{
		cout << "ERROR: multiply without cin";
		exit(0);
	}
}

void equate(double matrix_1[][100], double matrix_2[][100])
{
	//the two matrices should be of equal number of rows and columns
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			matrix_1[i][j] = matrix_2[i][j];
		}
	}
}

void power(double matrix[][100], int num_of_rows, int num_of_col, double res_matrix[][100])
{
	float n;
	cin >> n;

	if ((int)n == n /*checking if the input is integer*/ && n > 0 && num_of_rows == num_of_col)
	{
		double temp_matrix[100][100] = { 0 };
		equate(temp_matrix, matrix);

		for (int i = 1; i <= n; i++)
		{
			if (i == 1) /*skipping the first iteration without multiplying*/
				equate(res_matrix, matrix);
			else
			{
				multiply_without_cin(temp_matrix, num_of_rows, num_of_col, matrix, num_of_rows, num_of_col, res_matrix);
				equate(temp_matrix, res_matrix);
			}
		}

	}
	else
	{
		cout << "ERROR";
		exit(0);
	}
}
//printing function
void print(double matrix[][100], int num_of_rows, int num_of_col)
{
	string output, s;
	ostringstream element;
	output = "[";
	for (int i = 0; i <= num_of_rows - 1; i++)
	{
		for (int j = 0; j <= num_of_col - 1; j++)
		{
			//changing the number to string
			element.str(""); /*to clear string stream*/
			element.clear(); /*don't know its function ???*/
			element << matrix[i][j];
			s = element.str();
			//concatenating numbers to output string
			output = output + s;

			if (j != num_of_col - 1)
				output = output + " ";
		}
		if (i != num_of_rows - 1)
			output = output + ";";
	}
	output = output + "]";
	cout << output;
}

void transpose(double matrix[][100], double res_matrix[][100])
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			res_matrix[i][j] = matrix[j][i];
		}
	}
}

//making the specified cell of a row equal zero by Gaussian elimination(row echelon form)
void make_zero(double matrix[][100], int base_row, int sec_row, int zero_index /*place where you want the zero to be*/)
{
	double initial_base_row_element = matrix[base_row][zero_index];
	double initial_sec_row_element = matrix[sec_row][zero_index];

	for (int i = 0; i < 100; i++)
	{
		matrix[base_row][i] -= matrix[sec_row][i] / initial_sec_row_element * initial_base_row_element;
	}
}

//applying Gaussian elimination on the matrix
void gaus_ele(double matrix[][100])
{
	for (int j = 0; j < 99 /*iterate to the row before the last */; j++)
	{
		for (int i = j + 1 /*start from (j+1)th row*/; i < 100; i++)
		{
			make_zero(matrix, i, j, j);
		}
	}
}

double determinent(double matrix[][100], int num_of_rows, int num_of_col)
{
	//checking that the matrix is a square matrix
	if (num_of_rows == num_of_col)
	{
		gaus_ele(matrix);

		//multiplying elements of main diagonal
		double product = 1;
		for (int i = 0; i < num_of_rows; i++)
		{
			product *= matrix[i][i];
		}
		return product;
	}
	else
	{
		cout << "ERROR";
		exit(0);
	}
}

//this function turns the specified row into identity row and make the cells corresponding to the 1 in the other rows equal to zero
void identity_row(double matrix[][200], int row_num, int num_of_rows, int num_of_col)
{
	double initial_divisor_val = matrix[row_num][row_num];
	for (int i = 0; i < 200; i++)
	{
		matrix[row_num][i] /= initial_divisor_val;
	}

	for (int j = 0; j < 100; j++)
	{
		if (j != row_num)
		{
			double initial_multiply_val = matrix[j][row_num];
			for (int i = 0; i < 200; i++)
			{
				matrix[j][i] -= matrix[row_num][i] * initial_multiply_val;
			}
		}
	}
}

void inverse(double matrix[][100], int num_of_rows, int num_of_columns)
{
	//checking if the input matrix is square matrix
	if (num_of_rows == num_of_columns)
	{
		double gauss_matrix[100][200] = { 0 };
		//filling the new matrix with input matrix
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				gauss_matrix[i][j] = matrix[i][j];
			}
		}
		//filling the other half with the identity matrix
		for (int i = 0; i < 100; i++)
		{
			gauss_matrix[i][i + 100] = 1;
		}

		//applying Gauss-Jordan method on gauss_matrix
		for (int i = 0; i < num_of_rows; i++)
		{
			identity_row(gauss_matrix, i, num_of_rows, num_of_columns);
		}

		//filling original matrix with second half of gauss_matrix
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				matrix[i][j] = gauss_matrix[i][j + 100];
			}
		}
	}
	else
	{
		cout << "ERROR";
		exit(0);
	}
}

void divide(double matrix_1[][100], int rows_num_1, int col_num_1, double res_matrix[][100], int& col_num_2)
{
	string str_matrix_2;
	getline(cin, str_matrix_2);

	double matrix_2[100][100] = { 0 };
	parse(str_matrix_2, matrix_2);

	int rows_num_2 = det_rows(str_matrix_2);
	col_num_2 = det_col(str_matrix_2);

	//change matrix_2 to inverse
	inverse(matrix_2, rows_num_2, col_num_2);

	//number of columns of second matrix should equal number of rows of first matrix
	if (col_num_1 == rows_num_2)
	{
		multiply_without_cin(matrix_1, rows_num_1, col_num_1, matrix_2, rows_num_2, col_num_2, res_matrix);
	}
	else
	{
		cout << "ERROR";
		exit(0);
	}
}

int main()
{
	//getting input
	string str_matrix_1;
	getline(cin, str_matrix_1);

	double matrix_1[100][100] = { 0 };
	parse(str_matrix_1, matrix_1);

	int rows_num_1 = det_rows(str_matrix_1);
	int col_num_1 = det_col(str_matrix_1);

	double res_matrix[100][100] = { 0 };

	//taking operator from user
	string op;
	getline(cin, op);

	if (op == "+")
	{
		add(matrix_1, rows_num_1, col_num_1, res_matrix);
		print(res_matrix, rows_num_1, col_num_1);
	}


	if (op == "-")
	{
		subtract(matrix_1, rows_num_1, col_num_1, res_matrix);
		print(res_matrix, rows_num_1, col_num_1);
	}


	if (op == "*")
	{
		int mult_out_rows = 0;
		int mult_out_col = 0;
		multiply(matrix_1, rows_num_1, col_num_1, res_matrix, &mult_out_rows, &mult_out_col);
		print(res_matrix, mult_out_rows, mult_out_col);
	}

	if (op == "^")
	{
		power(matrix_1, rows_num_1, col_num_1, res_matrix);
		print(res_matrix, rows_num_1, col_num_1);
	}

	if (op == "T")
	{
		transpose(matrix_1, res_matrix);
		print(res_matrix, col_num_1, rows_num_1); //inverted the columns with the rows
	}

	if (op == "D")
	{
		double det = determinent(matrix_1, rows_num_1, col_num_1);
		cout << det;
	}

	if (op == "I")
	{
		inverse(matrix_1, rows_num_1, col_num_1);
		print(matrix_1, rows_num_1, col_num_1);
	}

	if (op == "/")
	{
		int col_num_2 = 0;
		divide(matrix_1, rows_num_1, col_num_1, res_matrix, col_num_2);
		print(res_matrix, rows_num_1, col_num_2);
	}

	return 0;
}














