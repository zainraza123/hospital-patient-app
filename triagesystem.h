#ifndef TRIAGESYSTEM_H
#define TRIAGESYSTEM_H

#include "Header.h"
#include "Patient.h"

#include <QMainWindow>

namespace Ui {
class TriageSystem;
}

class TriageSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit TriageSystem(QWidget *parent = 0);
    ~TriageSystem();

private slots:
    void on_menu_exit_triggered();

    void on_menu_import_triggered();

    void on_btnAddPatient_clicked();

    void on_btnNextPatient_clicked();

    void on_btnPrintAllTrage_clicked();

    void on_btnPrintAllTreated_clicked();

    void on_btnTreat_clicked();

    void on_btnTreatAll_clicked();

    void on_btnSearchPatient_clicked();

    void on_btnSearchDoctor_clicked();

private:
    Ui::TriageSystem *ui;
    Logger *logger;

    vector<Patient*> triagedContainer;
    vector<Patient*> treatedContainer;

    // add a patient to queue of triage
    void addTriaged(Patient* patient);

    // add a patient to treated container
    void addTreated(Patient* patient);

    // action print all patient in queue of triage container
    void onPrintTriaged();

    // action print all treated patient
    void onPrintTreated();


    // action add patients from a file
    void onAddTriagedFromFile(string fileName);

    // Readonly: get the next patient will be treated container
    Patient getNextTreated();

    // action treat a patient at front of queue container
    void onTreat();

    // action treat all patient in queue of triage container
    void onTreatAll();

    // action manually add a patient
    void onAddPatient();
};

#endif // TRIAGESYSTEM_H
