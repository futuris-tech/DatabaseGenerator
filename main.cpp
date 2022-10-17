#include <stdio.h>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "head.h"
using namespace std;

const int RowNum = 10000;
const int HalfSalaryProbability = 10000;		//0 - 65536

class randomaizer {
	struct city {
		char* name;
		char* coutry;
	};

	std::default_random_engine dre;
public:
	randomaizer() : dre(
		std::chrono::system_clock().now().time_since_epoch().count()) {}

	uint32_t operator()() { return dre(); }
	inline uint32_t get_small(uint32_t range, int pow = 1) {
		uint64_t value = dre();
		do value = value * value / dre.max();
		while (--pow);
		return value * range / dre.max();
	}

	const char* get_name() {
		static char buffer[256];
		bool m = dre() % 2;

		auto input = (const char*)surname[dre() % surname.size()];
		strcpy(buffer, input);
		auto ptr = buffer + strlen(buffer);
		if (!m) {
			strcpy(ptr, (const char*)u8"а");
			ptr += 2;
		}
		*ptr++ = ' ';

		if (m)	input = (const char*)m_name[dre() % m_name.size()];
		else	input = (const char*)f_name[dre() % f_name.size()];
		strcpy(ptr, input);
		ptr += strlen(ptr);
		*ptr++ = ' ';

		input = (const char*)lastname[dre() % lastname.size()];
		strcpy(ptr, input);
		if (!m) {
			ptr += strlen(ptr);
			strcpy(ptr - 4, (const char*)u8"на");
		}

		return buffer;
	}
	uint64_t get_mobile() {
		unsigned r = dre() % database::mob_operator_range;
		auto mo_ptr = mob_operator.begin();
		while (r >= mo_ptr->probability) {
			r -= mo_ptr->probability;
			mo_ptr++;
		}

		auto mr_begin = mo_ptr->begin;
		auto mr_end = mo_ptr->end;
		r = dre() % mr_end[-1].range_end + 1;
		auto mr_ptr = lower_bound(mr_begin, mr_end, r,
			[](const mobile_range_s& mr, unsigned value) { return mr.range_end < (int)value; });
		
		return mr_ptr->begin + r - mr_ptr[-1].range_end;
	}
	unsigned get_salary(unsigned average) {
		if ((dre() & 0xffff) < HalfSalaryProbability)
			average /= 2;

		auto add = get_small(average / 2, 2);
		if (dre() % 2)
			return average + add;
		else
			return average - add;
	}
};

int main() {
	init_database();
	ofstream out("result.csv");
	randomaizer dre;
	for (int left = RowNum; left;) {
		int max_empolyee_num = std::min(left, 5000);
		int employee_num = 50 + dre.get_small(max_empolyee_num - 49, 2);
		left -= employee_num;
		if (left < 50) {
			employee_num += left;
			left = 0;
		}

		auto addr = address[dre() % address.size()];
		auto write = [&](const job_s& j) {
			out << dre.get_name()			<< ';'
				<< "\"+" << dre.get_mobile()<< "\";"
				<< addr						<< ';'
				<< (const char*)j.name		<< ';'
				<< dre.get_salary(j.salary)	<< '\n';
		};

		for (auto& j : job1) {
			employee_num -= j.number;
			for (int i = j.number; i; i--)
				write(j);
		}

		int i = 0, c = 0;
		for (auto& j : job2) {
			c += j.proportion;
			int i_end = c * employee_num / database::job_range;
			for (; i < i_end; i++)
				write(j);
		}
	}
	return 0;
}
