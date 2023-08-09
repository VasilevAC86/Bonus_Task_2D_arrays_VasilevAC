# include <iostream>
#include<cstdlib>
#include<ctime>
#include<string>

void element_Aligment(int element, int max_Length) { // Функция выравнивания текущего элемента в ячейке таблицы
	short number = std::to_string(element).length(); // Объявляем и инициализируем локальную переменную для кол-ва символов текущей записи
	short m = max_Length - number; // Объявляем и инициализируем локальную переменную для выравнивания номеров столбцов в ячейках таблицы
	for (short k = 0; k < m / 2; k++) // Цикл записи пробелов до элемента
		std::cout << ' ';
	std::cout << element; // Вывод элемента
	for (short k = m / 2 + 1; k < m; k++) // Цикл записи пробелов после элемента
		std::cout << ' ';
	std::cout << '|';
}

int main() {

	// Задача 1. Среднее арифметическое каждого из столбцов массива 10х10
	std::cout << "\033[31mTask 1. Arifmetic mean of each matrix column\033[0m\n\n";
	short const rows1 = 10, cols1 = 10;
	int matrix[rows1][cols1]{};
	int A, B; // Переменные для хранения значений начала и конца диапазона
	short max_Element, max_Header, max_Length; /* Переменные для хранения значения максимально возможных длины элемента матрицы, длины заголовка таблицы,
												длины ячейки таблицы в кол-ве символов*/
	std::cout << "Enter a range of array element values:\nRange start = ";
	std::cin >> A; // Начало диапазона
	std::cout << "End of range = ";
	std::cin >> B; // Конец диапазона
	while (B < A) { // Цикл проверки диапазона
		std::cout << "Input error! The end of the range cannot be less than the start\nEnter a range of array element values:\nRange start = ";
		std::cin >> A;
		std::cout << "End of range = ";
		std::cin >> B;
	}
	// Определяем максимально возможную длину элемента массива	
	max_Element = std::to_string(A).length() > std::to_string(B).length() ? std::to_string(A).length() : std::to_string(B).length();
	// Определяем максимально возможную длину заголовка столбца (-1 в формуле убирает подсчёт символа конца строки "Col N  |")
	max_Header = std::size("Col N  |") - 1 + std::to_string(cols1 - 1).length();
	srand(time(NULL));
	max_Length = max_Element > max_Header ? max_Element : max_Header; // Определяем максамально возможную длину ячейки таблицы
	std::cout << "\n\033[32mTable with source matrix:\033[0m\n\n";
	for (short i = 0; i <= rows1; i++) {
		if (i) { // Вывод матрицы в ячейки таблицы
			for (short j = 0; j < cols1; j++) {
				matrix[i - 1][j] = rand() % (B - A + 1) + A;
				element_Aligment(matrix[i - 1][j], max_Length);
			}
			std::cout << std::endl;
		}
		else { // Вывод заголовков столбцов
			for (short j = 0; j < cols1; j++) {
				// Определяем кол-во символов в текущем заголовке столбца (-1 убирает подсчёт символа конца строки "Col N ")
				max_Header = std::size("Col N ") - 1 + std::to_string(j).length();
				std::cout << " Col N " << j;
				// Цикл выравнивания ячейки таблицы по параметру max_Length (-2 учитывает пробел перед элементом массива и символ | в конце ячейки)
				for (short k = 0; k < (max_Length - max_Header - 2); k++)
					std::cout << ' ';
				std::cout << '|';
			}
			std::cout << std::endl;
		}
	}
	std::cout << "\n\033[32mArifmetic mean of each matrix column:\033[0m\n\n";
	for (short i = 0; i < 2; i++) {
		for (int j = 0; j <= cols1; j++) {
			if (i) { // Вывод строки "1" таблицы
				switch (j) {
				case 0: // Вывод столбца "0" строки "1" таблицы
					std::cout << " Result ";
					max_Header = std::size(" Result ") - 1; // Определяем кол-во символов в строке " Result " (-1 убирает подсчёт символа конца строки)
					// Цикл выравнивания ячейки таблицы по параметру max_Length (-1 учитывает символ | в конце ячейки)
					for (short k = 0; k < max_Length - max_Header - 1; k++)
						std::cout << ' ';
					std::cout << '|';
					break;
				default: // Вывод столбцов от "1" до "cols" строки "1" таблицы
					int sum = 0; // Объявляем и инициализируем переменную для хранения суммы элементов столбца матрицы
					for (short k = 0; k < rows1; k++) // Цикл расчёта суммы элементов столбца j - 1 матрицы
						sum += matrix[k][j - 1];
					// Объявляем и инициализируем текстовую строку my_Text, в которой будем хранить среднеарифметическое значение суммы элементов столбца j-1
					std::string my_Text = std::to_string(sum / double(rows1));
					short m = std::size(my_Text); // Объявляем и инициализируем переменную для хранения кол-ва символов среднеарифметического значения													
					while (m >= max_Length) { // Пока значение среднего арифметического не влазит в ячейку таблицы
						my_Text.pop_back(); // удаляем последний символ строки my_Text
						m = std::size(my_Text); // Пересчитываем длину строки my_Text
					}
					std::cout << my_Text << '|'; // Выводим значение среднеарифметического в таблицу
				}
			}
			else { // Вывод строки "0" таблицы
				switch (j) {
				case 0: // Вывод столбца "0" строки "0" таблицы
					std::cout << " Col N ";
					max_Header = std::size(" Col N ") - 1; // Определяем кол-во символов в строке " Col N " (-1 убирает подсчёт символа конца строки)
					// Цикл выравнивания ячейки таблицы по параметру max_Length (-1 учитывает символ '|' в конце ячейки)
					for (short k = 0; k < max_Length - max_Header - 1; k++)
						std::cout << ' ';
					std::cout << '|';
					break;
				default: // Вывод столбцов от "1" до "cols" строки "0" таблицы					
					element_Aligment(j - 1, max_Length);
				}
			}
		}
		std::cout << std::endl;
	}

	// Задача 2. Матрица в шахматном порядке
	std::cout << "\n\n\033[31mTask 2. Checkerboard Matrix\033[0m\n\n";
	const short rows2 = 10, cols2 = 10;
	// Вариант решения 1 (через матрицу):
	short matrix_Chess[rows2][cols2]{}; // Объявляем и инициализируем матрицу	
	for (short i = 0; i < rows2; i++) { // Цикл заполнения матрицы
		if (i % 2) // Заполнение нечётных строк матрицы
			for (short j = 0; j < cols2; j++)
				if (j % 2) // Если столбец нечётный, то
					matrix_Chess[i][j] = 1; // элемент равен 1
				else // Если столбец чётный, то
					matrix_Chess[i][j] = 0; // элемент равен 0
		else
			for (short j = 0; j < cols2; j++)
				if (j % 2)
					matrix_Chess[i][j] = 0;
				else
					matrix_Chess[i][j] = 1;
	}
	for (short i = 0; i < rows2; i++) {
		for (short j = 0; j < cols2; j++)
			std::cout << matrix_Chess[i][j] << '\t';
		std::cout << std::endl;
	}
	
	// Вариант решения 2 (через одномерный массив):
	/*short array[rows2 * cols2]{}; // Объявляем и инициализируем одномерный массив
	for (short i = 0; i < rows2 * cols2; i++) // Цикл заполнения массива 0 и 1
		if (i % 2) // Если координата элемента чётная, то
			array[i] = 0; // элемент равен 0
		else // Если координата элемента нечётная, то
			array[i] = 1; // элемент равен 1
	for (short i = 0; i < rows2; i++) { // Цикл вывода одномерного массива в виде матрицы
		for (short j = 0; j < cols2; j++)
			std::cout << array[i + j] << '\t';
		std::cout << std::endl;
	}*/
	
	// Задача 3. Расчёт второго столбца матрицы
	std::cout << "\n\n\033[31mTask 3. Calculation of the second column of the matrix\033[0m\n\n";
	const short rows3 = 10, cols3 = 2;
	int matrix_Calculation[rows3][cols3]{};
	for (short i = 0; i < rows3; i++) // Вложенный цикл формирования матрицы
		for (short j = 0; j < cols3; j++) {
			if (j == 0) {
				std::cout << "Enter matrix elemnt with coordinates [" << i << " ; " << j << " ] = ";
				std::cin >> matrix_Calculation[i][j];
			}
			else
				matrix_Calculation[i][j] = matrix_Calculation[i][j - 1] * i;
		}
	std::cout << "\n\033[32mFinal matrix:\033[0m\n\n";
	for (short i = 0; i < rows3; i++) { // Цикл вывода матрицы 
		for (short j = 0; j < cols3; j++) {
			if (j == 0)
				std::cout << "{ " << matrix_Calculation[i][j] << "\t;";
			else
				std::cout << "  " << matrix_Calculation[i][j] << "\t}";
		}
		std::cout << std::endl;		
	}

	// Задача 4. Матрица змейка
	std::cout << "\n\n\033[31mTask 4. The snake matrix\033[0m\n\n";
	const short size = 5; // Объявляем и инициализируем размер квадратной матрицы
	short Snake[size][size]; // Объявляем квадратную 2D-матрицу

	// Вариан решения N 1 (организация цикла по кол-ву полных оборотов змейки)
	/*short round = 0, remains = size, counter = 0, row = 0, col = 0; // Кол-во оборотов, остаток от целых оборотов, счётчик номеров матрицы, начальные строка и столбец матрицы
	do { // Цикл расчёта кол-ва оборотов змейки по часовой стрелке
		remains -= 2; // Число "2" - уменьшение размера матрицы после полного оборота змей по часовой стрелке
		round++;
	} while (remains >= 2);
	for (short k = 0; k < round; k++) { // Цикл заполнения матрицы по полным оборотам по часовой стрелке
		for (; col < size - k; col++) { // Цикл заполнения матрицы по верхним строкам (горизонталям)
			Snake[row][col] = counter;
			counter++;
		}
		col--; 
		for (row = k + 1; row < size - k; row++) { // Цикл заполнения матрицы по правым столбцам (вертикалям)
			Snake[row][col] = counter;
			counter++;
		}
		row--; 
		for (col--; col >= k; col--) { // Цикл заполнения матрицы по нижним строкам (горизонталям)			
			Snake[row][col] = counter;
			counter++;
		}
		col++; 
		for (row--; row > k; row--) { // Цикл заполнения матрицы по левым столбцам (вертикалям)
			Snake[row][col] = counter;
			counter++;
		}
		// После каждого оборота надо змейку переставить на новую начальную точку для следующего оборота (+1 к строке и +1 к столбцу)
		row++;
		col++;
	}
	// Если размер матрицы нечётный, то надо заполнить элемент матрицы на пересечений главной и побочных диагоналей последним counter
	if (size % 2)
		Snake[size / 2][size / 2] = counter;
	for (short i = 0; i < size; i++) {
		for (short j = 0; j < size; j++)
			std::cout << Snake[i][j] << '\t';
		std::cout << std::endl;
	}*/

	// Вариант решения N 2 (кол-во несъеденных змейкой элементов массива)
	short total = size * size; // Кол-во элементов матрицы всего
	short eaten = 0, counter_Round = 0; // Кол-во заполненных элементов матрицы (съеденных змейкой) и текущее кол-во кругов змейки 
	short row_S = 0, col_S = 0; // Начальная координата змейки
	do { // Цикл заполнения матрицы змейкой по часовой стрелке
		for (; col_S < size - counter_Round; col_S++) { // Цикл заполнения матрицы по верхним строкам (горизонталям)
			Snake[row_S][col_S] = eaten;
			eaten++;
		}
		col_S--; 
		for (row_S = counter_Round + 1; row_S < size - counter_Round; row_S++) { // Цикл заполнения матрицы по правым столбцам (вертикалям)
			Snake[row_S][col_S] = eaten;
			eaten++;
		}
		row_S--;
		for (col_S--; col_S >= counter_Round; col_S--) { // Цикл заполнения матрицы по нижним строкам (горизонталям)			
			Snake[row_S][col_S] = eaten;
			eaten++;
		}
		col_S++;
		for (row_S--; row_S > counter_Round; row_S--) { // Цикл заполнения матрицы по левым столбцам (вертикалям)
			Snake[row_S][col_S] = eaten;
			eaten++;
		}
		counter_Round++; // Переход змейки на новый круг
		row_S++; // Изменение координаты строки для нового круга змейки
		col_S++; // Изменение координаты столбца для нового круга змейки	 
	} while (eaten < total); // Пока все элементы матрицы не заполнены (не съедены змейкой), выполняется цикл
	for (short i = 0; i < size; i++) { // Цикл вывода матрицы 
		for (short j = 0; j < size; j++)
			std::cout << Snake[i][j] << '\t';
		std::cout << std::endl;
	}

	return 0;
}