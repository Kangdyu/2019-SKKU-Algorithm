#ifndef TIME_TABLE
#define TIME_TABLE

class TimeTable {
private:
	int source[200];
	int destination[200];
	int timetable[200][31];
	int insert_num = 0;

public:
	
	void random_generate();

	// initializing insert_num
	void insert_init();

	void insert_city_info(int src, int dst);

	int seek(int src, int dst, int date);
};

#endif