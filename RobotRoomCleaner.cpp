/*
Given a robot cleaner in a room modeled as a grid.

Each cell in the grid can be empty or blocked.

The robot cleaner with 4 given APIs can move forward, turn left or turn right. Each turn it made is 90 degrees.

When it tries to move into a blocked cell, its bumper sensor detects the obstacle and it stays on the current cell.

Design an algorithm to clean the entire room using only the 4 given APIs shown below.

interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
Example:

Input:
room = [
  [1,1,1,1,1,0,1,1],
  [1,1,1,1,1,0,1,1],
  [1,0,1,1,1,1,1,1],
  [0,0,0,1,0,0,0,0],
  [1,1,1,1,1,1,1,1]
],
row = 1,
col = 3

Explanation:
All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.
Notes:

The input is only given to initialize the room and the robot's position internally. You must solve this problem "blindfolded". In other words, you must control the robot using only the mentioned 4 APIs, without knowing the room layout and the initial robot's position.
The robot's initial position will always be in an accessible cell.
The initial direction of the robot will be facing up.
All accessible cells are connected, which means the all cells marked as 1 will be accessible by the robot.
Assume all four edges of the grid are all surrounded by wall.
*/
/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */
class Solution {
private:
    static const int DOWN = 0;
    static const int UP = 1;
    static const int LEFT = 3;
    static const int RIGHT = 4;

    std::unordered_set<std::string> seen;
    int direction;

    std::string get_cell(const int i, const int j) {
        return std::to_string(i) + "$" + std::to_string(j);
    }

    void turn_up(Robot& robot) {
        if (direction == RIGHT) {
            robot.turnLeft();
        } else if (direction == LEFT) {
            robot.turnRight();
        } else if (direction == DOWN) {
            robot.turnRight();
            robot.turnRight();
        }
        direction = UP;
    }

    void turn_left(Robot& robot) {
        if (direction == UP) {
            robot.turnLeft();
        } else if (direction == DOWN) {
            robot.turnRight();
        } else if (direction == RIGHT) {
            robot.turnRight();
            robot.turnRight();
        }
        direction = LEFT;
    }

    void turn_right(Robot& robot) {
        if (direction == UP) {
            robot.turnRight();
        } else if (direction == DOWN) {
            robot.turnLeft();
        } else if (direction == LEFT) {
            robot.turnRight();
            robot.turnRight();
        }
        direction = RIGHT;
    }

    void turn_down(Robot& robot) {
        if (direction == LEFT) {
            robot.turnLeft();
        } else if (direction == RIGHT) {
            robot.turnRight();
        } else if (direction == UP) {
            robot.turnRight();
            robot.turnRight();
        }
        direction = DOWN;
    }
    
    void recurse1(Robot& robot, const int i, const int j) {
        const auto cell = get_cell(i, j);
        if (seen.count(cell)) {
            return;
        }
        seen.insert(cell);
        turn_up(robot);
        if (robot.move()) {
            recurse1(robot, i-1, j);
            turn_down(robot);
            robot.move();
        }
        turn_right(robot);
        if (robot.move()) {
            recurse1(robot, i, j+1);
            turn_left(robot);
            robot.move();
        }
        turn_down(robot);
        if (robot.move()) {
            recurse1(robot, i+1, j);
            turn_up(robot);
            robot.move();
        }
        turn_left(robot);
        if (robot.move()) {
            recurse1(robot, i, j-1);
            turn_right(robot);
            robot.move();
        }
        robot.clean(); 
    }

    void solution1(Robot& robot) {
        seen.clear();
        direction = UP;
        recurse1(robot, 0, 0);     
    }
public:
    void cleanRoom(Robot& robot) {
        solution1(robot);       
    }
};
