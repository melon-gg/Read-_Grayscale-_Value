#include <iostream>

using namespace std;

#include<stdio.h>
#include<stdlib.h>
#include <fstream>
#include <vector>

#define length 100
#define width 100
#define height 100

#define size height * width * length

struct point {
	int x;
	int y;
	int z;
};

void main()
{
	int i, j;

	FILE *fp;
	fp = fopen("a.raw", "rb");
	if (!fp)
	{
		printf("raw file open failed!\n");
	}
	fseek(fp, 0, SEEK_END); 
	int nFileLen = ftell(fp); 
	rewind(fp);
	unsigned char *pData = new unsigned char[nFileLen]; 

	fread(pData, sizeof(unsigned char), nFileLen, fp);
	fclose(fp); 

	//�Ҷ�ֵ
	int value[256] = { 0 }; 
	vector<point> v(256);
	//ͳ�ƻҶ�ֵ
	int l = 0;
	for (i = 0; i < length; i++) 
		for(int j = 0; j < width; j++)
			for (int k = 0; k < height; k++)
			{
				value[pData[l++]]++;
			}

	printf("�Ҷ�ֵ\t\t��С"); 
	printf("\n");
	fp = fopen("result.txt", "wb");
	fprintf(fp, "�Ҷ�ֵ\t\t��С\r\n");

	for (i = 0; i < size; i++)
	{
		char p[100] = { 0 };
		int x = i / height / width % width;
		int y = i / height % height;
		int z = i % height;
		p[0] = '(';
		char t[100] = { 0 };

		itoa(x, t, 10);
		strcat(p, t);
		strcat(p, ",");
		memset(t, 0, 100);

		itoa(y, t, 10);
		strcat(p, t);
		strcat(p, ",");
		memset(t, 0, 100);

		itoa(z, t, 10);
		strcat(p, t);
		memset(t, 0, 100);
		strcat(p, ")");

		printf("%s\t\t%d\n", p, pData[i]);
		fprintf(fp, "%s\t\t%d\r\n", p, pData[i]); //ע��\r\n �����ܻ���
	}
	delete[] pData;
	fclose(fp); 
}