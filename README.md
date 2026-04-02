# Mentor Scoring System
Designed to evaluate the performance of mentors in WnCC's Season of Code using C++.

## Prerequisites
Before running this project, ensure you have a C++ compiler (supporting C++17) and `make` installed. See `requirements.txt` for details.

## How to Build and Run
Open your terminal in the project folder and run the following commands:

```bash
# Clone the repository (replace with your actual URL)
git clone <your-repo-link>
cd <repo-folder>

# Build the project using the Makefile
Type `make build` to compile

# Execute the program
Type `make run` to execute and run the program.

# To remove the compiled executable and temporary files
Type `make clean`

 ## Project Structure
 - `main.cpp`: Contains the calling of functions to calculate score and file handling.
 - `mentors.csv` : Input data for mentors.
 - `feedbacks.csv` : Input data for feedbacks of mentors.
 - `interactions.csv` : Input data for interactions between mnetors and mentees.
 - `students.csv` : Input data for mentees.
 - `mentors_scores.csv` : The generated output file.
 - `mentor.h` : Contains the declarations for the functions to calculate scores.
 - `mentor.cpp` : Contains the definition for the functions used.
 - `Makefile` : Script to automate compilation and execution.
 - `requirements.txt` : List of System Dependencies.
