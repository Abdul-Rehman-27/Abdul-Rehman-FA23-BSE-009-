#include <iostream>
using namespace std;

class Node
{
public:
  int taskId;
  string Description;
  int priorLevel;
  Node *next;

  Node(int taskId, string Description, int priorLevel)
  {
    this->taskId = taskId;
    this->Description = Description;
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

  // Delete Task from Start
  void delTaskFromStart()
  {
    if (head == NULL)
    {
      cout << "Linked List is empty\n";
      return;
    }
    Node *temp = head;
    head = head->next;
    delete temp;
  }

  // Delete Task from End
  void delTaskFromEnd()
  {
    if (head == NULL)
    {
      cout << "Linked list is empty\n";
      return;
    }
    else
    {
      Node *temp = head;
      while (temp->next != tail)
      {
        temp = temp->next;
      }
      temp->next = NULL;
      delete tail;
      tail = temp;
    }
  }

  // Delete Task from Middle
  void delTaskFromMiddle(int taskId)
  {
    if (head == NULL)
    {
      cout << "Linked List is empty\n";
      return;
    }

    Node *temp = head;
    Node *prev = NULL;

    while (temp != NULL && temp->taskId != taskId)
    {
      prev = temp;
      temp = temp->next;
    }

    if (temp == NULL)
    {
      cout << "Task with ID " << taskId << " not found!\n";
      return;
    }

    if (temp == head)
    {
      delTaskFromStart();
      return;
    }

    if (temp == tail)
    {
      delTaskFromEnd();
      return;
    }

    prev->next = temp->next;
    delete temp;
  }

  void priorBasedAdd(int taskId, string Description, int priorLvl)
  {
    Node *newTask = new Node(taskId, Description, priorLvl);

    // If list is empty
    if (head == NULL)
    {
      head = tail = newTask;
      return;
    }

    //New task with the highest priority, insert at the start
    if (priorLvl < head->priorLevel)
    {
      newTask->next = head;
      head = newTask;
      return;
    }

    Node *temp = head;
    Node *prev = NULL;

    // Run Loop to find Position
    while (temp != NULL && temp->priorLevel <= priorLvl)
    {
      prev = temp;
      temp = temp->next;
    }

    prev->next = newTask;
    newTask->next = temp;

    // If inserted at the end, update tail
    if (temp == NULL)
    {
      tail = newTask;
    }
  }

  void removeHighestPriorityTask()
  {
    if (head == NULL)
    {
      cout << "No tasks available to remove.\n";
      return;
    }
    delTaskFromStart();
    cout << "Highest priority task removed.\n";
  }

  // View Task
  void viewTask()
  {
    Node *temp = head;
    if (temp == NULL)
    {
      cout << "No tasks available.\n";
      return;
    }
    while (temp != NULL)
    {
      cout << "Task ID: " << temp->taskId << "  Description: "
           << temp->Description << "  Priority: " << temp->priorLevel << endl;
      temp = temp->next;
    }
  }
};

int main()
{
  List view;
  int i = 0;
  while (i != 1)
  {
    cout << "====================Task Management System========================" << endl;
    cout << "1) Add Task" << endl;
    cout << "2) View Tasks" << endl;
    cout << "3) Remove Highest Priority Task" << endl;
    cout << "4) Remove Task by ID" << endl;
    cout << "5) Exit" << endl;

    int choice;
    cout << "Enter Your Choice: ";
    cin >> choice;

    if (choice == 1)
    {
      int taskId, priorLvl;
      string Description;

      cout << "Enter Task ID: ";
      cin >> taskId;
      cin.ignore();

      cout << "Enter Task Description: ";
      getline(cin, Description);

      cout << "Enter Priority Level: ";
      cin >> priorLvl;

      view.priorBasedAdd(taskId, Description, priorLvl);
    }
    else if (choice == 2)
    {
      cout << "==================View Task==================" << endl;
      view.viewTask();
    }
    else if (choice == 3)
    {
      view.removeHighestPriorityTask();
    }
    else if (choice == 4)
    {
      int taskId;
      cout << "Enter Task ID to Remove: ";
      cin >> taskId;
      view.delTaskFromMiddle(taskId);
    }
    else if (choice == 5)
    {
      i = 1;
      cout << "Exiting the Loop\n";
      break;
    }
    else
    {
      cout << "Invalid choice. Try again!\n";
    }
  }
  return 0;
}
