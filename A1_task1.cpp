#include <iostream>
using namespace std;

class Node {
public:
    int processID, execTime, remainingTime;
    Node* nxt;
    Node(int pID, int eTime) : processID(pID), execTime(eTime), remainingTime(eTime), nxt(nullptr) {}
};

class Scheduler {
    Node* nxt, *prev;
    int timeSlice;

public:
    Scheduler(int timeSlice) : nxt(nullptr), prev(nullptr), timeSlice(timeSlice) {}

    void add(int processID, int execTime) {
        Node* node = new Node(processID, execTime);
        if (!nxt) {
            nxt = prev = node;
            node->nxt = nxt;
        } else {
            prev->nxt = node;
            node->nxt = nxt;
            prev = node;
        }
    }

    void remove(Node* pre, Node* node) {
        if (node == nxt && node == prev) {
            delete node;
            nxt = prev = nullptr;
        } else if (node == nxt) {
            prev->nxt = nxt->nxt;
            nxt = nxt->nxt;
            delete node;
        } else {
            pre->nxt = node->nxt;
            if (node == prev) prev = pre;
            delete node;
        }
    }

    void run() {
        if (!nxt) return;
        Node* node = nxt;
        Node* pre = prev;
        int cycle = 1;

        while (nxt) {
            cout << "Cycle " << cycle << ": ";
            do {
                cout << endl << "P" << node->processID << " (Remaining: " << node->remainingTime << ") ";
                if (node->remainingTime <= timeSlice) {
                    cout << "-> Completes" << endl;
                    Node* next = node->nxt;
                    remove(pre, node);
                    node = next;
                } else {
                    node->remainingTime -= timeSlice;
                    pre = node;
                    node = node->nxt;
                }
                cout << endl;
                if (!nxt) break;

            } while (node != nxt);
            cycle++;
        }
        cout << "All processes completed!" << endl;
    }
};

int main() {
    Scheduler s(3);
    s.add(1, 10);
    s.add(2, 5);
    s.add(3, 8);
    cout << "Initial Processes: [(P1, 10), (P2, 5), (P3, 8)]" << endl << endl;
    cout << "CPU Time per Process per Cycle: 3" << endl << endl;
    s.run();
    cout << endl;
    return 0;
}
