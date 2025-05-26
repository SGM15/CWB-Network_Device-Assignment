#include<bits/stdc++.h>
using namespace std;

// Packet structure
struct Packet {
    string data;
    int dest_port;
    int priority;

    Packet(string d, int p, int pr) : data(d), dest_port(p), priority(pr) {}
};

// Linked List Node for buffering packets
struct Node {
    Packet packet;
    Node* next;
    Node(Packet pkt) : packet(pkt), next(nullptr) {}
};

// Linked List class for per port buffer
class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() {
        head = tail = nullptr;
    }

    void push(Packet pkt) {
        Node* newNode = new Node(pkt);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    bool pop(Packet& pkt) {
        if (!head) return false;
        pkt = head->packet;
        Node* temp = head;
        head = head->next;
        delete temp;
        if (!head) tail = nullptr;
        return true;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};
// For comparing packets based on priority
struct ComparePriority {
    bool operator()(Packet& a, Packet& b) {
        return a.priority < b.priority;  
    }
};
// Network Device class to manage ports and buffers
// Array of linked lists for each port buffer, Priority Queue for scheduling high priority packets, and Stack for processing order
class NetworkDevice {
    int num_ports;
    int buffer_limit;

    LinkedList* port_buffers;
    priority_queue<Packet, vector<Packet>, ComparePriority> scheduler;
    stack<Packet> processor;

public:
    NetworkDevice(int ports, int limit) {
        num_ports = ports;
        buffer_limit = limit;
        port_buffers = new LinkedList[ports];
    }

    void receivePacket(string data, int port, int priority) {
        if (port < 0 || port >= num_ports) {
            cout << "Invalid port" << endl;
            return;
        }

        // Count buffer size 
        int count = 0;
        Node* temp = port_buffers[port].head;
        while (temp) {
            count++;
            temp = temp->next;
        }

        if (count >= buffer_limit) {
            cout << "Port " << port << " is congested. Packet dropped" << endl;
            return;
        }

        Packet pkt(data, port, priority);
        port_buffers[port].push(pkt);
        cout << "Packet received at port " << port << endl;
    }

    void schedulePackets() {
        for (int i = 0; i < num_ports; i++) {
            Packet pkt("", 0, 0);
            if (port_buffers[i].pop(pkt)) {
                scheduler.push(pkt);
                cout << "Packet '" << pkt.data << "' from port " << i << " scheduled" << endl;
            }
        }
    }

    void processPackets() {
        while (!scheduler.empty()) {
            Packet pkt = scheduler.top();
            scheduler.pop();

            processor.push(pkt);  // Push to stack for processing
            cout << "Processing packet '" << pkt.data << "'..." << endl;

            // Simulate processing
            Packet topPkt = processor.top();
            processor.pop();
            cout << "Packet '" << topPkt.data << "' processed" << endl;
        }
    }

    ~NetworkDevice() {
        delete[] port_buffers;
    }
};

int main() {
    int ports, bufferSize;
    cout << "Enter number of ports: ";
    cin >> ports;
    cout << "Enter buffer limit per port: ";
    cin >> bufferSize;

    NetworkDevice device(ports, bufferSize);

    int numPackets;
    cout << "Enter number of packets to send: ";
    cin >> numPackets;

    for (int i = 0; i < numPackets; i++) {
        string data;
        int port, priority;
        cout << "Packet " << (i + 1) << ":" << endl;
        cout << "Enter packet data: ";
        cin >> data;
        cout << "Enter destination port (0 to " << ports - 1 << "): ";
        cin >> port;
        cout << "Enter priority : ";
        cin >> priority;
        device.receivePacket(data, port, priority);
        cout << endl;
    }

    cout << "Scheduling packets..." << endl;
    device.schedulePackets();

    cout << "Processing packets..." << endl;
    device.processPackets();
}
