#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string.h>
#include "tsp.h"

using std::cin;
using std::cout;
using std::endl;

typedef enum {inOrder, nearest, smallest}InsertMethod;

/**
 * @brief Reads in points from stdin and adds them
 * into the tsp object using the 
 * 
 * @param t reference to Tsp object
 * @param N number of points in tour
 * @return double time taken to calculate the tour
 */
double calculateTour(Tsp& t, int N, InsertMethod method);

/**
 * @brief Reads in the size of the window and the number of
 * points in the given tour. Then it calculates the tour and
 * displays it in an sfml window, or if the option to animate
 * the program has been selected it will display the tour as
 * it is being calculated.
 * 
 * @param argc number of command line arguments
 * @param argv option of passing 'a' to animate the program
 * @return int 
 */
int main(int argc, char* argv[])
{
    Tsp t;
    int width, height, N;
	double time{0};

    cin >> width;
    cin >> height;
    cin >> N;

	if(argc < 2 || strncmp(argv[1], "a", 2) != 0)
		time = calculateTour(t, N, nearest);

    sf::RenderWindow window(sf::VideoMode(width, height), "Traveling Salesman");
    sf::Event event;
    sf::View view(sf::Vector2f(width / 2, -height / 2), sf::Vector2f(width, height));
    window.setView(view);
    
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(t.size() == 0 && strncmp(argv[1], "a", 2) == 0)
        {
			clock_t start, end;
            start = clock();

            for(int i = 0; i < N; i++)
            {
				double x, y;
                cin >> x;
                cin >> y;

                Point p(x, y);
                t.insertSmallest(p);

                window.clear(sf::Color::Black);
                t.drawTour(window);
                window.display();
            }
            end = clock();
			time = (1.0* end - start) / CLOCKS_PER_SEC;
        }
		window.clear(sf::Color::Black);
        t.drawTour(window);
        window.display();
    }
    
    cout << "Distance of tour: " << t.distance() << endl;
    cout << "Number of points: " << t.size() << endl;
    cout << "Time to calculate tour: " << std::fixed << std::setprecision(2) 
		 << time << " seconds" << endl;
    return 0;
}

double calculateTour(Tsp& t, int N, InsertMethod method)
{
	clock_t start, end;
	start = clock();

    for(int i = 0; i < N; i++)
    {
		double x, y;
        cin >> x;
        cin >> y;

        Point p(x, y);
        switch(method)
        {
        case inOrder:
            t.insertInOrder(p);
            break;
        case nearest:
            t.insertNearest(p);
            break;
        case smallest:
            t.insertSmallest(p);
            break;
        }
    }
    end = clock();

	return (1.0 * end - start) / CLOCKS_PER_SEC;
}
