#include <fstream>
#include <iostream>
#include "head.h"
#include <cmrc/cmrc.hpp>
CMRC_DECLARE(csv_res);
using namespace std;

const auto OperatorFile = "operator.csv";
const auto PhoneFile = "phone.csv";
const auto Job1File = "job.csv";
const auto Job2File = "job_proportion.csv";

auto create_address() {
	array<const char*, 194003> address;
	auto fs = cmrc::csv_res::get_filesystem();
	auto ptr = fs.open("address_spb2.csv").begin();
	for (auto& dst : address) {
		dst = ptr;
		ptr = strchr(ptr, 0) + 1;
	}
	return address;
}
auto create_phones() {
	phone_vector phones;
	for (ifstream input(OperatorFile); input.peek() != EOF;) {
		string name, s;
		getline(input, name, ';');
		getline(input, s);
		phones.range +=
			phones[name].probability = stoi(s);
	}
	for (ifstream input(PhoneFile); input.peek() != EOF;) {
		string name, s;
		mobile_range_s mr;
		getline(input, name, ';');
		getline(input, s, ';');			mr.begin = stoll(s);
		getline(input, s, ';');			mr.range = stoll(s) - mr.begin;
		getline(input, s);				mr.probability = stoi(s);
		phones[name].push_back(mr);
	}
	return phones;
}
auto create_job1() {
	job1vector jobs;
	for (ifstream input(Job1File); input.peek() != EOF;) {
		string s;
		job1s job;
		getline(input, job.name, ';');
		getline(input, s, ';');			job.salary = stoi(s);
		getline(input, s);				job.number = stoi(s);
		jobs.push_back(job);
	}
	return jobs;
}
auto create_job2() {
	job2vector jobs;
	for (ifstream input(Job2File); input.peek() != EOF;) {
		string s;
		job2s job;
		getline(input, job.name, ';');
		getline(input, s, ';');			job.salary = stoi(s);
		getline(input, s);				job.proportion = stoi(s);
		jobs.push_back(job);
	}
	return jobs;
}

array<const char*, 194003> address = create_address();
phone_vector phone = create_phones();
job1vector job1 = create_job1();
job2vector job2 = create_job2();

/*array<const char*, 25221> address;
map<string, operator_s> phone;
vector<job1s> jobs1;
vector<job2s> jobs2;
void init() {
	address = create_address();
	phone = create_phones();
	job1 = create_job1();
	job2 = create_job2();
}*/
