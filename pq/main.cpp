#include <bits/stdc++.h>

using namespace std;

class pq {
public:
    class Node {
    private:
        Node* top {nullptr};
        Node* left {nullptr};
        Node* right {nullptr};
    public:
        friend class pq;
        int value {0};

        Node() = default;
        Node(int n, Node* top);
        Node* get_top();
        Node* get_left();
        Node* get_right();
        void set_left(Node* m);
        void set_right(Node* m);
        int value_();
        ~Node() = default;
    };

    Node* first {nullptr};
    Node* last {nullptr};

    pq() = default;
    pq(const pq& copy);
    ~pq() = default;

    int front();
    int back();
    bool empty();
    void push_back(int add);
    int pop_front();
};

pq::Node::Node(int n, Node* top_) {
    value = n;
    top = top_;
}

pq::Node* pq::Node::get_top() { return (*this).top; }
pq::Node* pq::Node::get_left() { return (*this).left; }
pq::Node* pq::Node::get_right() { return (*this).right; }

void pq::Node::set_left(Node* m) { left = m; }
void pq::Node::set_right(Node* m) { right = m; }

pq::pq(const::pq& copy) {
    *this = copy;
}

int pq::Node::value_() {
    return value;
}

void pq::push_back(int add) {
    if (first == nullptr) {
        first = new Node(add, nullptr);
        return;
    }

    if (first->get_left() == nullptr) {
        first->set_left(new Node(add, first));
        auto at = first->get_left();
        if (first->value_() > at->value_()) swap(at->value, first->value);
        last = first->get_left();
        return;
    }

    auto at = last;
    if (at->get_top()->get_right() == nullptr) {
        at->get_top()->set_right(new Node(add, at->get_top()));
        last = at = at->get_top()->get_right();
    } else {
        while (at->get_top() != first && at->get_top()->get_left() != at) { at = at->get_top(); }
        if (at->get_top()->get_left() == at) at = at->get_top()->get_right();
        else at = at->get_top()->get_left();
        while (at->get_left() != nullptr) { at = at->get_left(); }
        at->set_left(new Node(add, at));
        last = at = at->get_left();
    }

    while (at->get_top() != nullptr && at->value < at->get_top()->value) {
        swap(at->value, at->get_top()->value); at = at->get_top();
    }
}

int pq::pop_front() {
    int res = first->value;
    auto at = last, prelast = last;

    if (last == nullptr) {
        int n = first->value;
        first = new Node();
        return n;
    }

    if (first->get_right() == nullptr) {
        int n = first->value;
        first = last;
        last = nullptr;
        return n;
    }

    swap(first->value, last->value);

    while (at->get_top() != first && at->get_top()->get_left() == at) { at = at->get_top(); }
    if (at->get_top()->get_right() == at) {
        at = at->get_top()->get_left();
        while (at->get_left() != nullptr) { at = at->get_right(); }
        last = at;
    }
    else {
        at = at->get_top();
        while (at->get_left() != nullptr) { at = at->get_right(); }
        last = at;
    }

    if (prelast->get_top()->get_right() == nullptr) prelast->get_top()->set_left(nullptr);
    else prelast->get_top()->set_right(nullptr);

    at = first;
    while (at->get_left() != nullptr) {
        auto tmp = at->get_left();
        if (at->get_right() != nullptr && at->get_right()->value <= at->get_left()->value) tmp = at->get_right();
        if (tmp->value < at->value) {
            swap(at->value, tmp->value);
            at = tmp;
        } else break;
    }
    return res;
}

int pq::front() {
    return first->value_();// + first->get_left()->value_() + first->get_left()->get_left()->get_left()->value_();
}

int main() {
    string s;
    pq p;
    p.push_back(100);
    p.push_back(10);
    p.push_back(1000);
    p.push_back(1);
    p.push_back(100);
    p.push_back(1000);
    p.push_back(200);
    while (cin >> s) {
        int n = p.pop_front();
        cout << n << endl;
    }
}