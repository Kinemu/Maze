//
// Maze.cpp for Maze in /home/mondol_a/Maze
//
// Made by audrey mondoloni
// Login   <mondol_a@epitech.net>
//
// Started on  Tue May 21 16:07:01 2013 audrey mondoloni
// Last update Sun Apr 13 15:52:06 2014 audrey mondoloni
//

/*!
 * \file Maze.cpp
 * \brief Program which generates a perfect maze.
 * \author Audrey Mondoloni (mondol_a)
 * \date 30 May 2013
 *
 * This program generate mazes in ascii form. x symbolizes a breakable wall,
 * whereas o represents an unbreakable one. The borders of the maze are made
 * of o (unbreakable walls).
 *
 * The mazes generated are perfect mazes. It means you can go in any point from
 * any other point : there are neither closed circuits nor inaccesible areas.
 *
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "Maze.hh"

/*!
 * \fn void borderMap(void)
 * \brief Function which makes the borders of the maze.
 *
 * This function makes the border of the maze with unbreakable walls.
 *
 */

void Maze::borderMap(void)
{
  char **mappy;
  int x = _size_x + 3;
  int y = _size_y + 2;
  int i = 1;

  mappy = new char *[x];

  while (i <= _size_x)
    {
      mappy[i] = new char[y + 1];
      memset(mappy[i], 0, y);
      mappy[i][0] = 'o';

      strcat(mappy[i], maze[i - 1]);
      mappy[i][y - 1] = 'o';
      mappy[i][y] = '\0';
      ++i;
    }

  mappy[0] = new char[y + 1];
  memset(mappy[0], 'o', y);
  mappy[0][y] = '\0';

  mappy[x - 2] = new char[y + 1];
  memset(mappy[x - 2], 'o', y);
  mappy[x - 2][y] = '\0';

  deleteTab(0);
  maze = mappy;
}

/*!
 * \fn char checkNSEO(const MazePair &point) const
 * \brief Function which return a random possible direction to make a path.
 * \param point : The point which cardinal points will be analyzed.
 * \return : A random possible direction to make a new path, or null if there
 * isn't.
 *
 * This function will find all the directions where a new path can be made.
 * It will return a random direction between the ones found.
 *
 */

char Maze::checkNSEO(const MazePair &point) const
{
  int i = 0;
  char axis[4];
  const int first = point.first;
  const int second = point.second;

  if (first > 0 && checkNSEO(first - 1, second))
    axis[i++] = 'N';
  if (first < _size_x - 1 && checkNSEO(first + 1, second))
    axis[i++] = 'S';
  if (second < _size_y - 1 && checkNSEO(first, second + 1))
    axis[i++] = 'E';
  if (second > 0 && checkNSEO(first, second - 1))
    axis[i++] = 'O';

  return i > 0 ? axis[std::rand() % i] : 0;
}

/*!
 * \fn bool checkNSEO(const int x, const int y) const
 * \brief Function which determines if the point (x, y) is connected with
 * only one path.
 * \param x : The point's row.
 * \param y : The point's column.
 * \return : true if the point is connected with only one path, false otherwise.
 *
 * This function help knowing if a o (wall) can be replaced by a '.' (path).
 * It can be one and only one path to make this maze perfect. So if the number
 * of paths connected to this point exceeds 1 (Or if the point is a path
 * already), this function will return false, thus, the point will not be
 * created.
 *
 */

bool Maze::checkNSEO(const int x, const int y) const
{
  int i = 0;

  if (maze[x][y] == '.')
    return false;

  if (x > 0 && maze[x - 1][y] == '.')
    ++i;
  if (x < _size_x - 1 && maze[x + 1][y] == '.')
    ++i;
  if (y < _size_y - 1 && maze[x][y + 1] == '.')
    ++i;
  if (y > 0 && maze[x][y - 1] == '.')
    ++i;

  return i == 1;
}

