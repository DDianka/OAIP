#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const int SIZE_CHAR = 20;
const int RESERVE_SIZE = 100;
const string FILE_OF_DATA = "MyFile.txt"; //Путь к файлу

struct Student
{
	char name[SIZE_CHAR];
	char surname[SIZE_CHAR];
	int groupNum;
	char address[SIZE_CHAR];
	double raiting;
};
// Запись в файл (если что-то было в файле, то исходные данные будут удалены):
void writeFileStudents(Student* arr_of_students, int number_of_students);
// Добавление в конец файла одной строки:
void writeEndFileStudents(Student new_student);
// Чтение из файла в массив:
void readFileStudents(Student* arr_of_students, int& number_of_students);
// Определение количества структур в файле (при необходимости)
int getCountOfStucturesInFile(string file_path);
// Добавление студента в массив
void addStudentInArray(Student* arr_of_students, int& number_of_students);
// Линейный поиск
void linearSearch(Student* arr_of_students, int& number_of_students);
// Пузырьковая сортировка
void bubbleSort(Student* arr_of_students, int& number_of_students);
// Быстрая сортировка
void quickSort(Student* arr_of_students, int size);
// Бинарный поиск
int binarySearch(Student* arr_of_students, int l, int r, char searchString[]);
// Вывод бинарного поиска
void getBinarySearchResult(Student* arr_of_students, int& number_of_students);
// Вывод содержимого массива на экран
void showStudentArray(Student* arr_of_students, int number_of_students);

void main()
{
	setlocale(LC_ALL, "rus");
	Student arr_of_students[RESERVE_SIZE];
	int number_of_students = 0;

	bool canContinue = true;
	int actionCode;

	readFileStudents(arr_of_students, number_of_students);

	while (canContinue)
	{
		cout <<
			"1. add user" << endl <<
			"2. show users" << endl <<
			"3. linear search (by name)" << endl <<
			"4. bubble sort (by surname)" << endl <<
			"5. quick sort (by surname)" << endl <<
			"6. binary search (by name)" << endl;
		cin >> actionCode;

		switch (actionCode)
		{
		case 1:
		{
			addStudentInArray(arr_of_students, number_of_students);
			break;
		}
		case 2:
		{
			showStudentArray(arr_of_students, number_of_students);
			break;
		}
		case 3:
		{
			linearSearch(arr_of_students, number_of_students);
			break;
		}
		case 4:
		{
			bubbleSort(arr_of_students, number_of_students);
			showStudentArray(arr_of_students, number_of_students);
			break;
		}
		case 5:
		{
			quickSort(arr_of_students, number_of_students);
			showStudentArray(arr_of_students, number_of_students);
			break;
		}
		case 6:
		{
			quickSort(arr_of_students, number_of_students); // binary search requires array to be sorted, so we sort it firstly
			getBinarySearchResult(arr_of_students, number_of_students);
			break;
		}
		default:
		{
			cout << "Wrong input: " << actionCode << ". Try again entering number between 1 and 6." << endl;
			break;
		}
		}
	}

	addStudentInArray(arr_of_students, number_of_students);

	readFileStudents(arr_of_students, number_of_students);
	showStudentArray(arr_of_students, number_of_students);
}

void linearSearch(Student* arr_of_students, int& number_of_students) {
	char searchString[SIZE_CHAR];

	cout << "\tВведите фамилию студента: ";
	cin >> searchString;

	for (int i = 0; i <= number_of_students; i++) {
		if (strcmp(arr_of_students[i].surname, searchString) == 0) {
			cout << "\tФамилия: " << arr_of_students[i].surname << endl 
				 << "\tИмя: " << arr_of_students[i].name << endl
				 << "\tНомер группы: "<< arr_of_students[i].groupNum << endl
				 << "\tАдрес: "<<  arr_of_students[i].address << endl;
			return;
		}
	}

	cout << "Cтудента с таким именем не существует" << endl;
}

int binarySearch(Student* arr_of_students, int l, int r, char searchString[])
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle 
		// itself 
		if (strcmp(arr_of_students[mid].surname, searchString) == 0) {
			cout << "mid" << mid << endl;
			return mid;
		}
		// If element is smaller than mid, then 
		// it can only be present in left subarray 
		if (strcmp(arr_of_students[mid].surname, searchString) > 0)
			return binarySearch(arr_of_students, l, mid - 1, searchString);

		// Else the element can only be present 
		// in right subarray 
		return binarySearch(arr_of_students, mid + 1, r, searchString);
	}

	// We reach here when element is not 
	// present in array 
	return -1;
}

