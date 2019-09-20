#include <iostream>
#include<string>
#include <fstream>
using namespace std;

class Node;
typedef Node* NodePtr;
class CircularDLL;

class Node 
{
  friend class CircularDLL;
private:
  int stId;
  string stName;
  string stEmail;
  int stAge;
  NodePtr next;
  NodePtr prev;
public:
  Node();
  Node(int id, string name, string email, int age);
};

class CircularDLL
{
private:
  NodePtr  top;
  void destroy (NodePtr&);
public:
  CircularDLL();
  CircularDLL(const CircularDLL& source);
  ~CircularDLL();
  void insertDataFromFile();
  void print ();
  bool search (int id);
  void insertAfterFirst (int id, string name, string email, int age);
  void insertBeforeFirst (int id, string name, string email, int age);
  void insertAfterLast (int id, string name, string email, int age);
  void insertBeforeLast (int id, string name, string email, int age);
  void remove (int id);
  void copy (NodePtr atop, NodePtr& btop);
};

Node::Node()
{
  stId = stAge = 0;
  stName = stEmail = "SPACE";
}

Node::Node(int id, string name, string email, int age)
{
  stId = id;
  stName = name;
  stEmail = email;
  stAge = age;
}

CircularDLL::CircularDLL()
{
  top = NULL;
}

CircularDLL::CircularDLL(const CircularDLL& source)
{
  top = NULL;
  copy(source.top, top);
}

CircularDLL::~CircularDLL()
{
  destroy(top);
}

bool CircularDLL::search(int id)
{
  if(top != NULL)
    {
      NodePtr p = top;
      do{
	if(p -> stId == id)
	  return true;
        p = p -> next;
      }while(p != top);
    }
  return false;
}

void CircularDLL::insertBeforeFirst(int id, string name, string email, int age)
{
  if(search(id) == true)
    return;
  if(top == NULL)
    {
      top = new Node(id, name, email, age);
      top -> next = top;
      top -> prev = top;
      return;
    }
  NodePtr p = new Node(id, name, email, age);
  p -> next = top;
  p -> prev = top -> prev;
  top -> prev -> next = p;
  top -> prev = p;
  top = p;
}

void CircularDLL::insertAfterFirst(int id, string name, string email, int age)
{
  if(search(id) == true)
    return;
  if(top == NULL)
    {
      top = new Node(id, name, email, age);
      top -> next = top;
      top -> prev = top;
      return;
    }
  NodePtr p = new Node(id, name, email, age);
  p -> next = top -> next;
  top -> next = p;
  p -> prev = top;
}

void CircularDLL::insertAfterLast(int id, string name, string email, int age)
{
  if(search(id) == true)
    return;
  if(top == NULL)
    {
      top = new Node(id, name, email, age);
      top -> next = top;
      top -> prev = top;
      return;
    }
  NodePtr p = new Node(id, name, email, age);
  NodePtr q;  
  p -> next = top;
  q = top -> prev;
  q -> next = p;
  p -> prev = q;
  top -> prev = p;
}

void CircularDLL::insertBeforeLast(int id, string name, string email, int age)
{
  if(search(id) == true)
    return;
  if(top == NULL)
    {
      top = new Node(id, name, email, age);
      top -> next = top;
      top -> prev = top;
      return;
    }
  NodePtr p = new Node(id, name, email, age);
  NodePtr q = top -> prev;
  NodePtr k = q -> prev;
  p -> next = q;
  p -> prev = k;
  k -> next = p;
  q -> prev = p;
}

void CircularDLL::destroy(NodePtr& top)
{
  if(top != NULL)
    {
      NodePtr p = top;
      NodePtr q = top;
      do{
	q = q -> next;
	delete p;
	p = q;
      }while(p != top);
    }
  top = NULL;
}

void CircularDLL::remove(int id)
{
  if(top == NULL)
    {
      cout << "----------------------------" << endl;
      cout << "Nothing to remove" << endl;
      return;
    }
  if(search(id) == false)
    {
      cout << "----------------------------" << endl;
      cout << "No such a student" << endl;
      return;
    }
  if(top != NULL)
    {
      NodePtr p = top;
      NodePtr q = top;
      NodePtr z = top;
      do{
	if(top -> stId == id)
	  {
	    q = top -> prev;
	    top = p -> next;
	    q -> next = top;
	    top -> prev = q;
	    delete p;
	    return;
	  }
        p = p -> next;
        q = p;
	if(p -> stId == id)
          {
	    z = p;
            q = p -> prev;
            p = p -> next;
            q -> next = p;
            p -> prev = q;
            delete z;
            return;
          }
	//q = p;
	p = p -> next;
	q = p;
      }while(p != top);
    }
}

void CircularDLL::copy(NodePtr atop, NodePtr& btop)
{
  NodePtr acurr, bcurr, zcurr;
  destroy (btop);
  if (atop != NULL)
    {
      btop = new Node;
      btop -> stId = atop -> stId;
      btop -> stName = atop -> stName;
      btop -> stEmail = atop -> stEmail;
      btop -> stAge = atop -> stAge;
      acurr = atop;
      bcurr = btop;
      zcurr = btop;

      while (acurr -> next != atop)
        {
          bcurr -> next = new Node;
          acurr = acurr -> next;
          bcurr = bcurr -> next;
          bcurr -> stId = acurr -> stId;
          bcurr -> stName = acurr -> stName;
          bcurr -> stEmail = acurr -> stEmail;
          bcurr -> stAge = acurr -> stAge;
	  bcurr -> prev = zcurr;
	  zcurr = bcurr;
        }
      bcurr -> next = btop;
    }
}

void CircularDLL::insertDataFromFile()
{
  ifstream fin;
  string name;
  int num;
  string word;
  string word2;
  int num2;

  cout << "Enter data file: ";
  cin >> name;

  fin.open(name.data());

  while(fin)
    {
      fin >> num;
      fin >> word;
      fin >> word2;
      fin >> num2;
      insertAfterLast(num, word, word2, num2);
    }
}

void CircularDLL::print()
{
  if(top != NULL)
    {
      NodePtr p = top;
      do{
	cout << p -> stId << " ";
	cout << p -> stName << " ";
	cout << p -> stEmail << " ";
	cout << p -> stAge << endl;
	p = p -> next;
      }while(p != top);
    }
  cout << "-----------------------------" << endl;

}

int main () 
{
  CircularDLL list1;
  list1.insertDataFromFile();
  list1.print();
  list1.insertAfterFirst (54321, "Jim", "jim@csusm.edu", 25);
  list1.insertBeforeFirst (54123, "Joe", "joe@csusm.edu", 35);
  list1.insertAfterLast (63421, "Adam", "adam@csusm.edu", 20);
  list1.insertBeforeLast (66641, "Nancy", "nancy@csusm.edu", 27);
  list1.print();
  bool  found = list1.search (12321);
  if (found)
    cout << "the record was found" << endl;
  else
    cout << "the record was not found" << endl;
  list1.remove (54321);
  list1.print();
   
    CircularDLL list2(list1);
  list2.print();
  return 0;
}
