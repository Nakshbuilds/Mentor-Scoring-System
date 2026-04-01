#include "mentor.h"
#include <iostream>
#include <vector>

using namespace std;
int main(){
    vector<Mentor> mentors;
    vector<Student> students;
    vector<Interactions> interactions;

    readStudents("students.csv", students);
    readMentors("mentors.csv", mentors);
    readInteractions("interactions.csv", interactions);
    feedbacks("feedbacks.csv", interactions);

    cout << "Calculating Mentor Scores..." << endl;
    calculateScores(mentors, students, interactions);

    cout << "Ranking Mentors..." << endl;
    sortMentors(mentors);

    // cout << "Rank | Name | Score" << endl;
    // for (const auto& m : mentors) {
    //     cout << m.rank << " | " << m.name << " | " << m.Finalscore << endl;
    // }
    saveResults( mentors,"mentor_scores.csv");

    return 0;
}