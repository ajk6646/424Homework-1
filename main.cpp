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

/*----------------------------------------------------------Question 3---------------------------------------------------------------*/
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;

public:
    Plane(const std::string from, const std::string to, std::map<std::pair<std::string, std::string>, int> flightDistances)
    {
        origin = from;
        destination = to;
        if (origin == "SCE" && destination == "PHL" || origin == "PHL" && destination == "SCE")
        {
            distance = flightDistances[{"SCE", "PHL"}];
            cout << "The total trip miles is " << distance << endl;
        }
        else if (origin == "SCE" && destination == "ORD" || origin == "ORD" && destination == "SCE")
        {
            distance = flightDistances[{"SCE", "ORD"}];
            cout << "The total trip miles is " << distance << endl;
        }
        else if (origin == "SCE" && destination == "EWR" || origin == "EWR" && destination == "SCE")
        {
            distance = flightDistances[{"SCE", "EWR"}];
            cout << "The total trip miles is " << distance << endl;
        }
        else
        {
            cout << "Not a valid input" << endl;
        }
        pos = 0;
        vel = 0;
        if (to == "SCE")
        {
            at_SCE = 0;
        }
        else
        {
            at_SCE = 1;
        }
        cout << "Plane created at " << this << endl;
    }

    ~Plane() {
        cout << "Plane Destroyed.";
    }

    void operate(double dt) {
        if (pos < distance)
        {
            pos += vel * dt;
            at_SCE = 0;
        }
        else
        {
            if (destination == "SCE")
            {
                at_SCE = 1;

                swap(origin, destination);
                pos = 0.0;
            }
            else
            {
                swap(origin, destination);
                pos = 0.0;
            }
        }
    }

    double getPos() {
        return pos;
    }

    std::string getOrigin() {
        return origin;
    }

    std::string getDestination() {
        return destination;
    }

    double getDistance()
    {
        return distance;
    }

    bool isAtSCE() {
        return at_SCE;
    }

    double getVel() {
        return vel;
    }

    void setVel(double velocity) {
        vel = velocity;
    }
};