void getBinarySearchResult(Student* arr_of_students, int& number_of_students) {
	char searchString[SIZE_CHAR];

	cout << "\tВведите фамилию студента: ";
	cin >> searchString;
	int searchIndex = binarySearch(arr_of_students, 0, number_of_students, searchString);

	if (searchIndex == -1) {
		cout << "\tCтудента с таким именем не существует";
	}
	else {
		cout << "\tФамилия: " << arr_of_students[searchIndex].surname << endl
			<< "\tИмя: " << arr_of_students[searchIndex].name << endl
			<< "\tНомер группы: " << arr_of_students[searchIndex].groupNum << endl
			<< "\tАдрес: " << arr_of_students[searchIndex].address << endl;
	}
}


void bubbleSort(Student* arr_of_students, int& number_of_students) {
	Student temp;
	for (int i = 0; i < number_of_students - 1; i++) {
		for (int j = 0; j < number_of_students - 1; j++) {
			if (arr_of_students[i].surname > arr_of_students[j].surname) {
				// Переставляем элементы
				temp = arr_of_students[i];
				arr_of_students[i] = arr_of_students[j];
				arr_of_students[j] = temp;
			}
		}
	}
}

void quickSort(Student* arr_of_students, int size)
{
	int i = 0, j = size - 1;
	string mid = arr_of_students[size / 2].surname;
	do {
		for (int k = 0; arr_of_students[size / 2].surname[k] && arr_of_students[i].surname[k]; k++) {
			if (arr_of_students[i].surname == mid) {
				break;
			}
			while (arr_of_students[i].surname[k] < mid[k]) {
				i++;
			}
			while (arr_of_students[j].surname[k] > mid[k]) {
				j--;
			}
			break;
		}
		if (i <= j) {
			Student temp = arr_of_students[i];
			arr_of_students[i] = arr_of_students[j];
			arr_of_students[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (j > 0) {
		quickSort(arr_of_students, j + 1);
	}
	if (i < size) {
		quickSort(&arr_of_students[i], size - i);
	}
}

void addStudentInArray(Student* arr_of_students, int& number_of_students)
{
	//добавление студента, если не происходит выход за пределы массива
	if (number_of_students + 1 <= RESERVE_SIZE)
	{
		number_of_students++;
		cout << "\tВведите  фамилию студента: ";
		cin >> arr_of_students[number_of_students - 1].surname;
		cout << "\tВведите имя студента: ";
		cin >> arr_of_students[number_of_students - 1].name;
		cout << "\tВведите номер группы студента: ";
		cin >> arr_of_students[number_of_students - 1].groupNum;
		cout << "\tВведите адрес студента: ";
		cin >> arr_of_students[number_of_students - 1].address;
		writeEndFileStudents(arr_of_students[number_of_students - 1]);
	}
	else cout << "\tНедостаточно памяти для добавления нового элемента!" << endl;
}

void showStudentArray(Student* arr_of_students, int number_of_students)
{
	for (int i = 0; i < number_of_students; i++)
		cout <<"\t" << arr_of_students[i].surname << " "
		<< arr_of_students[i].name << " "
		<< arr_of_students[i].groupNum << " "
		<< arr_of_students[i].address << endl;
}
void writeFileStudents(Student* arr_of_students, int number_of_students)
{
	//Открываем файл для записи:
	ofstream fout(FILE_OF_DATA, ios::binary | ios::out);
	fout.write((char*)& arr_of_students[0],
		sizeof(Student) * number_of_students);
	fout.close();
}
void writeEndFileStudents(Student new_student)
{
	//Открываем файл для дозаписи:
	ofstream fadd(FILE_OF_DATA, ios::binary | ios::app);
	fadd.write((char*)& new_student, sizeof(new_student)); //Записали
	fadd.close();
}
void readFileStudents(Student* arr_of_students, int& number_of_students)
{
	ifstream fin(FILE_OF_DATA, ios::binary | ios::in);
	if (!fin.is_open()) cout << "Указанный файл не существует!" << endl;
	else
	{
		// определяем количество строк в файле
		int sizeOfFileWithStudents =
			getCountOfStucturesInFile(FILE_OF_DATA);
		/* если выделенная память под статический массив вмещает все
		строчки в файле */
		if (sizeOfFileWithStudents <= RESERVE_SIZE)
		{
			// будем считывать все строчки
			number_of_students = sizeOfFileWithStudents;
		}
		else
		{
			// иначе считаем ровно столько, насколько хватает места в массиве
			number_of_students = RESERVE_SIZE;
			cout << "There is not enough memory for read all data!" <<
				endl;
		}
		/* читаем сразу number_of_students-строчек из файла и
		сохраняем их в массиве */
		fin.read((char*)& arr_of_students[0],
			sizeof(Student) * number_of_students);
	}
	fin.close();
}
int getCountOfStucturesInFile(string file_path)
{
	//Открываем файл и перемещаем указатель в конец файла
	ifstream file(FILE_OF_DATA, ios::ate | ios::binary);
	/*file.tellg() возвращает значение типа int, которое показывает,
	сколько указателем пройдено в байтах от начала файла до текущей
	позиции */
	int number_of_strings = file.tellg() / sizeof(Student);
	file.close();
	return number_of_strings;
}
