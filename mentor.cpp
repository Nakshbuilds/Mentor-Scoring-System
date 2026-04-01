#include"mentor.h" // To include our own functions 
#include<iostream> // To handle the input and output stream
#include<fstream> // To read and write csv files
#include<sstream> // To read the file by breaking at comma
#include<vector> // To use dynamic array
#include<string>
#include<cmath>

using namespace std;

//Let's read the csv files
//1) Students
void readStudents(string students, vector<Student>& students1){
    //Opening the file
    ifstream file(students);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    string line;                // Variable that holds one row of the CSV;

    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        string cell;
        Student tmp;

        getline(ss, tmp.studentID, ',');

        getline(ss, tmp.name, ',');

        getline(ss, tmp.projectID, ',');

        getline(ss, cell, ',');
        tmp.milestonesCompleted = stoi(cell);

        getline(ss, cell, ',');
        tmp.totalMilestones = stoi(cell);

        students1.push_back(tmp);
        }

        file.close();
}

void readMentors(string mentors, vector<Mentor>& mentors1){
     ifstream file(mentors);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    string line;                // Variable that holds one row of the CSV;

    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        string cell;
        Mentor tmp;

        getline(ss, tmp.mentorID, ',');

        getline(ss, tmp.name, ',');

        getline(ss, tmp.domain, ',');

        string allProjects;
        getline(ss, allProjects, ',');

        std::stringstream projSS(allProjects);
        std::string pID;
        while (std::getline(projSS, pID, ';')) { // Split by semicolon
            tmp.projectIDs.push_back(pID);
        }
        mentors1.push_back(tmp);
}
file.close();
}


void readInteractions(string interactions, vector<Interactions>& interactions1){
    ifstream file(interactions);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }
    string line;
    getline(file,line);

    while(getline(file, line)){
        stringstream ss(line);
        string cell;
        Interactions tmp;

        getline(ss, tmp.mentorID, ',');

        getline(ss, tmp.studentID, ',');

         getline(ss, cell, ',');
        tmp.meetings = stoi(cell);

         getline(ss, cell, ',');
        tmp.codeReview= stoi(cell);

         getline(ss, cell, ',');
        tmp.message = stoi(cell);

         getline(ss, cell, ',');
        tmp.tavg = stod(cell);

        interactions1.push_back(tmp);
}
    file.close();
}
void loadStepTwo(string feedbacks, std::vector<Interactions>& interactions1) {
    std::ifstream file(feedbacks);
    std::string line, cell, currentIDm, currentIDs;
    std::getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, currentIDm, ','); // Get ID from File B

        getline(ss, currentIDs, ',');
        for(auto& tmp : interactions1){
            if(tmp.mentorID == currentIDm && tmp.studentID == currentIDs){
                // Found a match! Fill the rest of the struct
                getline(ss, cell, ',');
                tmp.feedback = stoi(cell);
                break;
            }
        }
    }
    file.close();
}

//First function

void calculateScores(vector<Mentor>& mentors, const vector<Student>& students, const vector<Interactions>& interactions) {
    for (auto& m : mentors) {
        double totalMilestones = 0, completedMilestones = 0;      // Initialize all the components to 0.
        double totalResponseTime = 0, interactionCount = 0;
        double engagementSum = 0, feedback = 0;
        int menteeCount = 0;

        for (const auto& i : interactions) {
            if (i.mentorID == m.mentorID) {
                menteeCount++;
                totalResponseTime += i.tavg;
                engagementSum += ((1.5 * i.meetings) + (1.5 * i.codeReview) + i.message);
                feedback += i.feedback;
                
                // Find matching student progress
                for (const auto& s : students) {
                    if (s.studentID == i.studentID) {
                        int n = s.milestonesCompleted;
                        int m = s.totalMilestones;
                        completedMilestones += n*(n + 1)/2;
                        totalMilestones += m*(m + 1)/2;
                    }
                }
            }
        }
       // 1. Progress Score (P)
        m.P = (totalMilestones > 0) ? (completedMilestones / totalMilestones) : 0;  

        // 2. Responsiveness Score (R) using e^(-0.25 * tavg)
        if (menteeCount > 0) {
            double avgT = totalResponseTime / menteeCount;
            m.R = std::exp(-0.25 * avgT);

            // 3. Engagement Score (E) - Normalized per mentee
            // Assuming a 'high' engagement is 50 interactions per mentee for 1.0 score
            m.E = (engagementSum / menteeCount) / 50.0;
            if (m.E > 1.0) m.E = 1.0;
        }
        //4. Calculating feedback
        m.F = feedback/(5 * menteeCount);

        //5. Calculating total sum using weighted score
        m.Finalscore = (0.25 * m.P) + (0.25 * m.R) + (0.3 * m.E) + (0.2 * m.F);
    }
}

void sortMentors(vector<Mentor>& mentors) { // Manual selection sort
    int n = mentors.size();
    for(int i = 0; i < n-1 ; i++){
        int max = i;
        for(int j = i+1; j < n ; j++){
        if(mentors[max].Finalscore < mentors[j].Finalscore)
        max = j;
        }
        Mentor tmp = mentors[max];
        mentors[max] = mentors[i];
        mentors[i] = tmp;
    }
    for (int i = 0; i < n; i++) mentors[i].rank = i + 1;
}




