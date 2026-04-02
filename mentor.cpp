#include"mentor.h" // To include our own functions 
#include<iostream> // To handle the input and output stream
#include<fstream> // To read and write csv files
#include<sstream> // To read the file by breaking at comma
#include<vector> // To use dynamic array
#include<string> // To be able to handle strings
#include<cmath> // For complex math equations
#include<unordered_map> // For calculating the score
#include <algorithm> // Required for std::sort

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
        if (line.empty()) continue; // Skip empty lines
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

        getline(ss, cell); // Read remaining line for tavg
    
    try {
        tmp.tavg = stod(cell);
    } catch (...) {
        tmp.tavg = 0.0; // Fallback for malformed data
    }

        interactions1.push_back(tmp);
}
    file.close();
}
void feedbacks(string feedbacks, std::vector<Interactions>& interactions1) {
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
    // 1. Create a Lookup Table for students: O(S)
    unordered_map<string, const Student*> studentMap;
    for (const auto& s : students) {
        studentMap[s.studentID] = &s;
    }

    for (auto& m : mentors) {
        double totalMilestones = 0, completedMilestones = 0;        // Initialize all the components to 0.
        double totalResponseTime = 0;
        double engagementSum = 0, feedbackSum = 0;
        int menteeCount = 0;

        for (const auto& i : interactions) {
            if (i.mentorID == m.mentorID) {
                menteeCount++;
                totalResponseTime += i.tavg;
                
                double engagementScore = (1.5 * i.meetings) + (1.5 * i.codeReview) + (0.5 * i.message);
                engagementSum += engagementScore;

                // Bias correction logic
                int multiplier = 1;
                if ((engagementScore < 15 && i.feedback >= 4) || (engagementScore > 45 && i.feedback <= 2)) {  
                    multiplier = 0;     // Trying to remove extreme cases biasness.
                }
                feedbackSum += multiplier * i.feedback;

                // 2. Optimized Student Lookup: O(1) instead of O(S)
                if (studentMap.count(i.studentID)) {
                    const Student* s = studentMap[i.studentID];
                    double n = s->milestonesCompleted;
                    double total = s->totalMilestones;
                    completedMilestones += n * (n + 1) / 2.0;
                    totalMilestones += total * (total + 1) / 2.0;
                }
            }
        }

        // Final Score Calculation
        m.P = (totalMilestones > 0) ? (completedMilestones / totalMilestones) : 0;    // 1. Progress Score (P)
        if (menteeCount > 0) {                    
            // 2. Responsiveness Score (R) using 1/(1+ e^2*(tavg - 2)).2 hours is taken as adequate response time.               
            double avgT = totalResponseTime / menteeCount; 
            m.R = 1.0 / (1.0 + exp(2.0 * (avgT - 2.0)));   
            // 3. Engagement Score (E) - Normalized per mentee
            // Assuming a 'high' engagement is 60 points per mentee for 1.0 score
            m.E = std::min(1.0, (engagementSum / menteeCount) / 60.0); 
            m.F = feedbackSum / (5.0 * menteeCount);   //4. Calculating feedback
        }
        //5. Calculating total sum using weighted score
        m.Finalscore = (0.25 * m.P) + (0.25 * m.R) + (0.3 * m.E) + (0.2 * m.F);
    }
}

void sortMentors(vector<Mentor>& mentors) { // Built-in sort using library-algorithm.
    if (mentors.empty()) return;

    std::sort(mentors.begin(), mentors.end(), [](const Mentor& a, const Mentor& b) {
        return a.Finalscore > b.Finalscore; // Descending order
    });

    // 2. Assign ranks with tie-handling (1-2-2-4 logic)
    int currentRank = 1;
    for (size_t i = 0; i < mentors.size(); i++) {
        // If it's not the first mentor AND the score is different from the previous one
        // The rank becomes the current index + 1 (to skip ranks)
        if (i > 0 && mentors[i].Finalscore < mentors[i - 1].Finalscore) {
            currentRank = i + 1;
        }
        
        mentors[i].rank = currentRank;
    }
}


//To write final CSV
void saveResults(const vector<Mentor>& mentors, const string& mentor_scores) {
    std::ofstream outFile(mentor_scores); // 1. Create/Open the output file

    // Check if the file opened successfully
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file " << mentor_scores << std::endl;
        return;
    }

    // 2. Write the Header Row so the CSV is readable
    outFile << "Rank,MentorID,Name,Final Score" << std::endl;

    // 3. Loop through the sorted vector and write each mentor's data
    for (const auto& m : mentors) {
        outFile << m.rank << "," 
                << m.mentorID << "," 
                << m.name << "," 
                << m.Finalscore << std::endl;
    }

    outFile.close(); // 4. Save and close
    std::cout << "Success: Results saved to " << mentor_scores << std::endl;
}


