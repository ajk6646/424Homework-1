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

class Pilot
    {
    private:
        std::string name;
        std::shared_ptr<Plane> myPlane;

    public:
        Pilot(const std::string& pilotName, std::shared_ptr<Plane> planePtr)
            : name(pilotName), myPlane(planePtr)
            // Prints out "Pilot ___ is at the gate, ready to board the plane. Memory Address: ____"
        {
            std::cout << "Pilot" << name << " is at the gate, ready to board the plane. Memory Address: " << planePtr << std::endl;
        }
        // Prints out "Pilot ____ is out of the plane."
        ~Pilot()
        {
            std::cout << "Pilot" << name << " is out of the plane." << std::endl;
        }

        std::string getName() const
        {
            return name;
        }

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

        ~Plane()
        {}

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
        for (int i = 0; i < maxIterations; ++i)
        {
            std::cout << "Pilot " << name << " controlling the plane at memory address: " << myPlane.get() << std::endl;
            myPlane->operate(timestep);

            if (myPlane->getPos() == 0)
            {
                break;
            }
        }
    }

int main()
    {
        auto plane = std::make_shared<Plane>("SCE", "PHL", 450);
        auto pilot1 = std::make_shared<Pilot>("Pilot-in-Command", plane);
        auto pilot2 = std::make_shared<Pilot>("Co-Pilot", plane);
// values used from question 5
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

            plane = std::make_shared<Plane>("SCE", "PHL", 450);
            // switch pilots
            std::swap(pilot1, pilot2);

        }

        return 0;
    }
