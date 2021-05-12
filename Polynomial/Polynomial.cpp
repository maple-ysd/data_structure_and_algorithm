#include "Polynomial.h"

using namespace std;

void Attach(double n, int i, Poly *prear)
{
    Poly pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation failed.\n";
        return;
    }
    pnew->coef = n;
    pnew->expo = i;
    pnew->next = nullptr;

    (*prear)->next = pnew;
    *prear = pnew;
}

Poly ReadPoly(istream &is)
{
    int n;
    is >> n;
    if (n <= 0)
    {
        cout << "empty polynomial.\n";
        return nullptr;
    }

    Poly front, rear, temp;
    front = new Node;       // create a head node
    front->next = nullptr;
    rear = front;

    double c = 0.0;
    int e = 0;
    while (n-- && is >> c >> e)
    {
        Attach(c, e, &rear);
    }
    temp = front;
    front = front->next;
    delete temp;        // delete the head node
    return front;
}

int compare(Poly p1, Poly p2)
{
    if (p1->expo == p2->expo)
        return 0;
    else if (p1->expo > p2->expo)
        return 1;
    else
        return -1;
}

Poly AddPoly(Poly p1, Poly p2)
{
    Poly t1 = p1, t2 = p2;
    Poly front, rear, temp;
    front = new Node;       // create a head node
    front->next = nullptr;
    rear = front;
    while (t1 && t2)
    {
        switch(compare(t1, t2))
        {
        case  0: if (t1->coef + t2->coef != 0) Attach(t1->coef + t2->coef, t1->expo, &rear); t1 = t1->next; t2 = t2->next; break;
        case  1: Attach(t1->coef, t1->expo, &rear); t1 = t1->next; break;
        case -1: Attach(t2->coef, t2->expo, &rear); t2 = t2->next; break;
        }
    }
    // deal with the remaining part
    while (t1)
    {
        Attach(t1->coef, t1->expo, &rear);
        t1 = t1->next;
    }
    while (t2)
    {
        Attach(t2->coef, t2->expo, &rear);
        t2 = t2->next;
    }
    temp = front;
    front = front->next;
    delete temp;
    return front;
}

Poly Mult1(Poly p1, Poly p2)
{
    if (!p1 || !p2) return nullptr;
    Poly t1 = p1, t2 = p2;
    Poly ret = nullptr;
    Poly prev = ret;

    Poly front, rear, temp;
    while (t1)
    {
        front = new Node;       // create a head node
        front->next = nullptr;
        rear = front;
        t2 = p2;
        while (t2)
        {
            Attach(t1->coef * t2->coef, t1->expo + t2->expo, &rear);
            t2 = t2->next;
        }
        temp = front;
        front = front->next;
        delete temp;            // delete head node

        prev = ret;
        ret = AddPoly(prev, front);
        // delete front list
        destroy(front);
        // delete previous ret list
        destroy(prev);
        t1 = t1->next;
    }
    return ret;
}

Poly Mult2(Poly p1, Poly p2)
{
    if  (!p1 || !p2) return nullptr;
    Poly t1 = p1, t2 = p2;
    Poly front, rear, temp;
    front = new Node;
    front->next = nullptr;
    rear = front;

    double c;
    int e;

    while (t2)
    {
        Attach(t1->coef * t2->coef, t1->expo + t2->expo, &rear);
        t2 = t2->next;
    }
    t1 = t1->next;
    while (t1)
    {
        t2 = p2; rear = front;
        while (t2)
        {
            c = t1->coef * t2->coef;
            e = t1->expo + t2->expo;
            while (rear->next && rear->next->expo > e)
                rear = rear->next;
            if (rear->next && rear->next->expo == e)
            {
                if (rear->next->coef + c)
                    rear->next->coef += c;
                else
                {
                    temp = rear->next;
                    rear->next = temp->next;
                    delete temp;
                }
            }
            else
            {
                temp = new Node;
                temp->coef = c;
                temp->expo = e;
                temp->next = rear->next;
                rear->next = temp;
            }
            t2 = t2->next;
        }
        t1 = t1->next;
    }
    temp = front;
    front = front->next;
    delete temp;
    return front;
}

int Size(Poly p)
{
    int sz = 0;
    while (p)
    {
        ++sz;
        p = p->next;
    }
    return sz;
}

void Print(Poly p)
{
    if (!p)
    {
        cout << "empty polynomial.\n";
        return;
    }
    cout << Size(p) << "\t";    // this sentence is optional, just to show how many terms in the polynomial
    int flag = 0;
    while (p)
    {
        if (!flag)
            flag = 1;
        else
            cout << "\t";
        cout << p->coef << " " << p->expo;
        p = p->next;
    }
}
void destroy(Poly p)
{
    Poly temp;
    while (p)
    {
        temp = p;
        p = p->next;
        delete temp;
    }
}
