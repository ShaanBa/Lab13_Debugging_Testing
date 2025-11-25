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

// Correct implementation: count from index 0
bool failLecture_correct(const vector<int>& attendanceRecords) {
    int absentCount = 0;
    for (int i = 0; i < (int)attendanceRecords.size(); ++i) {
        absentCount += attendanceRecords[i] == 0;
    }
    return absentCount >= 3;
}

int count_absent(const vector<int>& v) {
    int c = 0;
    for (int x : v) c += (x == 0);
    return c;
}

std::string printVec(const vector<int>& v) {
    std::string s = "{";
    for (size_t i = 0; i < v.size(); ++i) {
        s += (v[i] == 0 ? '0' : '1');
        if (i + 1 < v.size()) s += ',';
    }
    s += "}";
    return s;
}

int main() {
    cout << "Lab 13 — Attendance fault demonstration\n\n";

    // Test case (Q2) — does NOT expose the fault (both functions agree).
    // Attendance: absences at indices 1,2,3 (three absences but index 0 present)
    vector<int> T_noExpose = {1,0,0,0,1,1,1,1,1,1};

    // Test case (Q3) — executes the faulty code but does not produce an error state
    // (faulty code executed; both functions still return the same boolean).
    vector<int> T_faultExec_noError = {1,0,0,0,1,1,1,1,1,1}; // same as above

    // Test case (Q4) — internal error state but NOT a failure: correct counts 4,
    // faulty counts 3 (ignores index 0), both still report "fail" (true).
    vector<int> T_errorNoFailure = {0,0,0,0,1,1,1,1,1,1};

    // Test case (Q5) — failure: correct says fail (3 absences) but faulty ignores
    // the absence at index 0 and returns false.
    vector<int> T_failure = {0,0,0,1,1,1,1,1,1,1};

    struct Test { std::string name; vector<int> v; };
    vector<Test> tests = {
        {"DoesNOTExposeFault (Q2)", T_noExpose},
        {"FaultExec_NoError (Q3)", T_faultExec_noError},
        {"ErrorState_NoFailure (Q4)", T_errorNoFailure},
        {"Failure (Q5)", T_failure}
    };

    for (const auto &t : tests) {
        int correctCount = count_absent(t.v);
        int faultyCount = 0; // compute faulty's internal count by calling the loop manually
        for (int i = 1; i < (int)t.v.size(); ++i) faultyCount += (t.v[i] == 0);

        bool expect = correctCount >= 3;
        bool actual = failLecture_faulty(t.v);

        cout << "Test: " << t.name << "\n";
        cout << "  Attendance: " << printVec(t.v) << " (len=" << t.v.size() << ")\n";
        cout << "  Correct absent count = " << correctCount << ", Faulty internal count = " << faultyCount << "\n";
        cout << "  Expected (correct) result: " << (expect ? "FAIL (true)" : "PASS (false)") << "\n";
        cout << "  Faulty function result:  " << (actual ? "FAIL (true)" : "PASS (false)") << "\n";

        if (expect == actual) {
            if (correctCount != faultyCount) {
                cout << "  => INTERNAL ERROR STATE (counts differ) but NO FAILURE (external behavior matches).\n";
            } else {
                cout << "  => No error observed; faulty implementation did not change outcome.\n";
            }
        } else {
            cout << "  => FAILURE: external behavior deviates from correct behavior.\n";
        }
        cout << "\n";
    }

    // Also answer Q1 explicitly (print fault description)
    cout << "Q1) Fault location and explanation:\n";
    cout << "  Fault: the loop in the provided implementation starts at index 1 (for i=1)",
         " so the attendance at index 0 is ignored. For 10 lectures (indices 0..9) this causes",
         " an off-by-one counting error whenever the student is absent at lecture 0.\n\n";

    cout << "Summary (mapping to lab terms):\n";
    cout << "  - Fault: the off-by-one bug in the loop (code defect).\n";
    cout << "  - Error state: the internal absent count differs from the correct count (e.g., 3 vs 4).\n";
    cout << "  - Failure: the returned boolean differs from the correct result (example run above: 'Failure (Q5)').\n";

    return 0;
}