/*!
 * \fn void defaultMaze(void)
 * \brief Default maze creator.
 * \param level : Indicates the chances for a wall to become breakable.
 *
 * This function creates the default Bomberman's maze.
 * The "maze" can't be made properly if the coordinates aren't odd, so in case
 * they're even, they're automatically incremented.
 * The level param permits the random generation of breakable walls. The
 * breakable walls are placed on an empty point ('.'), never on 'o'
 * (Unbreakable walls).
 * The chances of an empty point to become a breakable wall is 1 out of level.
 *  Thus, if level equals 1 or 0, it will automatically consider that no
 *  breakable wall must be erected (:DDD).
 *
 */

void Maze::defaultMaze(const unsigned short level)
{
  int random;

  fillIt('.');
  int x = 0;
  while (x < _size_x)
    {
      int y = 0;
      while (y < _size_y)
        {
	  (y % 2) && (x % 2) && x ? maze[x][y] = 'o' : 0;
	  if (!(maze[x][y] == 'o' || level < 1 || (random = rand() % level)))
	    maze[x][y] = 'x';
	  ++y;
        }
      ++x;
    }

  borderMap();
}

/*!
 * \fn void deleteTab(void)
 * \brief This function deletes the maze's table.
 * \param add : additional lines which will be deleted.
 *
 * This function makes a loop to delete each string of the maze's table.
 * It can delete x elements in addition of _size_x in case the user
 * wants to delete the borders.
 *
 */

void Maze::deleteTab(const unsigned short add)
{
  int i = 0;
  int x = _size_x + add;

  while (i < x)
    delete [] maze[i++];
  delete [] maze;
}

/*!
 * \fn void fillIt(char c)
 * \brief This function creates and fills the maze's table with the
 * character c.
 * \param c : The character the maze's table will be filled with.
 *
 * This fonction creates a new "empty" maze filled with the c character.
 * If c's NULL, it is automatically switched to the 'o' character by default.
 *
 */

void Maze::fillIt(char c)
{
  int x = 0;

  c ? 0 : c = 'o';
  maze = new char *[_size_x + 1];
  while (x < _size_x)
    {
      maze[x] = new char[_size_y + 1];
      memset(maze[x], c, _size_y);
      maze[x][_size_y] = '\0';
      ++x;
    }
}

/*!
 * \fn int getHeight(void) const
 * \brief Function which returns the maze's height.
 * \return _size_x : The maze's column size.
 *
 * This function will return the current height of the Maze Object.
 * This is useful as the variable _size_y is private.
 *
 */

int Maze::getHeight(void) const
{
  return _size_y;
}

/*!
 * \fn char ** getMaze(void) const
 * \brief Function which returns the maze.
 * \return maze : The current maze.
 *
 * This function will return the current maze of the Maze Object.
 * This is useful as the variable maze is private.
 *
 */

char **Maze::getMaze(void) const
{
  return maze;
}

/*!
 * \fn MazeVector (std::vector<std::pair<int,int> >) getPath const
 * \brief Function which returns the maze's path.
 * \return path : The maze's path.
 *
 * This function will return the maze's path of the Maze Object.
 * This is useful as the variable path is private.
 *
 */

Maze::MazeVector Maze::getPath(void) const
{
  MazeVector path;

  int x = 0;
  while (x < getWidth() + 2)
    {
      int y = 0;
      while (y < getHeight() + 2)
        {
	  if (maze[x][y] == '.')
	    path.push_back(std::make_pair<int, int>(x, y));
	  ++y;
        }
      ++x;
    }

  return path;
}

/*!
 * \fn int getWidth(void) const
 * \brief Function which returns the maze's width.
 * \return _size_x : The maze's row size.
 *
 * This function will return the current width of the Maze Object.
 * This is useful as the variable _size_x is private.
 *
 */

int Maze::getWidth(void) const
{
  return _size_x;
}

/*!
 * \fn void initMaze(const int level)
 * \brief Function which initializes the maze and its first point.
 * \param level : indicates the chances for a wall to become breakable for the
 * putWall function.
 *
 * This function makes the first '.' (path) on the maze. It will also call
 * the main functions to make the maze. Everything starts and ends here.
 *
 */

