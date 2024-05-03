#define _CRT_SECURE_NO_WARNINGS //���������� ����� ����� �� ������ fscanf_s -> fscanf
#include <stdio.h> //�������� ���������� ��� ��
#include <math.h> //�����. ��������
#include <malloc.h> //�������
#include <string.h> //������ �� ��������
#include <locale.h> //��� �������� �����

struct treygolnic
{
	float x1, x2, x3, y1, y2, y3;
	int status;
};
typedef struct treygolnic T; //������� ���

float Cosinus(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float ax, ay, bx, by, cos;
	//��� �������
	ax = x2 - x1; ay = y2 - y1;
	bx = x3 - x1; by = y3 - y1;
	//����� ���� ����� ����
	cos = (ax * bx + ay * by) / (sqrt(pow(ax, 2) + pow(ay, 2)) * sqrt(pow(bx, 2) + pow(by, 2)));
	return cos;
}

int main()
{
	//������� ���� � ����������� �� ������
	//setlocale(LC_ALL, ".1251"); //Windows 7+
	system("chcp 1251>nul"); //Windows 10+
	int proverka = 0, numT = 0, count = -1, n = 0, probels = 0, k = 0;
	float ABx, ABy, A�x, A�y, BCx, BCy, AB, BC, AC, S, P, cos1, cos2, cos3;
	int* num = calloc(0, sizeof(int)); //������, ������������ ������ ���������� �����
	FILE* file = fopen("examen.txt", "r");
	while (!feof(file)) //���������� ������
	{
		char* str = calloc(50, sizeof(char));
		fgets(str, 50, file); //��������� �� �����
		proverka = 0; //�������� �������� ������������ �����
		count++; //������� �����
		//���� �� �������� �������� ������
		for (int i = 0; i < strlen(str) - 1; i++) //strlen(str) c������ ������ � \n
		{
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ' || str[i] == '-' || str[i] == ',' || str[i] == '.')
			{
				proverka = 1; //��� ���������
				if (str[i] == ' ')
				{
					probels++; //������� �������� � ������ (������ ���� 5)
				}
			}
			else
			{
				proverka = 0;
				probels = 0;
				break;
			}
		}
		if (proverka == 1 && probels == 5) //���������� ����� ������ � ������
		{
			n++; //������� ��������� �������
			num = realloc(num, n * sizeof(int));
			num[n - 1] = count; // n-1 = 0
		}
		probels = 0;
		free(str); //������� �����
	}
	fclose(file);
	T* array = calloc(n, sizeof(T)); //�������� ������ ��� ��������� ���������� �������������
	printf("������ ���������� �����: ");
	for (int p = 0; p < n; p++) { printf("%d ", num[p] + 1); }
	printf("\n");
	file = fopen("examen.txt", "r");
	FILE* file2 = fopen("rezult.txt", "w"); //�������� ������������� � ������ � ����� ����
	for (int s = 0; s < count; s++)
	{
		if (num[k] == s) //����� ������ ����� ������ ������ ����������� ������������ -1, ��� ��� ���� � ����
		{
			fscanf(file, "%f %f %f %f %f %f\n", &array[num[k]].x1, &array[num[k]].y1, &array[num[k]].x2, &array[num[k]].y2, &array[num[k]].x3, &array[num[k]].y3); //��������� �� ����� � ���������																																	   //������� ������������
			ABx = array[num[k]].x2 - array[num[k]].x1;
			ABy = array[num[k]].y2 - array[num[k]].y1;
			A�x = array[num[k]].x3 - array[num[k]].x1;
			A�y = array[num[k]].y3 - array[num[k]].y1;
			BCx = array[num[k]].x3 - array[num[k]].x2;
			BCy = array[num[k]].y3 - array[num[k]].y2;
			//������� ������������
			S = abs(((ABx * A�y) - (A�x * ABy)) / 2);
			if (S != 0)
			{
				array[num[k]].status = 1;
				//����� ������
				AB = sqrt(abs(pow(ABx, 2) + pow(ABy, 2)));
				AC = sqrt(abs(pow(A�x, 2) + pow(A�y, 2)));
				BC = sqrt(abs(pow(BCx, 2) + pow(BCy, 2)));
				//��������
				P = AB + BC + AC;
				//��� ������������
				cos1 = Cosinus(array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3); // ������ ��� ����� - ��, ��� ���� �� ����
				cos2 = Cosinus(array[num[k]].x2, array[num[k]].y2, array[num[k]].x1, array[num[k]].y1, array[num[k]].x3, array[num[k]].y3);
				cos3 = Cosinus(array[num[k]].x3, array[num[k]].y3, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2);
				//������� �� ������� � � ����
				printf("����������� %d: %.2f %.2f %.2f %.2f %.2f %.2f\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3);
				fprintf(file2, "%d: %.2f %.2f %.2f %.2f %.2f %.2f - %d\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3, array[num[k]].status);
				if (cos1 == 0 || cos2 == 0 || cos3 == 0)
				{
					printf("���: �������������\n");
					fprintf(file2, "\t�������������\n");
				}
				else if (cos1 < 0 || cos2 < 0 || cos3 < 0)
				{
					printf("���: ������������\n");
					fprintf(file2, "\t������������\n");
				}
				else if (cos1 > 0 || cos2 > 0 || cos3 > 0)
				{
					printf("���: �������������\n");
					fprintf(file2, "\t�������������\n");
				}
				printf("����� ������: %.2f %.2f %.2f\nS = %.2f P = %.2f\n\n", AB, BC, AC, S, P);
				fprintf(file2, "\tAB = %.2f BC = %.2f AC = %.2f\n\tS = %.2f P = %.2f\n", AB, BC, AC, S, P);
			}
			else
			{
				array[num[k]].status = 0;
				fprintf(file2, "%d: %.2f %.2f %.2f %.2f %.2f %.2f - %d\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3, array[num[k]].status);
				printf("����������� %d: %.2f %.2f %.2f %.2f %.2f %.2f\n����� ����� �� ����� ������\n\n", num[k] + 1, array[num[k]].x1, array[num[k]].y1, array[num[k]].x2, array[num[k]].y2, array[num[k]].x3, array[num[k]].y3);
			}
			k++;
		}
		else
		{
			char* buffer = calloc(50, sizeof(char));
			fgets(buffer, 50, file); //��������� ������ �� �����
			free(buffer);
		}
	}
	fclose(file);
	fclose(file2);
	return 0;
}
