//create by Zain Raza

#include "triagesystem.h"
#include "ui_triagesystem.h"
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>

Logger *logger = &Logger::getInstance();

TriageSystem::TriageSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TriageSystem)
{
    logger = &Logger::getInstance();

    ui->setupUi(this);
    ui->txtPriority->setValidator(new QIntValidator(0, 1000, this));
}

TriageSystem::~TriageSystem()
{    
    treatedContainer.clear();
    triagedContainer.clear();
    delete ui;
}

void TriageSystem::on_menu_exit_triggered()
{
    exit(0);
}

void TriageSystem::on_menu_import_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open text file"), "/", tr("Text Files (*.txt)"));

//    QMessageBox msgBox;
//    msgBox.setText(fileName.toUtf8().constData());
//    msgBox.exec();

    this->onAddTriagedFromFile(fileName.toUtf8().constData());

}

void TriageSystem::on_btnAddPatient_clicked()
{
    this->onAddPatient();
}

void TriageSystem::on_btnNextPatient_clicked()
{
    Patient res = this->getNextTreated();
    ui->txtConsole->document()->setPlainText(res.report().c_str());
}

void TriageSystem::on_btnPrintAllTreated_clicked()
{
    this->onPrintTreated();
}

void TriageSystem::on_btnPrintAllTrage_clicked()
{
    this->onPrintTriaged();
}

void TriageSystem::on_btnTreatAll_clicked()
{
    this->onTreatAll();
}

void TriageSystem::on_btnTreat_clicked()
{
    this->onTreat();
}

void TriageSystem::on_btnSearchPatient_clicked()
{

}

void TriageSystem::on_btnSearchDoctor_clicked()
{

}

void TriageSystem::onAddTriagedFromFile(string fileName) {
    logger->log("action bulk add patients into the system (from a file)");

    string firstName;
    string middleName;
    string lastName;
    string suffix;
    vector<string> ailments;
    string doctor;
    bool treated;
    int priority;

    string content;

    ifstream file(fileName, ifstream::binary);

    logger->log("add patients from file: \"" + fileName + "\"");

    while (getline(file, content)) {
        // trim content (erase not-need character)
        content.erase(remove(content.begin(), content.end(), '\n'), content.end());
        content.erase(remove(content.begin(), content.end(), '\t'), content.end());
        content.erase(remove(content.begin(), content.end(), '\r'), content.end());
        content.erase(remove(content.begin(), content.end(), '\f'), content.end());

        if (content.find("firstName:", 0) == 0) firstName = content.substr(10);
        else if (content.find("middleName:") == 0) middleName = content.substr(11);
        else if (content.find("lastName:") == 0) lastName = content.substr(9);
        else if (content.find("suffix:") == 0) suffix = content.substr(7);
        else if (content.find("ailment:") == 0) ailments.push_back(content.substr(8));
        else if (content.find("doctor:", 0) == 0) doctor = content.substr(7);
        else if (content.find("treated:") == 0) treated = (atoi(content.substr(8, 9).c_str()) != 0);
        else if (content.find("priority:") == 0) {
            priority = atoi(content.substr(9).c_str());
            vector<string> ailmentsClone(ailments); // clone vector ailments

            Patient *newPatient = new Patient(firstName, middleName, lastName,
                    suffix, ailmentsClone, doctor, treated, priority);

            if (treated) {
                this->addTreated(newPatient);
            } else {
                this->addTriaged(newPatient);
            }
            // clear vector ailments
            ailments.clear();
        } else continue;
    }
    file.close();

    ui->txtConsole->appendPlainText("\nDone add patients from file");
}

void TriageSystem::onPrintTriaged() {
    logger->log("action print out a report of all the patients in triage");

    ui->txtConsole->clear();

    for (int i = 0; i < triagedContainer.size(); i++) {
        Patient res = *triagedContainer[i];
        ui->txtConsole->appendPlainText(res.report().c_str());
    }
}

