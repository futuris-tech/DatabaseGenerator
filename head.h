#pragma once
#include <cstdint>
#include <array>
#include <cstring>
#include <algorithm>

struct mobile_range_s {
	int64_t begin;
	int64_t range_end;
	inline mobile_range_s(int64_t begin, int64_t range_end) :
		begin(begin), range_end(range_end) {}
};
struct operator_s {
	const mobile_range_s* begin;
	const mobile_range_s* end;
	int num_count;
	int probability;
	inline operator_s(
		const mobile_range_s* begin,
		const mobile_range_s* end,
		int num_count,
		int probability) 
	:
		begin(begin),
		end(end),
		num_count(num_count),
		probability(probability) {}
};
struct job_s {
	const char8_t* name;
	int salary;
	job_s(const char8_t* name, int salary) :
		name(name), salary(salary) {}
};
struct job1s : job_s {
	int number;
	job1s(
		const char8_t* name,
		int salary,
		int number)
	:
		job_s(name, salary),
		number(number) {}
};
struct job2s : job_s {
	int proportion;
	job2s(
		const char8_t* name,
		int salary,
		int proportion)
	:
		job_s(name, salary),
		proportion(proportion) {}
};

extern const std::array<const char8_t*, 40> m_name;
extern const std::array<const char8_t*, 44> f_name;
extern const std::array<const char8_t*, 250> surname;
extern const std::array<const char8_t*, 73> lastname;
extern const std::array<mobile_range_s, 131> mob_range;
extern const std::array<operator_s, 5> mob_operator;
extern const std::array<job1s, 1> job1;
extern const std::array<job2s, 10> job2;
extern std::array<const char*, 25221> address;

namespace database {
	extern const unsigned mob_operator_range;
	extern const unsigned job_range;
}

void init_database();