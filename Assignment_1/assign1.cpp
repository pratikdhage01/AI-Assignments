#include<iostream> 
#include<vector>        
#include<queue> 
#include<set>           
#include<string>        
#include<algorithm>     

using namespace std;

// Struct to represent the state of the puzzle
struct PuzzleState {
    vector<vector<int>> board;  
    string path;                
};


const vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}  
};


bool is_goal(const vector<vector<int>>& state) {
    return state == goal;
}

// Function to find the coordinates of the empty space (0)
pair<int,int> find_zero(const vector<vector<int>>& state) {
    for (int r = 0; r < 3; r++) {         
        for (int c = 0; c < 3; c++) {     
            if (state[r][c] == 0)         
                return {r, c};            
        }
    }
    return {-1, -1};  
}

// Converts the board to a string to store in visited set
string serialize(const vector<vector<int>>& state) {
    string s;
    for (auto &row : state)
        for (int val : row)
            s += to_string(val);  
    return s;
}

// Checks if a position is inside the 3x3 grid
bool is_valid(int r, int c) {
    return r >= 0 && r < 3 && c >= 0 && c < 3;
}

// Directions for moving the empty space: Up, Down, Left, Right
const vector<pair<int,int>> directions = {
    {-1, 0}, 
    {1, 0},  
    {0, -1}, 
    {0, 1}   
};


const vector<char> dir_chars = {'U', 'D', 'L', 'R'};

// Swaps the empty tile with a tile at new position to generate new board
vector<vector<int>> move_tile(const vector<vector<int>>& state, int r1, int c1, int r2, int c2) {
    vector<vector<int>> new_state = state;      
    swap(new_state[r1][c1], new_state[r2][c2]); 
    return new_state;                           
}


void print_board(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row) cout << val << " "; 
        cout << "\n";                           
    }
    cout << "\n";                               
}

// BFS algorithm 
void bfs_solver(const vector<vector<int>>& start) {
    queue<PuzzleState> q;           
    set<string> visited;            

    q.push({start, ""});            
    visited.insert(serialize(start)); 

    while (!q.empty()) {            
        PuzzleState current = q.front(); // Take the first state
        q.pop();

        if (is_goal(current.board)) {
            cout << "Goal reached! Moves: " << current.path << "\n";
            cout << "Final board:\n";
            print_board(current.board);
            return;
        }

        pair<int,int> zero_pos = find_zero(current.board);
        int zr = zero_pos.first;
        int zc = zero_pos.second;

        // Try all 4 directions (U, D, L, R)
        for (int i=0; i<directions.size(); i++) {
            int nr = zr + directions[i].first;   
            int nc = zc + directions[i].second;  

            if (is_valid(nr, nc)) {  // If move is inside the board
                // Generate new board by swapping zero
                vector<vector<int>> new_board = move_tile(current.board, zr, zc, nr, nc);

                
                string s = serialize(new_board);

                if (visited.find(s) == visited.end()) { // If new state is not visited
                    visited.insert(s);                 
                    q.push({new_board, current.path + dir_chars[i]}); 
                }
            }
        }
    }

   
    cout << "No solution found.\n";
}


int main() {
    
    vector<vector<int>> start = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    cout << "Starting BFS to solve 8-puzzle...\n";
    bfs_solver(start);  

    return 0;
}
