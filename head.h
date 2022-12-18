#pragma once
#include <cstring>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

struct mobile_range_s {
	uint64_t begin;
	uint32_t range;
	uint32_t probability;
};
struct operator_s : std::vector<mobile_range_s> {
	uint32_t probability = 0;
    uint32_t range = 0;
    inline void push_back(const mobile_range_s& x) {
        std::vector<mobile_range_s>::push_back(x);
        range += x.probability;
    }
};
struct phone_vector : std::map<std::string, operator_s> {
    uint32_t range = 0;
};

struct job_s {
	std::string name;
	int salary;
};
struct job1s : job_s {
	int number;
};
struct job2s : job_s {
	int proportion;
};
typedef std::vector<job1s> job1vector;
struct job2vector : std::vector<job2s> {
    uint32_t range = 0;
    inline void push_back(const job2s& x) {
        std::vector<job2s>::push_back(x);
        range += x.proportion;
    }
};

extern uint32_t operator_range;
extern const std::array<const char8_t*, 40> m_name;
extern const std::array<const char8_t*, 44> f_name;
extern const std::array<const char8_t*,250> surname;
extern const std::array<const char8_t*, 73> lastname;
extern std::array<const char*, 194003> address;
extern phone_vector phone;
extern job1vector job1;
extern job2vector job2;
