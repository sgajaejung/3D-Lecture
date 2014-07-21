#include <iostream>
using namespace std;

struct sAAA
{
	int a;
	int b;
	char c;
	float f;
	int ccc[100];
	int *pp;
};


struct sTerain
{
	int col;
	int row;
	float cellSize;
	int size; // 100, 200;
	float height[ 10000];
	//float height[];
};


void main()
{
	{
		FILE *fp = fopen("aaa.bin", "w");
		sAAA ss;
		ss.a = 10;
		ss.b = 20;
		ss.c = 'A';
		ss.f = 0.123f;
		fwrite(&ss, sizeof(sAAA), 1, fp);
		fclose(fp);
	}


	{
		FILE *fp = fopen("aaa.bin", "r");
		sAAA bb;
		fread(&bb, sizeof(sAAA), 1, fp);
		fclose(fp);
	}


	{


	}




}
