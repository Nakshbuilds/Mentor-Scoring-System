#ifndef MENTOR_H
#define MENTOR_H

#include <string>
#include <vector>

struct Student{
    std::string studentID;
    std:: string name;
    std::string projectID;
    int milestonesCompleted;
    int totalMilestones;
};

struct Mentor{
    std::string mentorID;
    std::string name;
    std::string domain;
    std::vector <std::string>projectIDs ;

    //Scores for mentors initialized to 0
    double P = 0.0;
    double R = 0.0;
    double E = 0.0;
    double F = 0.0;
    double Finalscore = 0.0;
    int rank = 0;
};

struct Interactions{
    std::string mentorID;
    std::string studentID;
    int meetings;
    int codeReview;
    int message;
    double tavg;
    int feedback;
};

void readStudents(std::string filename, std::vector<Student>& students1);
void readMentors(std::string filename, std::vector<Mentor>& mentors1);
void readInteractions(std::string filename, std::vector<Interactions>& interactions1);
void feedbacks(std::string filename, std::vector<Interactions>& interactions1);

// double calculateP(int completedPoints, int totalPoints);
// double calculateR(double tavg);
// double calculateE(int meetings, int codereviews, int interactions, int students);
// double calculateF(int feedback, int students);


void calculateScores(std::vector<Mentor>& mentors, const std::vector<Student>& students, const std::vector<Interactions>& interactions);
void sortMentors(std::vector<Mentor>& mentors);
void saveResults(const std::vector<Mentor>& mentors, const std::string& mentor_scores);

#endif