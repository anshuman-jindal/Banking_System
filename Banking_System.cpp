// Anshuman Jindal, CS22B067
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
  int acc;
  int bal;
  Node *next;
  Node() {
    bal = 1000;
    next = nullptr;
  }

  Node(int acc) {
    this->bal = 1000;
    this->acc = acc;
    next = nullptr;
  }
  friend class SLL;
};

class SLL {
private:
  Node *first;
  Node *last;
  int len;

public:
  SLL() {
    first = nullptr;
    last = nullptr;
    len = 0;
  }
  void InsertNode(int);
  int GetLen() { return len; }
  void Count(int);
  void Highest();
  void Balance(int);
  friend class DLL;
  void printsll() {
    Node *temp = first;
    while (temp != nullptr) {
      cout << temp->acc << " " << temp->bal << endl;
      temp = temp->next;
    }
  }
} S;

void SLL::InsertNode(int acc) {
  Node *ToAddNode = new Node(acc);
  Node *temp;
  if (first == nullptr) {
    first = ToAddNode;
    last = ToAddNode;
    len++;
  } else {
    temp = first;
    for (int i = 1; i < len; i++) {
      temp = temp->next;
    }
    temp->next = ToAddNode;
    last = ToAddNode;
    len++;
  }
}

class DNode {
private:
  int acc;
  char c;
  int amount;
  DNode *next;
  DNode *prev;

public:
  DNode() {}
  DNode(int acc, char c, int amount) {
    this->acc = acc;
    this->c = c;
    this->amount = amount;
    next = nullptr;
    prev = nullptr;
  }
  friend class DLL;
};

class DLL {
private:
  DNode *Head;
  DNode *Tail;
  int Dlen;
  DNode *cursor;

public:
  DLL() {
    Head = new DNode();
    Tail = new DNode();
    Head->next = Tail;
    Head->prev = nullptr;
    Tail->next = nullptr;
    Tail->prev = Head;
    Dlen = 0;
    cursor = Head;
  }
  DNode *GetHead() { return Head; }
  DNode *GetTail() { return Tail; }
  void DInsertNode(int, char, int, SLL &);
  void KInsertNode(int, char, int, int);
  void Process(int);
  void Undo(int);
  void Insert();
  void AllAfterCursor();
  void SY(int);
  void DAM(int, int);
  void dis() {
    DNode *temp = Head->next;
    while (temp != Tail) {
      cout << temp->acc << " " << temp->amount << " " << temp->c << " " << endl;
      temp = temp->next;
    }
  }
} D;

void DLL::DInsertNode(int acc, char c, int amount, SLL &S) {
  Node *temp = S.first;
  while (temp != nullptr) {
    if (temp->acc == acc)
      break;
    temp = temp->next;
  }
  if (temp == nullptr)
    return;
  DNode *DToAddNode = new DNode(acc, c, amount);
  // assert(DToAddNode->acc==acc);
  DToAddNode->next = Tail;
  DToAddNode->prev = Tail->prev;
  Tail->prev = DToAddNode;
  DToAddNode->prev->next = DToAddNode;
  Dlen++;
}
void DLL::KInsertNode(int x, char c, int y, int K) {
  if (K > Dlen)
    return;
  DNode *DToAddNode = new DNode(x, c, y);
  DNode *temp1 = Head;
  int dummy = 0;
  for (int i = 0; i < K; i++) {
    if (temp1 == cursor)
      dummy = 1;
    temp1 = temp1->next;
  }
  DNode *c2 = cursor;
  DToAddNode->next = temp1->next;
  DToAddNode->prev = temp1;
  temp1->next = DToAddNode;
  DToAddNode->next->prev = DToAddNode;
  Dlen++;
  if (dummy == 0) {
    cursor = Head->next;
    while (cursor->acc != x) {
      cursor = cursor->next;
    }
    cursor = cursor->prev;
    Process(1);
  }
  cursor=c2;
}
void DLL::Process(int X) {
  while (X-- && cursor != D.GetTail()) {
    cursor = cursor->next;
    if (cursor->c == 'D') {
      Node *tmp = S.first;
      while (tmp->acc != cursor->acc) {
        tmp = tmp->next;
      }
      tmp->bal += cursor->amount;
    } else if (cursor->c == 'W') {
      Node *tmp = S.first;
      while (tmp->acc != cursor->acc) {
        tmp = tmp->next;
      }
      tmp->bal -= cursor->amount;
    }
  }
  if (cursor == Tail)
    cursor = Tail->prev;
}

