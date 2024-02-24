// This Homework was completed by Aaron Kern and worked on with Marty Mullen
// ChatGPT was used for debugging, when I was very confused(7&8), and for organzing the main file 
//   which was then separated into separate question files

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

class Plane;
// Question 6
class Pilot
    {
    private:
        std::string name;
        Plane* myPlane;

    public:
        Pilot(const std::string& pilotName, Plane* planePtr)
            : name(pilotName), myPlane(planePtr)
            // Prints out "Pilot ___ is at the gate, ready to board the plane. Memory Address: ____"
        {
            std::cout << "Pilot" << name << " is at the gate, ready to board the plane. Memory Address: " << myPlane << std::endl;
        }
        // Prints out "Pilot ____ is out of the plane."
        ~Pilot()
        {
            std::cout << "Pilot" << name << " is out of the plane." << std::endl;
        }
        // getter for name of specific pilot
        std::string getName() const
        {
            return name;
        }
        // function to control the plane
        void controlPlane(double timestep, int maxIterations);
    };


class Plane
    {
    private:
        double pos;
        double vel;
        double distance;
        std::string origin;
        std::string destination;

    public:
        Plane(const std::string& from, const std::string& to, double planeSpeed)
        {
            pos = 0;
            vel = planeSpeed;
            distance = 0;
            origin = from;
            destination = to;
        }
        // getter for position
        double getPos() const
        {
            return pos;
        }

        void operate(double dt)
        {
            pos += vel * dt;

            if (pos <= 0)
            {
                pos = 0;
            }

            if (pos == 0)
            {
                std::cout << "Plane landed at SCE. Memory address: " << this << std::endl;
            }
        }
    };

void Pilot::controlPlane(double timestep, int maxIterations)
    {
        for (int i = 0; i = maxIterations; ++i)
        {
            std::cout << "Pilot " << name << " controlling the plane at memory address: " << myPlane << std::endl;
            myPlane->operate(timestep);

            if (myPlane->getPos() == 0)
            {
                break;
            }
        }
        
    }

int main()
    {
        Plane ("SCE", "PHL", 450);
        std::shared_ptr<Pilot> pilot1 = std::make_shared<Pilot>("Pilot-in-Command", &plane);
        std::shared_ptr<Pilot> pilot2 = std::make_shared<Pilot>("Co-Pilot", &plane);
// values gotten from question 5
        double timestep = 50;
        int maxIterations = 1000; 

        while (true) 
        {
        // Pilot in Command flies plane to destination and back to SCE
            pilot1->controlPlane(timestep, maxIterations);
            std::cout << "Plane is at SCE" << std::endl;
        // Co-Pilot flies plane to destination and back to SCE
            pilot2->controlPlane(timestep, maxIterations);
            std::cout << "Plane is at SCE" << std::endl;

            plane = Plane("SCE", "PHL", 450);
        // swap pilots
            std::swap(pilot1, pilot2);

        }

        return 0;
    }