int main()
{

    /*----------------------------------------------------------Question 1---------------------------------------------------------------*/
       // defining variables (units are commented afterwards)
    double EmptyWeight, usableFuelPerGallon, baggageWeight; //Pounds
    int FrontSeat, RearSeat; //Unitless
    double EmptyWeightMoment; //Pounds-inches
    double FrontSeatMomentArm, RearSeatMomentArm, FuelMomentArm, BaggageMomentArm; //Inches
    double UsableFuel; //Gallons

    double maxGrossWeight = 2950;  //Pounds
    double forwardCGLim = 82.1;  //Inches
    double aftCGLLim = 84.7; //inches

    cout << "Enter airplane empty weight (pounds): ";
    cin >> EmptyWeight;
    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> EmptyWeightMoment;
    cout << "Enter number of front seat occupants: ";
    cin >> FrontSeat;

    // Array to store weights of front seat occupants
    vector<double> frontSeatWeights(FrontSeat);
    double totalFrontWeight = 0;

    for (int i = 0; i < FrontSeat; ++i) {
        std::string iString = std::to_string(i + 1);
        cout << "Enter weight of front seat occupant " + iString + " (pounds): ";
        cin >> frontSeatWeights[i];
        totalFrontWeight = totalFrontWeight + frontSeatWeights[i];
    }

    cout << "Enter front seat moment arm (inches): ";
    cin >> FrontSeatMomentArm;
    cout << "Enter number of rear seat occupants: ";
    cin >> RearSeat;

    // Array to store weights of rear seat occupants
    vector<double> rearSeatWeights(RearSeat);
    double totalRearWeight = 0;
    for (int i = 0; i < RearSeat; ++i) {
        std::string iString = std::to_string(i + 1);
        cout << "Enter weight of each rear seat occupant " + iString + " (pounds): ";
        cin >> rearSeatWeights[i];
        totalRearWeight = totalRearWeight + rearSeatWeights[i];
    }

    cout << "Enter rear seat moment arm (inches): ";
    cin >> RearSeatMomentArm;
    cout << "Enter number of gallons of usable fuel: ";
    cin >> UsableFuel;
    cout << "Enter usable fuel weight per gallon (pounds): ";
    cin >> usableFuelPerGallon;
    cout << "Enter fuel tank moment arm (inches): ";
    cin >> FuelMomentArm;
    cout << "Enter baggage weight (pounds): ";
    cin >> baggageWeight;
    cout << "Enter baggage moment arm (inches): ";
    cin >> BaggageMomentArm;

    double usableFuelWeight = UsableFuel * usableFuelPerGallon;


    double totalWeight = EmptyWeight + totalFrontWeight + totalRearWeight + usableFuelWeight + baggageWeight;

    double totalMoment = EmptyWeightMoment + totalFrontWeight * FrontSeatMomentArm + totalRearWeight * RearSeatMomentArm
        + usableFuelWeight * FuelMomentArm + baggageWeight * BaggageMomentArm;

    cout << "\n";

    if (totalWeight > maxGrossWeight || totalMoment < forwardCGLim || totalMoment > aftCGLLim) {
        double fuelAdjustment = 0.0;

        cout << "The aircraft is out of design limits.\n";
        cout << "The old total weight was (pounds): " << fixed << setprecision(2) << totalWeight << endl;
        cout << "The old C.G. location  was (inches): " << fixed << setprecision(2) << totalMoment / totalWeight << endl;
        cout << "\n";
        if (totalWeight > maxGrossWeight) {
            fuelAdjustment = (totalWeight - maxGrossWeight) / usableFuelPerGallon;
        }
        double newGrossWeight = totalWeight - fuelAdjustment * usableFuelPerGallon;
        double newCGLocation = totalMoment / newGrossWeight;

        cout << "The aircraft new design limits are as follows.\n";
        cout << "Required fuel adjustment (gallons): " << fixed << setprecision(2) << fuelAdjustment << endl;
        cout << "New gross weight (punds): " << fixed << setprecision(2) << newGrossWeight << endl;
        cout << "New C.G. location (inches): " << fixed << setprecision(2) << newCGLocation << endl;
    }
    else {
        cout << "The aircraft is within design limits.\n";
        cout << "Gross weight (pounds): " << fixed << setprecision(2) << totalWeight << endl;
        cout << "C.G. location (inches): " << fixed << setprecision(2) << totalMoment / totalWeight << endl;
    }



    /*---------------------------------------------------Question 2-------------------------------------------------------------------*/
    std::map<std::pair<std::string, std::string>, int> flightDistances;

    // Each flight distance dictated from the map
    flightDistances[{"SCE", "PHL"}] = 160;
    flightDistances[{"SCE", "ORD"}] = 640;
    flightDistances[{"SCE", "EWR"}] = 220;



    /*---------------------------------------------------Question 5------------------------------------------------------------------*/

    std::string from;
    std::string to;
    cout << "Please enter a starting airport(SCE, EWR, PHL, or ORD):  ";
    cin >> from;
    cout << "Please enter a destination airport(SCE, EWR, PHL, or ORD): ";
    cin >> to;
    Plane plane(from, to, flightDistances);

    double placeHolder = 0;
    cout << "Please enter a flight speed: (mph) ";
    cin >> placeHolder;
    placeHolder = placeHolder / 3600;

    plane.setVel(placeHolder);

    double timestep = 10;
    double iterations = 1000;
    double position = 0.0;
    int time = 0;
    double distance = plane.getDistance();
    for (int i = 0; i < iterations; ++i) {
        if (distance - position > 0)
        {
            plane.operate(timestep);
            position = plane.getPos();
            time += timestep;
            cout << "Time: " << time << " seconds, Position: " << position << " miles." << endl;
        }
        else
        {
            break;
        }
    }
}
/*--------------------------------------------------------------Question 6/7--------------------------------------------------------------------*/
    
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
        Plane plane("SCE", "PHL", 450);

        std::shared_ptr<Pilot> pilot1 = std::make_shared<Pilot>("Pilot-in-Command", &plane);
        std::shared_ptr<Pilot> pilot2 = std::make_shared<Pilot>("Co-Pilot", &plane);

        double timestep = 50;
        int maxIterations = 10; // should be 1000 as in question 5, reduced for easier/smoother tests of code

        while (true) {
            pilot1->controlPlane(timestep, maxIterations);
            std::cout << "Plane is at SCE" << std::endl;

            pilot2->controlPlane(timestep, maxIterations);
            std::cout << "Plane is at SCE" << std::endl;

            plane = Plane("SCE", "PHL", 450);

            std::swap(pilot1, pilot2);

        }

        return 0;
    }

/*-------------------------------------------------------------------Question 8-----------------------------------------------------------------*/
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

        double timestep = 50;
        int maxIterations = 10; // should be 1000 as in question 5, reduced for easier/smoother tests of code


        while (true) {
            pilot1->controlPlane(timestep, maxIterations);
            std::cout << "Plane is at SCE" << std::endl;

            pilot2->controlPlane(timestep, maxIterations);
            std::cout << "Plane is at SCE" << std::endl;

            plane = std::make_shared<Plane>("SCE", "PHL", 450);

            std::swap(pilot1, pilot2);

        }

        return 0;
    }
