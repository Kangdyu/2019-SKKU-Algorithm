#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TimeTable.h"

void TimeTable::random_generate() {
	srand(7537);
	//srand(time(NULL));
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 31; j++) {
			timetable[i][j] = rand() % 48;
			timetable[i][j] *= 30;
		}
	}
}

void TimeTable::insert_init() {
	insert_num = 0;
}

void TimeTable::insert_city_info(int src, int dst) {
	if (insert_num < 200) {
		source[insert_num] = src;
		destination[insert_num] = dst;
		insert_num++;
	}
}

int TimeTable::seek(int src, int dst, int date) {
	for (int i = 0; i < 200; i++) {
		if (source[i] == src && destination[i] == dst) {
			return timetable[i][date];
		}
	}
	return -1;
}

void TimeTable::print()
{
	for (int i = 0; i < 200; i++)
	{
		printf("%3c%3c", source[i] + 97, destination[i] + 97);
		for (int j = 0; j < 31; j++)
			printf("%5d", timetable[i][j]);
		printf("\n");
	}
	printf("\n");
}