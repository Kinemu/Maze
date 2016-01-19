//
// Maze.hh for Maze in /home/mondol_a/Maze
//
// Made by audrey mondoloni
// Login   <mondol_a@epitech.net>
//
// Started on  Tue May 21 16:09:50 2013 audrey mondoloni
// Last update Sun Apr 13 15:51:50 2014 audrey mondoloni
//

#ifndef     MAZE_HH
# define    MAZE_HH

/*!
 * \file Maze.hh
 * \brief Program which generates a perfect maze.
 * \author Audrey Mondoloni (mondol_a)
 * \date 30 May 2013
 */

#include <vector>
#include <utility>

class Maze
{
    typedef std::pair<int, int> MazePair;
    typedef std::vector<MazePair> MazeVector;

public:
    Maze();
    Maze(int size_x,int size_y);
    ~Maze();

public:
    void defaultMaze(const unsigned short level);
    void initMaze(const unsigned short level);
    int  getHeight(void) const;
    char **getMaze(void) const;
    MazeVector getPath(void) const;
    int  getWidth(void) const;
    void printMaze(void) const;

private:
    void borderMap(void);
    char checkNSEO(const MazePair &point) const;
    bool checkNSEO(const int x, const int y) const;
    void deleteTab(const unsigned short add);
    void fillIt(char c);
    bool makeMaze(void);
    void putWall(const unsigned short level);

private:
    MazeVector coords;
    char **maze;
    int _size_x;
    int _size_y;
};

#endif      /* !MAZE_HH */