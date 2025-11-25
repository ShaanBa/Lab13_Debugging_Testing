/*
 * Lab 13 — Debugging & Testing
 * attendance_test.cpp
 *
 * Purpose: demonstrate the fault/error/failure distinction for a simple
 * attendance checker. Implements the faulty function (as given) and a
 * corrected version, then runs a set of test cases that show cases that
 * (a) do not expose the fault, (b) execute the fault but no error state,
 * (c) produce an internal error state but no failure, and (d) produce a
 * failure.
 *
 * Author: Shaan Bawa
 * Creation date: 2025-11-25
 */

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;

// Faulty implementation taken from the lab description.
bool failLecture_faulty(const vector<int>& attendanceRecords) {
    int absentCount = 0;
    // BUG: loop starts at 1, so attendanceRecords[0] is ignored
    for (int i = 1; i < (int)attendanceRecords.size(); ++i) {
        absentCount += attendanceRecords[i] == 0;
    }
    return absentCount >= 3;
}