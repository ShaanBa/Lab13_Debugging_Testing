/*
 * Lab 13 — Debugging & Testing
 * attendance_test.cpp
 *
 * Author: Shaan Bawa
 * Creation date: 2025-11-25
 *
 * -----------------------------------------------------------------------
 * WRITTEN ANSWERS (PROLOGUE):
 * -----------------------------------------------------------------------
 *
 * 1. Is there a fault in the program? If so, locate it and explain.
 * YES. The fault is in the loop initialization: `for (int i = 1; ...`.
 * The loop starts at index 1 instead of index 0. This causes the program
 * to ignore the attendance status of the very first lecture.
 *
 * 2. Define a test case that does not execute the fault.
 * IMPOSSIBLE. The fault is located in the unconditional loop header
 * (`int i = 1`). Whenever the function is called, this line causes the
 * fault to be executed immediately. We cannot run the function without
 * triggering this initialization.
 *
 * 3. Define a test case that executes the fault but does not result in an error state.
 * Input: {1, 0, 0, 0, 1, 1, 1, 1, 1, 1}
 * Explanation: The student was PRESENT (1) at index 0. The faulty code skips
 * index 0. Since the student was present, skipping it does not increase the
 * 'absent' count. The internal variable `absentCount` remains correct (0)
 * at that step.
 *
 * 4. Define a test case that results in an error state but not a failure.
 * Input: {0, 0, 0, 0, 1, 1, 1, 1, 1, 1}
 * Explanation: The student was ABSENT (0) at index 0. The faulty code skips
 * it, so the internal `absentCount` is 3. The correct count is 4. This is an
 * ERROR STATE (internal variables differ). However, since both 3 and 4 are
 * >= 3, both functions return TRUE (Fail). Thus, no external failure occurs.
 *
 * 5. Define a test case that results in failure.
 * Input: {0, 0, 0, 1, 1, 1, 1, 1, 1, 1}
 * Explanation: The student was ABSENT (0) at index 0.
 * Correct count = 3 (Result: Fail).
 * Faulty count = 2 (Result: Pass).
 * The faulty function returns FALSE when it should return TRUE.
 * -----------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;

// ---------------------------------------------------------
// 1. The Faulty Implementation (Required by Lab)
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
// 2. The Correct Implementation (Required by Lab)
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
    cout << "Note: Written answers are located in the prologue comments.\n";
    cout << "--------------------------------------------------\n\n";

    struct TestCase {
        std::string question;
        std::string description;
        vector<int> input;
    };

    vector<TestCase> tests = {
        // Q3: Execute fault, but NO error state.
        {
            "Q3",
            "Execute fault, NO Error State (Index 0 is Present/1)",
            {1, 0, 0, 0, 1, 1, 1, 1, 1, 1} 
        },

        // Q4: Error state, but NO failure.
        {
            "Q4",
            "Error State, NO Failure (Index 0 is Absent/0, total > 3)",
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1}
        },

        // Q5: Failure.
        {
            "Q5",
            "Failure (Index 0 is Absent/0, total hits threshold exactly)",
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1}
        }
    };

    // ---------------------------------------------------------
    // Run Tests
    // ---------------------------------------------------------
    
    // Explicitly print Q2 answer to console as well
    cout << "Test Q2: Case that does not execute fault.\n";
    cout << "   Result: IMPOSSIBLE (Fault is in unconditional loop init).\n";
    cout << "--------------------------------------------------\n";

    for (const auto& t : tests) {
        cout << "Test " << t.question << ": " << t.description << "\n";
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