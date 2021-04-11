#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

enum class PClass{
    Upper = 1,
    Middle = 2,
    Lower = 3,
    NoInfo
};

enum class Sex{
    Male,
    Female,
    NoInfo
};

enum class PassengerField{
    Id,
    Survived,
    PClass,
    Name,
    Sex,
    Age,
    Sibsp,
    Parch,
    Ticket,
    Fare,
    Cabin,
    Embarked
};

struct Passenger
{
    unsigned int id;
    bool survived;
    PClass pclass;
    std::string name;
    Sex sex;
    unsigned int age;
    unsigned int sibsp;
    unsigned int parch;
    std::string ticket;
    double fare;
    std::string cabin;
    std::string embarked;
};

typedef std::vector<Passenger> VecPassengers;


std::ostream& operator<<(std::ostream& out, Passenger p)
{
    out << std::setw(4) << p.id << ",";
    out << std::setw(1) << p.survived << ",";
    out << std::setw(1) << static_cast<int>(p.pclass) << ",";
    out << std::setw(20) << p.name.substr(0, 20) << ",";
    std::string sex;
    switch(p.sex){
    case Sex::Female:
        sex = "Female";
        break;
    case Sex::Male:
        sex = "Male";
        break;
    default:
        sex = "";
    }
    out << std::setw(6) << sex << ",";
    out << std::setw(2) << p.age << ",";
    out << std::setw(1) << p.sibsp << ",";
    out << std::setw(1) << p.parch << ",";
    out << std::setw(15) << p.ticket << ",";
    out << std::setw(10) << p.fare << ",";
    out << std::setw(6) << p.cabin << ",";
    out << std::setw(1) << p.embarked;
    return out;
}


PClass toPClass(const std::string& buffer)
{
    std::stringstream sspcl(buffer);
    int pclassInt = 0;
    sspcl >> pclassInt;
    PClass pclass = static_cast<PClass>(pclassInt);
    return pclass;
}

Sex toSex(const std::string& buffer)
{
    Sex sex = Sex::NoInfo;
    if (buffer == "male") {
        sex = Sex::Male;
    }
    else if (buffer == "female") {
        sex = Sex::Female;
    }
    return sex;
}

int toUInt(const std::string& buffer)
{
    std::stringstream ssid(buffer);
    unsigned int number = 999;
    ssid >> number;
    return number;
}

double toDouble(const std::string& buffer)
{
    std::stringstream ssid(buffer);
    double number = 0;
    ssid >> number;
    return number;
}



Passenger extractData(std::istream& in)
{
    Passenger newPassenger;
    std::string buffer;
    
    std::getline(in, buffer, ','); // ID
    newPassenger.id = toUInt(buffer);
    
    std::getline(in, buffer, ','); // survived
    newPassenger.survived = buffer == "1";
    
    std::getline(in, buffer, ','); // pclass
    newPassenger.pclass = toPClass(buffer);
    
    std::getline(in, buffer, ','); // full name
    newPassenger.name = buffer;
    
    std::getline(in, buffer, ','); // sex
    newPassenger.sex = toSex(buffer);
    
    std::getline(in, buffer, ','); // age
    newPassenger.age = toUInt(buffer);
    
    std::getline(in, buffer, ','); // sibsp
    newPassenger.sibsp = toUInt(buffer);
    
    std::getline(in, buffer, ','); // parch
    newPassenger.parch = toUInt(buffer);
    
    std::getline(in, buffer, ','); // ticket
    newPassenger.ticket = buffer;
    
    std::getline(in, buffer, ','); // fare
    newPassenger.fare = toDouble(buffer);

    std::getline(in, buffer, ','); // Cabin
    newPassenger.cabin = buffer;

    std::getline(in, buffer, '\n'); // Embarked
    newPassenger.embarked = buffer;
    return newPassenger;
}

VecPassengers loadData(const std::string& INPUT_FILE_NAME)
{
    std::ifstream in;
    in.open(INPUT_FILE_NAME);
    VecPassengers passengers;
    std::string buffer;
    std::getline(in, buffer); // header
    while(std::getline(in, buffer))
    {
        std::stringstream lineStream(buffer);
        Passenger newPass = extractData(lineStream);
        passengers.push_back(newPass);
    }
    return passengers;
}

int main ()
{
    const std::string INPUT_FILE_NAME = "../../data/titanic.csv";
    VecPassengers passengers = loadData(INPUT_FILE_NAME);
    
    for (size_t i = 0; i < 200; ++i)
    {
        std::cout << passengers[i] << "\n";
    }
}
