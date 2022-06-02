#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H
#include <iostream>

class HealthPoints
{
    private:
    int m_hp;
    int m_maxHp;

    friend bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2); 
    friend bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
    friend HealthPoints operator-(const int extraHealth, const HealthPoints& health);               
    friend std::ostream& operator<<(std::ostream& os , const HealthPoints& healthPoints);

    public:
    HealthPoints(int maxHp=100);
    //HealthPoints(HealthPoints& health)=defult
    //~HealthPoints()=defult    
    HealthPoints& operator+=(const int extraHealth); 
    HealthPoints operator+(const int extraHealth); 
    HealthPoints& operator-=(const int extraHealth); 
    HealthPoints operator-(const int extraHealth); 

    
    class InvalidArgument{};                                             
    
};

    HealthPoints operator+(const int extraHealth, const HealthPoints& health);            

    bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
    bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
    bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
    bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);



   



#endif //EX3_HEALTHPOINTS_H