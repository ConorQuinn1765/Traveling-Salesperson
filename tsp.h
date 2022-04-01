#ifndef TSP_H
#define TSP_H
#include <SFML/Graphics.hpp>
#include "point.h"

struct Node
{
	Point p;
    Node* next;

	Node() : p(Point(0, 0)), next(NULL) {}
	Node(Point a) : p(a), next(NULL) {}
};

class Tsp
{
 public:
	/**
	 * @brief Construct a new Tsp object
	 */
	Tsp();

	/**
	 * @brief Destroy the Tsp object
	 */
	~Tsp();

	/**
	 * @brief Output string format of each point
	 */
	void show();

	/**
	 * @brief Draw every point to specified window
	 * 
	 * @param window sfml window
	 */
	void drawPoints(sf::RenderWindow& window);

	/**
	 * @brief Draw every point and the connections
	 * between them
	 * 
	 * @param window sfml window
	 */
	void drawTour(sf::RenderWindow& window);

	/**
	 * @brief return the total number of points
	 * 
	 * @return int 
	 */
	inline int size() {return numNodes;}

	/**
	 * @brief Calculates the distance of the tour
	 * 
	 * @return double 
	 */
	double distance();

	/**
	 * @brief Insert each point in the order it was read
	 * 
	 * @param p point to insert
	 */
	void insertInOrder(Point p);

	/**
	 * @brief Insert each point at the place which
	 * has the smallest euclidean distance between
	 * p and the point before it
	 * 
	 * @param p point to be inserted
	 */
	void insertNearest(Point p);

	/**
	 * @brief Insert each point at the place which
	 * causes total distance to go up the least
	 * 
	 * @param p point to be inserted
	 */
	void insertSmallest(Point p);

 private:
	Node* head;
	unsigned numNodes;
};

#endif