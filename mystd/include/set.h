#ifndef SET_H
#define SET_H



namespace mystd
{


class set
{
private:

    template<class T>
    struct node
    {
        T val;
        struct node* left;
        struct node* right;
    };

    struct node* root;  
    int size;
    
  
 


public:
    set (/* args */);
    ~set ();
};

set::set (/* args */)
{}

set::~set ()
{}



} // namespace mystd



#endif
