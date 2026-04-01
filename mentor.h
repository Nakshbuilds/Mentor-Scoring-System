#ifndef MENTOR_H
#define MENTOR_H

#include <string>
#include <vector>

using namespace std;

struct Student{
    string studentID;
    string name;
    string projectID;
    int milestonesCompleted;
    int totalMilestones;
};

struct Mentor{
    string mentorID;
    string name;
    string domain;
    vector <string>projectIDs ;

    //Scores for mentors initialized to 0
    double P = 0.0;
    double R = 0.0;
    double E = 0.0;
    double F = 0.0;
    double Finalscore = 0.0;
};

struct Interactions{
    string mentorID;
    string studentID;
    int meetings;
    int codeReview;
    int message;
    double tavg;
    int feedback;
};

double calculateP(int completedPoints, int totalPoints);
double calculateR(double tavg);
double calculateE(int meetings, int codereviews, int interactions, int students);
double calculateF(int feedback, int students);









#endif