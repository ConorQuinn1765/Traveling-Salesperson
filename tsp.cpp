#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <float.h>
#include "tsp.h"

Tsp::Tsp()
{
    head = NULL;
    numNodes = 0;
}

/**
 * @brief Destroy the Tsp object
 * Loops through the list of nodes
 * and deletes them as it goes.
 */
Tsp::~Tsp()
{
    Node* temp;
    while(head != NULL)
    {
        temp = head->next;
        delete head;
        head = temp;
    }
}

/**
 * @brief Call toString of every point
 * and output the result
 */
void Tsp::show()
{
    Node* temp = head;
    while(temp != NULL)
    {
        std::cout << temp->p.toString() << std::endl;
        temp = temp->next;
    }
}

/**
 * @brief Loop through every point in list and draw a
 * circle at the corresponding x,y position in window
 * 
 * @param window sfml window
 */
void Tsp::drawPoints(sf::RenderWindow& window)
{
    Node* temp = head;
    while(temp != NULL)
    {
        sf::CircleShape circle;
        circle.setRadius(2);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(temp->p.getX(), temp->p.getY());

        window.draw(circle);
        temp = temp->next;
    }
}

/**
 * @brief Loop through each point in list and draw
 * a line from the current point to the next point in
 * the list. At the end of the list draw a line back
 * to the starting point.
 * 
 * @param window sfml window
 */
void Tsp::drawTour(sf::RenderWindow& window)
{
    Node* temp = head;
    if(temp != NULL)
    {
        while(temp->next != NULL)
        {
            sf::Vertex line[] = 
            {
                sf::Vertex(sf::Vector2f(temp->p.getX(), temp->p.getY())),
                sf::Vertex(sf::Vector2f(temp->next->p.getX(), temp->next->p.getY()))
            };
            window.draw(line, 2, sf::Lines);
            temp = temp->next;
        }
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(temp->p.getX(), temp->p.getY())),
            sf::Vertex(sf::Vector2f(head->p.getX(), head->p.getY()))
        };
        window.draw(line, 2, sf::Lines);
    }
}

/**
 * @brief Loop through each point in list and
 * call distanceTo(nextPoint) on the point.
 * Add the new value to the total after each call
 * 
 * @return double total distance
 */
double Tsp::distance()
{
    double dist{0};
    Node* temp = head;

    if(temp != NULL)
    {
        while(temp->next != NULL)
        {
            dist += temp->p.distanceTo(temp->next->p);
            temp = temp->next;
        }
        dist += temp->p.distanceTo(head->p);
    }
    return dist;
}

/**
 * @brief If head is NULL create a new point and
 * make it the head. Otherwise create a new point
 * and add it to the end of the list.
 * 
 * @param p point to be added
 */
void Tsp::insertInOrder(Point p)
{
    Node* temp;
    if(head == NULL)
    {
        head = new Node(p);
        numNodes++;
        return;
    }

    temp = head;
    while(temp->next != NULL)
        temp = temp->next;

    temp->next = new Node(p);

    numNodes++;
}

/**
 * @brief Loops through each point in list and tracks
 * which point has the shortest euclidean distance 
 * between it and the point
 * 
 * @param p point to be inserted
 */
void Tsp::insertNearest(Point p)
{
    Node* minNode{NULL}, *temp, *newNode;
    double minDist{DBL_MAX};

    if(!head)
    {
        head = new Node(p);
        numNodes++;
        return;
    }

    temp = head;
    while(temp != NULL)
    {
        if(temp->p.distanceTo(p) < minDist)
        {
            minNode = temp;
            minDist = temp->p.distanceTo(p);
        }
        temp = temp->next;
    }

    newNode = new Node(p);
    newNode->next = minNode->next;
    minNode->next = newNode;

    numNodes++;
}

/**
 * @brief Loops through each point in the list and
 * keeps track of which index adds the smallest amount
 * to the total distance
 * 
 * @param p point to be inserted
 */
void Tsp::insertSmallest(Point p)
{
    Node* minNode, *newNode, *temp;
    double minDist{DBL_MAX};

    if(!head)
    {
        head = new Node(p);
        numNodes++;
        return;
    }

    newNode = new Node(p);

    temp = head;
    while(temp != NULL)
    {
        newNode->next = temp->next;
        temp->next = newNode;

        if(distance() < minDist)
        {
            minNode = temp;
            minDist = distance();
        }
        temp->next = newNode->next;
        newNode->next = NULL;
        temp = temp->next;
    }

    newNode->next = minNode->next;
    minNode->next = newNode;
    numNodes++;
}
