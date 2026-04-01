#include"mentor.h" // To include our own functions 
#include<iostream> // To handle the input and output stream
#include<fstream> // To read and write csv files
#include<sstream> // To read the file by breaking at comma
#include<vector> // To use dynamic array
#include<string>

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
        mentors.push_back(tmp);
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