void DLL::Undo(int Y) {
  while (Y-- && cursor != D.GetHead()) {

    if (cursor->c == 'D') {
      Node *tmp = S.first;
      while (tmp->acc != cursor->acc) {
        tmp = tmp->next;
      }
      tmp->bal -= cursor->amount;
    } else if (cursor->c == 'W') {
      Node *tmp = S.first;
      while (tmp->acc != cursor->acc) {
        tmp = tmp->next;
      }
      tmp->bal += cursor->amount;
    }
    cursor = cursor->prev;
  }
}

void DLL::SY(int Y) {
  DNode *t = D.GetHead();
  while (t != cursor->next) {
    t = t->next;
    if (t->acc == Y)
      cout << t->acc << " " << t->c << " " << t->amount << endl;
  }
}

void DLL::AllAfterCursor() { Process(Dlen + 30); }

void SLL::Count(int X) {
  Node *tmp = S.first;
  int c = 0;
  while (tmp != nullptr) {
    if (tmp->bal >= X)
      c++;
    tmp = tmp->next;
  }
  cout << c << endl;
}
void SLL::Highest() {
  Node *tmp = S.first;
  vector<int> v;
  int a = INT_MIN;
  while (tmp != nullptr) {
    if (tmp->bal == a)
      v.push_back(tmp->acc);
    else if (tmp->bal > a) {
      a = tmp->bal;
      v.clear();
      v.push_back(tmp->acc);
    }
    tmp = tmp->next;
  }
  // sort(v.begin(), v.end());
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
  return;
}

void SLL::Balance(int X) {
  Node *tmp = S.first;
  while (tmp != nullptr) {
    if (tmp->acc == X) {
      cout << tmp->bal << endl;
      return;
    }
    tmp = tmp->next;
  }
}

void DLL::DAM(int M, int A) {
  DNode *c2 = cursor;
  int count = 0;
  if (M > 0) {
    while (count != M && c2 != D.GetTail()) {
      c2 = c2->next;
      if (c2->acc == A) {
        c2->prev->next = c2->next;
        c2->next->prev = c2->prev;
        // c1 = c2;
        // c2 = c2->prev;
        // delete c1;
        count++;
      }
    }
  } else if (M < 0) {
    while (count != ((-1) * M) && c2 != D.GetHead()) {
      c2 = c2->prev;
      if (c2->acc == A) {
        DNode *cc = cursor;
        cursor = c2;
        D.Undo(1);
        c2->prev->next = c2->next;
        c2->next->prev = c2->prev;
        cursor = cc;
        // c1 = c2;
        // c2 = c2->next;
        // delete c1;
        count--;
      }
    }
  }
}

int main() {
  // SLL S and DLL D are already declared
  int C;
  cin >> C;
  for (int i = 0; i < C; i++) {
    int x;
    cin >> x;
    S.InsertNode(x);
  }

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int x, y;
    char c;
    cin >> x >> c >> y;
    D.DInsertNode(x, c, y, S);
  }
  // D.dis();
  // DNode *cursor = D.GetHead();
  char c;
  cin >> c;
  while (c != 'E') {
    if (c == 'F') {
      int X;
      cin >> X;
      D.Process(X);
    } else if (c == 'R') {
      int Y;
      cin >> Y;
      D.Undo(Y);
    } else if (c == 'G') {
      int X;
      cin >> X;
      S.Count(X);
    } else if (c == 'M') {
      S.Highest();
    } else if (c == 'V') {
      int X;
      cin >> X;
      S.Balance(X);
    } else if (c == 'C') {
      D.AllAfterCursor();
    } else if (c == 'I') {
      int x, y, K;
      char c;
      cin >> x >> c >> y >> K;
      D.KInsertNode(x, c, y, K);
    } else if (c == 'S') {
      int Y;
      cin >> Y;
      D.SY(Y);
    } else if (c == 'D') {
      int A, M;
      cin >> A >> M;
      D.DAM(M, A);
    }
    // D.dis();
    // cout << endl;
    // S.printsll();
    cin >> c;
  }
  return 0;
}
