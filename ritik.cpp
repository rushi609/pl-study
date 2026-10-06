#include<iostream>
using namespace std;

class Animal
{
public:
void sound()
{
cout<<"Animal makes a sound"<<endl;
}
};
class Dog : public Animal
{
public:
void sound()
{
cout<<"Dog barks"<<endl;
}
};

class Cat : public Animal
{
public:
void sound()
{
cout<<"Cat meows"<<endl;
}
};

class Cow : public Animal
{
public:
void sound()
{
cout<<"Cow moos"<<endl;
}
};

int main()
{
Dog d;
d.sound();

Cat c;
c.sound();

Cow cow;
cow.sound();

return 0;
}
