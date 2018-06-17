#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nullptr (0)

//typedef struct Nameval Nameval;
typedef struct Nameval {
	char name[12];
	int value;
} Nameval;

struct NVtab {
	int nval;
	int max;
	Nameval *nameval;
} nvtab;

enum { NVINT = 1, NVGROW = 2 };

int addname(Nameval newname)
{
	Nameval *nvp;

	if (nvtab.nameval == NULL)
	{
		nvtab.nameval = (Nameval *)malloc(NVINT * sizeof(Nameval));
		if (nvtab.nameval == NULL)
			return -1;
		nvtab.max = NVINT;
		nvtab.nval = 0;
	}
	else if(nvtab.nval >= nvtab.max)
	{
		nvp = (Nameval *)realloc(nvtab.nameval, (NVGROW*nvtab.max) * sizeof(Nameval));
		if (nvp == NULL)
			return -1;
		nvtab.max *= NVGROW;
		nvtab.nameval = nvp;
	}

	nvtab.nameval[nvtab.nval] = newname;
	return nvtab.nval++;
}

int delname(char *name)
{
	for (int i = 0; i < nvtab.nval; i++)
		if (strcmp(nvtab.nameval[i].name, name) == 0)
		{
			memmove(nvtab.nameval + 1, nvtab.nameval + i + 1,
				(nvtab.nval - (i + 1)) * sizeof(Nameval));
			nvtab.nval--;
			return 1;
		}

	return 0;
}

int main(void)
{
	printf("Programming start .. \n");
	Nameval aperson[10];
	// initializes aperson
	//aperson.name = nullptr;
	for (int i = 0; i < 12; i++)
	{
		aperson[i].name[i] = 0;
		aperson[i].value = 0;
	}

	// assign values to aperson
	char szData[12] = { "Hello" };
	
	strncpy_s(aperson[0].name, szData, 4);
	aperson[0].value = 99;
	addname(aperson[0]);

	const char *name = "ROY";
	strncpy_s(aperson[1].name, name, 4);
	aperson[1].value = 100;
	addname(aperson[1]);

	printf("%d\n", nvtab.nval);
	for (int i = 0; i < nvtab.nval ; i++)
		printf("%s\n", nvtab.nameval[i].name);

	printf("\nEnd programming..\n");
	return 0;
}
