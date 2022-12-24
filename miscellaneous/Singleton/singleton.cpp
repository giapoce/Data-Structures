#include <iostream>
 
template<typename T> class Singleton
{
  public:
    static T& Instance()
    {
        static T theSingleInstance;  // assumes T has a protected default constructor
        return theSingleInstance;
    }
};
 
class OnlyOne : public Singleton<OnlyOne>
{
    friend class Singleton<OnlyOne>;
    int example_data;
  public:
    int Getexample_data() const {return example_data;}
  protected: 
    OnlyOne(): example_data(42) {}   // default constructor 
};
 
#define ReferenceName OnlyOne::Instance()
 
/* This test case should print "42". */
#include <iostream>
int main()
{
    std::cout<< ReferenceName.Getexample_data()<<std::endl;
    return 0;
}
