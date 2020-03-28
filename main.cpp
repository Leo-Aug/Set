#include <iostream>
#include <algorithm>

int *int_add(int *p_insert, int *end, int data);
int *int_int(int *begin, const int *end, int data);
int *int_del(int *p_del, const int *end);


class MySet
{
    int s[10];
    int size;
public:
    MySet(int *list, int size);
    MySet();
    bool add(int data);
    bool del(int data);
    MySet operator+(MySet S);
    MySet operator*(MySet S);
    friend std::ostream &operator<<(std::ostream &os, const MySet &S);
};

MySet::MySet() = default;

MySet::MySet(int *list, int size)
{
    std::sort(list, list + size);
    int *end = std::unique(list, list + size);
    this->size = (int)(end - list);
    for(int *begin = list, *s_begin = s;begin != end;begin++, s_begin++)
    {
        *s_begin = *begin;
    }
}

bool MySet::add(int data)
{
    int *begin = s;
    int *end = s + size;
    int *p_insert = int_int(begin, end, data);
    if(size == 0 && data == 0)
    {
        size++;
        return true;
    }
    if(*p_insert != data)
    {
        if(size < 10)
        {
            if(size < 10)
            {
                int_add(p_insert, end, data);
                size++;
            }
            else
            {
                std::cout << "This set is full!" << std::endl;
            }
        }
        else
        {
            std::cerr << "This set is full" << std::endl;
            return false;
        }
    }
    return true;
}

bool MySet::del(int data)
{
    int *begin = s, *end = s + size;
    int *p_del = int_int(begin, end, data);
    if(p_del == end && data == 0)return false;
    if(*p_del == data)
    {
        int_del(p_del, end);
        size--;
        return true;
    }
    else
        return false;
}

MySet MySet::operator+(MySet S)
{
    int *begin = S.s;
    for(int *p = s;p != s+size;p++)
    {
        int *p_insert = int_int(begin, S.s+S.size, *p);
        if(*p_insert != *p)
        {
            int_add(p_insert, S.s+S.size, *p);
            S.size++;
        }
        begin = p_insert;
    }
    return S;
}

MySet MySet::operator*(MySet S)
{
    int *begin = s, *end = s + size;
    for(int *p = S.s;p != S.s + S.size;p++)
    {
        begin = int_int(begin, end, *p);
        if(*begin != *p)
        {
            int_del(p, S.s+S.size);
            S.size--;
            continue;
        }
    }
    return S;
}

int *int_add(int *p_insert, int *end, int data)
{
    for(int *pp = end;pp != p_insert;pp--)
    {
        pp[0] = pp[-1];
    }
    *p_insert = data;
    return p_insert;
}

int *int_int(int *begin, const int *end, int data)
{
    int *p = begin;
    while(p != end && data > *p)
    {
        p++;
    }
    return p;
}

int *int_del(int *p_del, const int *end)
{
    for(int *p = p_del;p != end - 1;p++)
    {
        p[0] = p[1];
    }
    return p_del;
}

std::ostream &operator<<(std::ostream &os, const MySet &S)
{
    const int *p;
    for(p = S.s;p < S.s + S.size;p++)
    {
        os << *p << ' ';
    }
    return os;
}

int main()
{
    int a[4] = {1, 2, 2, 3};
    int b[8] = {3, 4, 5, 6, 7, 8, 9, 10};
    MySet s1(a, 4), s2(b, 8);
    s1 = s1 + s2;
    std::cout << s1 << std::endl;
    s2 = s1 * s2;
    std::cout << s2 << std::endl;
    s2.del(3);
    std::cout << s2 << std::endl;
    s2.add(1);
    s2.add(2);
    s2.add(11);
    s2.add(13);
    s2.add(14);
    std::cout << s2 << std::endl;

    return 0;
}