void Maze::initMaze(const unsigned short level)
{
  fillIt(0);

  int x = std::rand() % (_size_x);
  int y = std::rand() % (_size_y);

  coords.push_back(std::make_pair(x, y));
  maze[x][y] = '.';

  while (makeMaze());
  putWall(level);
  borderMap();
}

/*!
 * \fn char bool makeMaze(void)
 * \brief Function which makes a new path in the maze, and add this point to the
 * pair vector coords.
 * \return : true if there are other paths to make, false otherwise.
 *
 * This function will put the '.' (paths) on the maze's table.
 * It will simply makes the maze paths and fills a pair vector with the
 * coordinates of the point (x, y).
 * It will send to checkNSEO a point which at least one of
 * its cardinal points can become a possible path.
 * If it is possible, makeMaze put the '.' (path) on the maze and add new
 * coordinates to the pair vector.
 * It deletes the vector's points with no cardinal points possibly
 * becoming a path. If the vector's empty, it means all the possible paths were
 * created : then, it returns false.
 * This function is not a recursive one, because it calls itself so much than
 * the stack implodes (Stack Overflow), so the function initMaze calls
 * it within a loop.
 *
 */

bool Maze::makeMaze(void)
{
  char c;

  while (!coords.empty() && !(c = checkNSEO(coords.back())))
    coords.pop_back();

  if (coords.empty())
    return false;

  const MazePair &coord = coords.back();
  int x = coord.first;
  int y = coord.second;

  if (c == 'N')
    --x;
  else if (c == 'S')
    ++x;
  else if (c == 'E')
    ++y;
  else if (c == 'O')
    --y;

  coords.push_back(std::make_pair(x, y));
  maze[x][y] = '.';
  return true;
}

/*!
 * \fn void printMaze(void) const
 * \brief Function which shows the finished maze.
 *
 * This function will loop on the maze table to show its strings one per one.
 * It will show the entire maze, with its border (that's why we add 2 to
 * _size_x : to show the borders).
 *
 */

void Maze::printMaze(void) const
{
  int i = 0;

  while (i < _size_x + 2)
    std::cout << maze[i++] << std::endl;
}

/*!
 * \fn void putWall(const int level)
 * \brief Function which transforms some unbreakable walls in breakable ones.
 * \param level : 1/level chances to make a breakable wall. When
 * equals 1, all walls are breakables.
 *
 * This function will scan the maze table to find out the o and make it become
 * a x (breakable wall).
 * A wall becomes breakable if the random number % level equals 0.
 * Thus, there will be 1 chance out of level to the wall to become breakable.
 *
 */

void Maze::putWall(const unsigned short level)
{
  int x = 0;
  int y = 0;
  while (x < _size_x)
    {
      while (y < _size_y)
        {
	  if (maze[x][y] == 'o' && level > 1)
            {
	      short rand = std::rand() % level;
	      if (!rand)
		maze[x][y] = 'x';
            }
	  ++y;
        }
      y = 0;
      ++x;
    }
}

/*!
 * \brief Maze's Constructor
 *
 * This constructor will create a 1024*1024 default maze.
 *
 */

Maze::Maze() : _size_x(1024), _size_y(1024)
{
  srand(time(0) * getpid());
}

/*!
 * \brief Maze's Constructor
 * \param size_x : Maze's number of rows.
 * \param size_y : Maze's number of columns.
 *
 * This constructor will create a size_x * size_y maze.
 *
 */

Maze::Maze(int size_x, int size_y) : _size_x(size_x), _size_y(size_y)
{
  srand(time(0) * getpid());
}

/*!
 * \brief Maze's Destructor
 *
 * This destructor will call the deleteTab func to delete the maze
 * (It gives it "2" in argument in order to delete the borders).
 *
 */

Maze::~Maze()
{
  deleteTab(2);
}

int		main(int ac, char **av)
{
  Maze		*newMaze;
  if (ac > 2)
    newMaze = new Maze(atoi(av[1]), atoi(av[2]));
  else
    newMaze = new Maze;
  newMaze->initMaze(0);
  newMaze->printMaze();
  delete newMaze;
}