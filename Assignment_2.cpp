#include <iostream>
using namespace std;

class Node
{
public:
  string patientName;
  int arrivalOrder;
  string emergCondition;
  int priorLevel;
  Node *next;

  Node(string patientName, int arrivalOrder, string emergCondition, int priorLevel)
  {
    this->patientName = patientName;
    this->arrivalOrder = arrivalOrder;
    this->emergCondition = emergCondition;
    this->priorLevel = priorLevel;
    next = NULL;
  }
};

// Class of Link
class List
{
public:
  Node *head;
  Node *tail;

  List()
  {
    head = tail = NULL;
  }

  void priorBasedAdd(string patientName, int arrivalOrder, string emergCondition, int priorLevel)
  {

    Node *newPatient = new Node(patientName, arrivalOrder, emergCondition, priorLevel);

    // If there is no patient already
    if (head == NULL)
    {
      head = tail = newPatient;
      return;
    }

    // New Patient with the Highest Priority
    if (priorLevel < head->priorLevel)
    {
      newPatient->next = head;
      head = newPatient;
      return;
    }
    Node *temp = head;
    Node *prev = NULL;

    // Patient with Middle Priority
    while (temp != NULL && temp->priorLevel <= priorLevel)
    {
      prev = temp;
      temp = temp->next;
    }

    prev->next = newPatient;
    newPatient->next = temp;

    // Patient with lowest Priority
    if (temp == NULL)
    {
      tail = newPatient;
    }
  }

  // View Task
  void viewPatient()
  {
    cout << "===================View Patient=======================" << endl;
    Node *temp = head;
    if (temp == NULL)
    {
      cout << "No Patient available.\n";
      return;
    }
    while (temp != NULL)
    {
      cout << "Patient: " << temp->patientName << "  Arrival Order: "
           << temp->arrivalOrder << "  Emergency: " << temp->emergCondition << "  Priority: " << temp->priorLevel << endl;
      temp = temp->next;
    }
  }
};

int main()
{
  List history;
  int i = 0;
  while (i != 1)
  {
    cout << "====================Medical Scheduling========================" << endl;
    cout << "1) Add Patient" << endl;
    cout << "2) View Patient" << endl;
    cout << "3) Exit" << endl;
    cout << "--------------------------------------------------------------" << endl;

    int choice;
    cout << "Enter Your Choice: ";
    cin >> choice;

    if (choice == 1)
    {
      cout << "====================Add Patient========================" << endl;
      string patientName;
      int arrivalOrder;
      string emergCondition;
      int priorLevel;

      cout << "Enter Patient Name: ";
      cin >> patientName;

      cout << "Enter Arrival Order: ";
      cin >> arrivalOrder;

      cout << "Enter Emerg Condition: ";
      cin.ignore();
      getline(cin, emergCondition);

      //Set priority Based On Emerg Condition
      if (emergCondition == "Heart Attack" || emergCondition == "Stroke")
        priorLevel = 1;
      else if (emergCondition == "Broken Leg" || emergCondition == "Severe Burn" || emergCondition == "Fractured Arm")
        priorLevel = 2;
      else if (emergCondition == "Fever" || emergCondition == "Food Poisoning" || emergCondition == "Migraine")
        priorLevel = 3;
      else if (emergCondition == "Mild Cold" || emergCondition == "Small Cut")
        priorLevel = 4;
      else
      {
        cout << "Invalid valid emergency condition.\n";
        continue;
      }

      history.priorBasedAdd(patientName, arrivalOrder, emergCondition, priorLevel);
    }
    else if (choice == 2)
    {
      history.viewPatient();
    }
    else if (choice == 3)
    {
      i = 1;
      cout << "Exiting the Loop...\n";
      break;
    }
    else
    {
      cout << "Invalid choice. Try again!\n";
    }
  }
  return 0;
}