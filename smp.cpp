#include <iostream>
template <typename Type>
class SMP{
private:
    Type *p;
public:
    SMP(Type *ptr){
        p=ptr;
    }
    ~SMP(){
        delete p;
        std::cout<<"Destructor was called"<<'\n';
    }
    Type& operator*(){
        return *p;
    }
};
