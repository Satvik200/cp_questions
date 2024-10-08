#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Function for finding the end co-ordinates using the instructions vector
pair<int, int> simulatePath(const vector<string> &instructions) {
  int x = 0, y = 0;
  // 0: North, 1: East, 2: South, 3: West
  int direction = 0;

  for (const string &instruction : instructions) {
    if (instruction == "Left") {
      direction = (direction - 1 + 4) % 4;
    } else if (instruction == "Right") {
      direction = (direction + 1) % 4;
    } else if (instruction == "Forward") {
      switch (direction) {
      case 0: y++;  break;
      case 1: x++;  break;
      case 2: y--;  break;
      case 3: x--;  break;
      }
    }
  }

  return make_pair(x, y);
}

vector<string> find_error_instruction(int target_x, int target_y, int no_of_instr, vector<string> &instructions) {
  vector<string> answer;
  vector<string> possibilities = {"Left", "Right", "Forward"};

  for (int i = 0; i < no_of_instr; i++) {
    for (int k = 0; k < possibilities.size(); k++) {
      instructions[i] = possibilities[k];
      // we simulate whether we will reach the target destination or not
      pair<int, int> actualPosition = simulatePath(instructions);

      // if we reach, we have found our error instruction
      if (actualPosition.first == target_x &&
          actualPosition.second == target_y) {
        answer.push_back(to_string(i + 1));
        answer.push_back(instructions[i]);
        return answer;
      }
    }
  }
  return answer;
}

int main() {
  int target_x, target_y;
  int no_of_instr;
  vector<string> instructions;
  string temp;
  vector<string> answer;

  // input all the variables
  cin >> target_x >> target_y;
  cin >> no_of_instr;
  for (int i = 0; i < no_of_instr; i++) {
    cin >> temp;
    instructions.push_back(temp);
  }

  // call function for finding the error
  answer =
      find_error_instruction(target_x, target_y, no_of_instr, instructions);

  // print the error instruction
  if (!answer.empty()) {
    cout << "Answer: " << answer[0] << " " << answer[1] << endl;
  } else {
    cout << "Answer: "<< "No Error" << endl;
  }
}