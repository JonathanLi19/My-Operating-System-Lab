#include<iostream>
using namespace std;
int main()
{
	FILE* fp = fopen("mbr.bin", "rb+");
	if (fp == NULL)
	{
		cout << "Cannot find the file!\n";
		return 0;
	}
	fseek(fp, 0, SEEK_END); //定位到文件末
	int n;
	n = ftell(fp); //文件长度
	if (n > 510)
	{
		cout << "ERROR: boot block too large: "<< n << "bytes (max 510)\n";
	}
	else
	{
		cout << "OK: boot block is "<< n << "bytes(max 510)\n";
		for (int i = 0; i < 510 - n; i++)
		{
			fputc('\0', fp);
		}
		fputc('\x55', fp);
		fputc('\xaa', fp);
	}
	fclose(fp);
	return 0;
}
