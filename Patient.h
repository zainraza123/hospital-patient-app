#ifndef PATIENT_H
#define PATIENT_H

#include "Header.h"

// declare class Patient
class Patient {
public:
    Patient();
    Patient(string firstName, string middleName, string lastName,
            string suffix, vector<string> &ailments, string doctor,
            bool treated, int priority);

    virtual ~Patient();

    // check if this patient is treated
    bool isTreated();

    // treat this patient
    void treat();

    // get name of patient
    string getName();

    // get doctor's name of patient
    string getDoctor();
    
    // clone this patient
    Patient* clone();
    
    string toString();

    string report();

    //operator function
    friend ostream& operator<<(ostream &out, const Patient &w);
    
    /* Implement Comparable */
    friend bool operator<(const Patient &o1, const Patient &o2);
    friend bool operator<=(const Patient &o1, const Patient &o2);
    friend bool operator>(const Patient &o1, const Patient &o2);
    friend bool operator>=(const Patient &o1, const Patient &o2);
    friend bool operator==(const Patient &o1, const Patient &o2);

private:
    string firstName;
    string middleName;
    string lastName;
    string suffix;
    vector<string> ailments;
    string doctor;
    bool treated;
    int priority;
};

#endif /* PATIENT_H */

