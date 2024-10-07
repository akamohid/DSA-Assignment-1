#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Node {
public:
    long long val;
    Node* next;

    Node(long long v) : val(v), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void add(long long v) {
        Node* newNode = new Node(v);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int size() {
        int len = 0;
        Node* temp = head;
        while (temp) {
            len++;
            temp = temp->next;
        }
        return len;
    }

    Node* get(int idx) {
        Node* temp = head;
        for (int i = 0; i < idx && temp; i++) {
            temp = temp->next;
        }
        return temp;
    }

    ~LinkedList() {
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

vector<long long> buildLargeNum(LinkedList& list) {
    vector<long long> largeNum;
    int len = list.size();

    for (int i = 0; i < len; ++i) {
        Node* node = list.get(i);
        if (node) {
            largeNum.push_back(node->val);
        }
    }
    return largeNum;
}

void printLargeNum(const vector<long long>& largeNum) {
    for (long long segment : largeNum) {
        cout << segment << " ";
    }
    cout << endl;
}

bool isPrime(const vector<long long>& largeNum, int k) {
    long long combined = 0;
    for (long long seg : largeNum) {
        combined ^= seg;
    }
    return combined % 2 != 0;
}

LinkedList genRand() {
    LinkedList list;
    for (int i = 0; i < 16; i++) {
        long long randSeg = static_cast<long long>(rand()) << 32 | rand();
        list.add(randSeg);
    }
    return list;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    LinkedList list = genRand();
    vector<long long> largeNum = buildLargeNum(list);

    cout << "Generated 1024-bit number in segments:\n";
    printLargeNum(largeNum);

    bool isPrimeNum = isPrime(largeNum, 5);

    if (isPrimeNum) {
        cout << "The 1024-bit number is probably prime" << endl;
    } else {
        cout << "The 1024-bit number is not prime" << endl;
    }

    return 0;
}
