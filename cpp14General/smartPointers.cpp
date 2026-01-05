#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Sensor 
{
private:
    string name;
    int id;
public:
   Sensor(string n, int i) : name(n), id(i) 
   {
    cout << "Sensor" << name << " created\n";
   }

   ~Sensor() 
   {
    cout << "Sensor" << name << " destroyed\n";
   }

   void readData() 
   {
    cout << "Reading data from " << name << " ( ID " << id << " )\n"; 
   }
};

int main() 
{
    // unique ptr - exclusive membership
    unique_ptr<Sensor> sensor1 = make_unique<Sensor>("Temporary", 1);
    sensor1->readData();

    unique_ptr<Sensor> sensor2 = move(sensor1);

    // shared_ptr - shared ownership with reference count
    shared_ptr<Sensor> sensor3 = make_shared<Sensor>("Pressure", 2);
    cout << "Reference count: "  << sensor3.use_count() << "\n";

    {
        shared_ptr<Sensor> sensor4 = sensor3;
        cout << "Reference count: " << sensor3.use_count() << "\n";
        sensor4->readData();
    }

    cout << "Reference count:  " << sensor3.use_count() << "\n";

    weak_ptr<Sensor> weakSensor = sensor3;
    if (auto locked = weakSensor.lock()) {
        locked->readData();
        cout << "Weak pointer is valid\n";
    }

    return 0;
}