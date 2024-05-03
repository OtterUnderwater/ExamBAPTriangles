#define _CRT_SECURE_NO_WARNINGS //Библиотека нужна чтобы не писать fscanf_s -> fscanf
#include <stdio.h> //Основная библиотека для си
#include <math.h> //Матем. операции
#include <malloc.h> //Массивы
#include <string.h> //Работа со строками
#include <locale.h> //Для русского языка

struct treygolnic
{
	float x1, x2, x3, y1, y2, y3;
	int status;
};
typedef struct treygolnic T; //Краткое имя

float Cosinus(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float ax, ay, bx, by, cos;
	//два вектора
	ax = x2 - x1; ay = y2 - y1;
	bx = x3 - x1; by = y3 - y1;
	//поиск угла между ними
	cos = (ax * bx + ay * by) / (sqrt(pow(ax, 2) + pow(ay, 2)) * sqrt(pow(bx, 2) + pow(by, 2)));
	return cos;
}

int main()
{
	//Русский язык в зависимости от версий
	//setlocale(LC_ALL, ".1251"); //Windows 7+
	system("chcp 1251>nul"); //Windows 10+
	int proverka = 0, numT = 0, count = -1, n = 0, probels = 0, k = 0;
	float ABx, ABy, AСx, AСy, BCx, BCy, AB, BC, AC, S, P, cos1, cos2, cos3;
	int* num = calloc(0, sizeof(int)); //массив, записывающий номера правильных строк
	FILE* file = fopen("examen.txt", "r");
	while (!feof(file)) //проверяеем строки
	{
		char* str = calloc(50, sizeof(char));
		fgets(str, 50, file); //считываем из файла
		proverka = 0; //обнуляем проверку адекватности строк
		count++; //счетчик строк
		//цикл на проверку символов строки
		for (int i = 0; i < strlen(str) - 1; i++) //strlen(str) cчитает вместе с \n
		{
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ' || str[i] == '-' || str[i] == ',' || str[i] == '.')
			{
				proverka = 1; //все нормально
				if (str[i] == ' ')
				{
					probels++; //подсчет пробелов в строке (должно быть 5)
				}
			}
			else
			{
				proverka = 0;
				probels = 0;
				break;
			}
		}
		if (proverka == 1 && probels == 5) //записываем номер строки в массив
		{
			n++; //счетчик элементов массива
			num = realloc(num, n * sizeof(int));
			num[n - 1] = count; // n-1 = 0
		}
		probels = 0;
		free(str); //очищаем буфер
	}
	fclose(file);
	T* array = calloc(n, sizeof(T)); //выделяем память под структуру правильных треугольников
	printf("Номера правильных строк: ");
	for (int p = 0; p < n; p++) { printf("%d ", num[p] + 1); }
	printf("\n");
	file = fopen("examen.txt", "r");
	FILE* file2 = fopen("rezult.txt", "w"); //Проверка треугольников и запись в новый файл
	for (int s = 0; s < count; s++)
	{
		if (num[k] == s) //номер строки равен номеру строки правильного треугольника -1, так как счет с нуля
		{
			fscanf(file, "%f %f %f %f %f %f\n", &array[num[k]].x1, &array[num[k]].y1, &array[num[k]].x2, &array[num[k]].y2, &array[num[k]].x3, &array[num[k]].y3); //считываем из файла в структуру																																	   //Вектора треугольника
			ABx = array[num[k]].x2 - array[num[k]].x1;
			ABy = array[num[k]].y2 - array[num[k]].y1;
			AСx = array[num[k]].x3 - array[num[k]].x1;
			AСy = array[num[k]].y3 - array[num[k]].y1;
			BCx = array[num[k]].x3 - array[num[k]].x2;
			BCy = array[num[k]].y3 - array[num[k]].y2;
			//Площадь треугольника
			S = abs(((ABx * AСy) - (AСx * ABy)) / 2);
			if (S != 0)
			{
				array[num[k]].status = 1;
				//Длина сторон
				AB = sqrt(abs(pow(ABx, 2) + pow(ABy, 2)));
				AC = sqrt(abs(pow(AСx, 2) + pow(AСy, 2)));
				BC = sqrt(abs(pow(BCx, 2) + pow(BCy, 2)));
				//Периметр
				P = AB + BC + AC;
				//Тип треугольника
				cos1 = Cosinus(array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3); // первые две точки - те, чей угол мы ищем
				cos2 = Cosinus(array[num[k]].x2, array[num[k]].y2, array[num[k]].x1, array[num[k]].y1, array[num[k]].x3, array[num[k]].y3);
				cos3 = Cosinus(array[num[k]].x3, array[num[k]].y3, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2);
				//Выводим на консоль и в файл
				printf("Треугольник %d: %.2f %.2f %.2f %.2f %.2f %.2f\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3);
				fprintf(file2, "%d: %.2f %.2f %.2f %.2f %.2f %.2f - %d\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3, array[num[k]].status);
				if (cos1 == 0 || cos2 == 0 || cos3 == 0)
				{
					printf("Тип: Прямоугольный\n");
					fprintf(file2, "\tПрямоугольный\n");
				}
				else if (cos1 < 0 || cos2 < 0 || cos3 < 0)
				{
					printf("Тип: Тупоугольный\n");
					fprintf(file2, "\tТупоугольный\n");
				}
				else if (cos1 > 0 || cos2 > 0 || cos3 > 0)
				{
					printf("Тип: Остроугольный\n");
					fprintf(file2, "\tОстроугольный\n");
				}
				printf("Длина сторон: %.2f %.2f %.2f\nS = %.2f P = %.2f\n\n", AB, BC, AC, S, P);
				fprintf(file2, "\tAB = %.2f BC = %.2f AC = %.2f\n\tS = %.2f P = %.2f\n", AB, BC, AC, S, P);
			}
			else
			{
				array[num[k]].status = 0;
				fprintf(file2, "%d: %.2f %.2f %.2f %.2f %.2f %.2f - %d\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3, array[num[k]].status);
				printf("Треугольник %d: %.2f %.2f %.2f %.2f %.2f %.2f\nТочки лежат на одной прямой\n\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3);
			}
			k++;
		}
		else
		{
			char* buffer = calloc(50, sizeof(char));
			fgets(buffer, 50, file); //считываем строку из файла
			free(buffer);
		}
	}
	fclose(file);
	fclose(file2);
	return 0;
}
