#include "Patient.h"

Patient::Patient() {
}

Patient::Patient(string firstName, string middleName, string lastName,
        string suffix, vector<string> &ailments, string doctor,
        bool treated, int priority) {
    this->firstName = firstName;
    this->middleName = middleName;
    this->lastName = lastName;
    this->suffix = suffix;
    this->ailments = ailments;
    this->doctor = doctor;
    this->treated = treated;
    this->priority = priority;
}

Patient::~Patient() {
}

bool Patient::isTreated() {
    return treated;
}

void Patient::treat() {
    treated = true;
}

string Patient::getName() {
    return firstName;
}

string Patient::getDoctor() {
    return doctor;
}

Patient* Patient::clone() {
    Patient* patient = new Patient();
    patient->firstName = firstName;
    patient->middleName = middleName;
    patient->lastName = lastName;
    patient->suffix = suffix;
    patient->ailments = ailments;
    patient->doctor = doctor;
    patient->treated = treated;
    patient->priority = priority;
    return patient;
}

string Patient::toString() {
    string result = "{";
    
    result += "firstName: " + this->firstName + ", ";
    result += "middleName: " + this->middleName + ", ";
    result += "lastName: " + this->lastName + ", ";
    result += "suffix: " + this->suffix + ", ";
    result += "ailments: [";
    for (int i = 0; i < this->ailments.size(); i++)
        result += this->ailments[i] + (i < (this->ailments.size() - 1)?", ":"");
    result += "], ";
    result += "doctor: " + this->doctor + ", ";
    result += "treated: " + to_string(this->treated) + ", ";
    result += "priority: " + to_string(this->priority);
    result += "}";
    
    return result;
}

string Patient::report() {
    string result = "";
    result += "firstName: " + this->firstName + "\n";
    result += "middleName: " + this->middleName + "\n";
    result += "lastName: " + this->lastName + "\n";
    result += "suffix: " + this->suffix + "\n";
    for (int i = 0; i < this->ailments.size(); i++)
        result += "ailment: " + this->ailments[i] + "\n";
    result += "doctor: " + this->doctor + "\n";
    result += "treated: " + to_string(this->treated) + "\n";
    result += "priority: " + to_string(this->priority) + "\n";
    return result;
}

/* Implement Comparable */

ostream& operator<<(ostream &out, const Patient &p) //operator function
{
    out << "firstName: " << p.firstName << endl;
    out << "middleName: " << p.middleName << endl;
    out << "lastName: " << p.lastName << endl;
    out << "suffix: " << p.suffix << endl;
    for (int i = 0; i < p.ailments.size(); i++)
        out << "ailment: " << p.ailments[i] << endl;
    out << "doctor: " << p.doctor << endl;
    out << "treated: " << p.treated << endl;
    out << "priority: " << p.priority;
    return out;
}

bool operator<(const Patient &o1, const Patient &o2) {
    return o1.priority < o2.priority;
}

bool operator<=(const Patient& o1, const Patient& o2) {
    return o1.priority <= o2.priority;
}

bool operator>(const Patient &o1, const Patient &o2) {
    return o1.priority > o2.priority;
}

bool operator>=(const Patient& o1, const Patient& o2) {
    return o1.priority >= o2.priority;
}

bool operator==(const Patient &o1, const Patient &o2) {
    return o1.priority == o2.priority;
}
