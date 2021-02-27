#include <iostream>
#include <vector>
#include <string>

bool is_size_ok(int size)
{
    const int max_size = 1024;

    if (size <= 0 || size > max_size)
    {
        std::cerr << "Oops: requested size is not supported: "
                << size << " -- can't fulfill request." << std::endl;

        return false;
    }

    return true;
}

const std::vector<int>* fibon_seq(int size)
{
    static std::vector<int> elems;

    if (!is_size_ok(size))
    {
        return 0;
    }

    for (int ix = elems.size(); ix < size; ++ix)
    {
        if (ix == 0 || ix == 1)
        {
            elems.push_back(1);
        }
        else
        {
            elems.push_back(elems[ix - 2] + elems[ix - 1]);
        }
    }

    return &elems;
}

const std::vector<int>* pent_seq(int size)
{
    static std::vector<int> elems;

    if (!is_size_ok(size))
    {
        return 0;
    }

    for (int ix = elems.size(); ix < size; ++ix)
    {
        elems.push_back((ix + 1) * (3 * (ix + 1) - 1) / 2);
    }

    return &elems;
}

void display_message(const std::string& msg)
{
    std::cout << msg;
}

inline bool seq_elem(int pos, int& elem, const std::vector<int>* (*seq_ptr)(int))
{
    if (!seq_ptr)
    {
        display_message("Internal Error: seq_ptr is set to null!");
    }

    const std::vector<int>* pseq = seq_ptr(pos);

    if (!pseq)
    {
        elem = 0;

        return false;
    }

    elem = (*pseq)[pos - 1];

    return true;
}

void print_sequence(const std::vector<int>& elems, std::string& elemType)
{

    std::cout << "Type of element: " << elemType << std::endl;

    for (int ix = 0; ix < elems.size(); ++ix)
    {
        std::cout << elems[ix] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    int pos;
    std::cout << "Please enter a position: ";
    std::cin >> pos;

    std::string elemType;
    std::cout << "Please enter a type of element (fibon/pent): ";
    std::cin >> elemType;

    std::vector<int>* elems;

    if (elemType == "fibon")
    {
        int elem;

        if (seq_elem(pos, elem, fibon_seq))
        {
            std::cout << "element # " << pos
                    << " is " << elem << std::endl;
            print_sequence(*fibon_seq(pos), elemType);
        }
    }
    else if (elemType == "pent")
    {
        int elem;

        if (seq_elem(pos, elem, pent_seq))
        {
            std::cout << "element # " << pos
                    << " is " << elem << std::endl;
            print_sequence(*pent_seq(pos), elemType);
        }
    }
}