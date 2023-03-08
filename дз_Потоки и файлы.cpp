// дз_Потоки и файлы.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

/*
	Задача 1: Дан текстовый файл. Необходимо создать новый файл, в который 
	переписать из исходного файла все слова, состоящие не менее чем из семи 
	букв.
	Задача 2: Дан текстовый файл. Необходимо переписать его строки в другой
	файл. Порядок строк во втором файле должен совпадать с порядком строк в 
	заданном файле.
	Задача 3: Создать и инициализировать массив из 4-х объектов типа Дробь 
	(Fraction) и записать этот массив в файл в бинарном режиме.
	Затем создать другой массив из 4-х объектов типа Дробь и считать в этот 
	массив объекты из этого файла.
	Задача 4: Создать и инициализировать массив из 4-х объектов типа Дробь 
	(Fraction) и записать этот массив в файл в бинарном режиме.
	Затем создать объект типа Дробь и считать из этого файла в этот объект 
	данные предпоследнего объекта массива. Использовать позиционирование по 
	файлу.
*/

// Задача 1
int main1()
{
	// создаем исходный файл для записи слов
	std::ofstream file("File_with_words.txt");
	// проверка на возможность открытия файла
	if (!file)
	{
		std::cerr << "File_with_words.txt couldn't be opened for writing!"
			<< std::endl;
		exit(-1);
	}
	// записываем в файл данные
	file << "I wish you happy holidays, dear!" << std::endl;

	file.close();  // закрываем файл, чтобы открыть для чтения

	// чтение из файла
	std::ifstream file1("File_with_words.txt");
	// проверка на возможность открытия файла
	if (!file1)
	{
		std::cerr << "File_with_words.txt couldn't be opened for reading!"
			<< std::endl;
		exit(-1);
	}

	// создаем второй файл для записи результатов
	std::ofstream file2("File_with_words_result.txt");
	// проверка на возможность открытия файла
	if (!file2)  
	{
		std::cerr << "File_with_words_result.txt couldn't be opened for writing!"
			<< std::endl;
		exit(-1);
	}

	while (file1)  // пока есть информация для чтения
	{
		std::string str;  // создаем объект типа string
		file1 >> str;     // считываем данные из исходного файла
		if (size(str) >= 7)  // если строка >= 7 символов
		{
			// проверка, если из этих 7 символов последний - точка или
			// запятая
			if (str[str.length() - 1] == '.' ||
				str[str.length() - 1] == ',')
			{
				// тогда удаляем эту точку или запятую
				str.erase(str.length() - 1, 1);
			}
			// записываем результат во второй файл
			file2 << str << std::endl;
		}
	}
	return 0;
}

// Задача 2
int main2()
{
	// создаем исходный файл для записи строк
	std::ofstream file("File_with_strings.txt");
	// проверка на возможность открытия файла
	if (!file)
	{
		std::cerr << "File_with_strings.txt couldn't be opened for writing!"
			<< std::endl;
		exit(-1);
	}
	// запись строк в файл:
	file << "I wish you happy holidays, dear!" << std::endl;
	file << "Happy New Year!" << std::endl;
	file << "Happy Christmas!" << std::endl;
	
	// // чтение из файла
	std::ifstream file1("File_with_strings.txt");
	// проверка на возможность открытия файла
	if (!file1)
	{
		std::cerr << "File_with_strings.txt couldn't be opened for reading!"
			<< std::endl;
		exit(-1);
	}

	// создаем файл для записи результата
	std::ofstream file2("File_with_strings_result.txt");
	// проверка на возможность открытия файла
	if (!file2) 
	{
		std::cerr << "File_with_strings_result.txt couldn't be opened for writing!"
			<< std::endl;
		exit(-1);
	}

	while (file1)  // пока есть информация для чтения
	{
		std::string str;  // создаем объект типа string
		getline(file1, str);  // перемещаем данные в строку из объекта file1
		file2 << str << std::endl;  // записываем строки в file2
	}

	return 0;
}

// Задача 3 и 4
class Fraction  // класс Дробь
{
	int num;    // числитель
	int denom;  // знаменатель
public:
	Fraction() : num{0}, denom{0} {}
	void SetFraction()   // метод для утсановки значений
	{
		std::cout << "Enter num and denom: ";
		std::cin >> num >> denom;
	}
	void ShowFraction()  // метод для вывода на экран
	{
		std::cout << "|||" << num << '/' << denom << "|||" << std::endl;
	}
};
int main()
{
	// создание объекта ofstream и запись в бинарном режиме
	std::ofstream file("Fraction.dat", std::ios::binary);

	const int SIZE = 4;  // константа для размера массива
	Fraction fract1[SIZE];  // создаем массив объектов типа Дробь
	for (size_t i = 0; i < SIZE; i++)  // инициализируем массив объектами
	{
		fract1[i].SetFraction();
	}
	std::cout << "Fractions array1:\n";
	for (size_t i = 0; i < SIZE; i++)  // выводим массив объектов на экран
	{
		fract1[i].ShowFraction();
	}
	
	// записываем массив объектов в объект ofstream
	file.write((char*)&fract1, sizeof(fract1));
	// закрываем файл перед тем, как открыть для чтения
	file.close();

	// чтение в бинарном режиме
	std::ifstream file1("Fraction.dat", std::ios::binary);

	Fraction fract2[SIZE];  // создаем новый массив объектов типа Дробь
	// чтение из файла (объекта ifstream) в новый массив
	file1.read((char*)&fract2, sizeof(fract2));

	std::cout << "Fractions array2:\n";
	for (size_t i = 0; i < SIZE; i++)  // вывод объектов Дробь на экран
	{
		fract1[i].ShowFraction();
	}
	
	// к задаче 4:
	Fraction fract3;  // cоздание объекта типа Дробь (не массив)
	// находим позицию, с которой начинаем считывать данные (перед нужной нам
	// предпоследней)
	int position = (SIZE - 2) * sizeof(fract1[0]);  
	// перемещаем файловый указаетль перед нужной позицией
	file1.seekg(position, std::ios::beg);
	// считываем данные
	file1.read((char*)&fract3, sizeof(fract3));

	std::cout << "Fractions object[2]:\n";
	fract3.ShowFraction();

	return 0;
}