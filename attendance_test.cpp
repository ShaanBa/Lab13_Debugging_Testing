/*
 * Lab 13 — Debugging & Testing
 * attendance_test.cpp
 *
 * Purpose: Demonstrate the fault/error/failure distinction for a simple
 * attendance checker.
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

// ---------------------------------------------------------
// 1. The Faulty Implementation (from Lab PDF)
// ---------------------------------------------------------
bool failLecture_faulty(const vector<int>& attendanceRecords) {
    int absentCount = 0;
    // FAULT: Loop starts at 1, ignoring index 0.
    for (int i = 1; i < (int)attendanceRecords.size(); ++i) {
        absentCount += attendanceRecords[i] == 0;
    }
    return absentCount >= 3;
}

// ---------------------------------------------------------
// 2. The Correct Implementation
// ---------------------------------------------------------
bool failLecture_correct(const vector<int>& attendanceRecords) {
    int absentCount = 0;
    // CORRECT: Loop starts at 0.
    for (int i = 0; i < (int)attendanceRecords.size(); ++i) {
        absentCount += attendanceRecords[i] == 0;
    }
    return absentCount >= 3;
}

// Helper to count actual absences for verification
int count_absent(const vector<int>& v) {
    int c = 0;
    for (int x : v) c += (x == 0);
    return c;
}

// Helper to print the vector
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
    cout << "Lab 13 — Debugging and Testing\n";
    cout << "Author: Shaan Bawa\n";
    cout << "--------------------------------------------------\n\n";

    // ---------------------------------------------------------
    // Q1: Fault Identification
    // ---------------------------------------------------------
    cout << "Q1) Is there a fault? Locate and explain.\n";
    cout << "Answer: YES. The fault is in the loop initialization: 'int i = 1'.\n";
    cout << "The loop skips the first attendance record (index 0), causing an\n";
    cout << "off-by-one error in counting absences if the student was absent at lecture 0.\n\n";

    // ---------------------------------------------------------
    // Q2: Test case that does NOT execute the fault
    // ---------------------------------------------------------
    cout << "Q2) Test case that does NOT execute the fault.\n";
    cout << "Answer: IMPOSSIBLE.\n";
    cout << "Reason: The fault is located in the unconditional loop header.\n";
    cout << "Whenever the function is called, the line 'int i = 1' is executed.\n";
    cout << "Therefore, we cannot run the function without executing the fault.\n\n";

    // ---------------------------------------------------------
    // Test Setup for Q3, Q4, Q5
    // ---------------------------------------------------------
    struct TestCase {
        std::string question;
        std::string description;
        vector<int> input;
    };

    vector<TestCase> tests = {
        // Q3: Execute fault, but NO error state.
        // Index 0 is '1' (Present). Skipping it doesn't change the count.
        {
            "Q3",
            "Execute fault, NO Error State",
            {1, 0, 0, 0, 1, 1, 1, 1, 1, 1} 
        },

        // Q4: Error state, but NO failure.
        // Index 0 is '0' (Absent). Internal count is wrong (off by 1), 
        // but total absences are high enough (4) that both return True.
        {
            "Q4",
            "Error State, NO Failure",
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1}
        },

        // Q5: Failure.
        // Index 0 is '0' (Absent). Internal count is wrong (2 vs 3).
        // Correct returns True (Fail), Faulty returns False (Pass).
        {
            "Q5",
            "Failure (External behavior incorrect)",
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1}
        }
    };

    // ---------------------------------------------------------
    // Run Tests
    // ---------------------------------------------------------
    for (const auto& t : tests) {
        cout << t.question << ") " << t.description << "\n";
        cout << "   Input: " << printVec(t.input) << "\n";

        // Calculate data
        int correctAbsences = count_absent(t.input);
        
        // Simulate faulty internal state manually for demonstration
        int faultyInternalCount = 0;
        for(size_t i=1; i<t.input.size(); ++i) faultyInternalCount += (t.input[i]==0);

        bool expectedResult = failLecture_correct(t.input);
        bool actualResult = failLecture_faulty(t.input);

        cout << "   Correct Internal Count: " << correctAbsences << "\n";
        cout << "   Faulty  Internal Count: " << faultyInternalCount << "\n";
        
        if (correctAbsences != faultyInternalCount) {
             cout << "   [!] Error State Detected: Internal variables differ.\n";
        } else {
             cout << "   [OK] No Error State: Internal variables match.\n";
        }

        cout << "   Expected Output: " << (expectedResult ? "True (Fail Course)" : "False (Pass Course)") << "\n";
        cout << "   Actual Output:   " << (actualResult ? "True (Fail Course)" : "False (Pass Course)") << "\n";

        if (expectedResult != actualResult) {
            cout << "   => FAILURE OBSERVED.\n";
        } else {
            cout << "   => NO FAILURE OBSERVED.\n";
        }
        cout << "--------------------------------------------------\n";
    }

    return 0;
}