void TriageSystem::onPrintTreated() {
    logger->log("action print out a report of “treated” patients");

    ui->txtConsole->clear();

    for (int i = 0; i < treatedContainer.size(); i++) {
        Patient res = *treatedContainer[i];
        ui->txtConsole->appendPlainText(res.report().c_str());
    }
}

void TriageSystem::addTriaged(Patient* patient) {
    logger->log("add patient to triagedContainer - " + patient->toString());

    if (triagedContainer.size() == 0 || *triagedContainer[0] == *patient) {
        triagedContainer.push_back(patient);
        return;
    }

    for (int i = 0; i < triagedContainer.size(); i++) {
        if (*patient < *triagedContainer[i]) {
            triagedContainer.emplace(triagedContainer.begin() + i, patient);
            return;
        }
    }
    triagedContainer.push_back(patient);
}

void TriageSystem::addTreated(Patient* patient) {
    logger->log("add patient to treatedContainer - " + patient->toString());

    treatedContainer.push_back(patient);
}

Patient TriageSystem::getNextTreated() {
    Patient *next = triagedContainer.front();
    return *next;
}

void TriageSystem::onTreat() {
//    ui->txtConsole->clear();
    logger->log("action \"treat\" a patient in triaged order");

    if (triagedContainer.size() == 0) {
        logger->log("there is no patient to treat");
        ui->txtConsole->insertPlainText("\nThere is no patient to treat");
        return;
    }

    Patient *patient = triagedContainer.front();
    triagedContainer.erase(triagedContainer.begin());

    logger->log("Treating patient - " + patient->toString());
    ui->txtConsole->insertPlainText("\nTreating patient");
    ui->txtConsole->insertPlainText(patient->report().c_str());
    int treatTime = rand() % 3 + 1;
    std::this_thread::sleep_for(std::chrono::seconds(treatTime));
    patient->treat();
    logger->log("Treated patient after " + to_string(treatTime) + "s - " + patient->toString());
    ui->txtConsole->insertPlainText("\nTreated patient after(s) ");
    ui->txtConsole->insertPlainText(to_string(treatTime).c_str());

    addTreated(patient);
}

void TriageSystem::onTreatAll() {
    ui->txtConsole->clear();
    logger->log("action treat all patients");

    int size = triagedContainer.size();

    for (int i = 0; i < size; i++) {
        onTreat();
    }

    ui->txtConsole->insertPlainText("\nDone treat all patients");
}

void tokenize(const string& str, vector<string>& tokens, const string& delimiters = ";")
{
  // Skip delimiters at beginning.
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);

  // Find first non-delimiter.
  string::size_type pos = str.find_first_of(delimiters, lastPos);

  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));

    // Skip delimiters.
    lastPos = str.find_first_not_of(delimiters, pos);

    // Find next non-delimiter.
    pos = str.find_first_of(delimiters, lastPos);
  }
}

void TriageSystem::onAddPatient() {
    logger->log("action add a patient to the system");

    string firstName = ui->txtFirstName->text().toUtf8().constData();
    string middleName = ui->txtMidlleName->text().toUtf8().constData();
    string lastName = ui->txtLastName->text().toUtf8().constData();
    string suffix = ui->txtSuffix->text().toUtf8().constData();
    string ailment = ui->txtAliments->text().toUtf8().constData();
    vector<string> ailments;
    string doctor = ui->txtDoctor->text().toUtf8().constData();
    bool treated = ui->cbTreated->isChecked();
    int priority = ui->txtPriority->text().toInt();

    tokenize(ailment, ailments, ";");

    Patient *newPatient = new Patient(firstName, middleName, lastName,
            suffix, ailments, doctor, treated, priority);

    if (newPatient->isTreated()) {
        this->addTreated(newPatient);
    } else {
        this->addTriaged(newPatient);
    }

    cout << "Done add triaged" << endl;
}
