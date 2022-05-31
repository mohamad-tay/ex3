#include "HealthPoints.h"
#include <iostream>


//const int MAX_HEALTH_DEFAULT = 100;


HealthPoints::HealthPoints(int maxHp)
{
    if(maxHp<=0)
    {
        //HealthPoints::InvalidArgument error();
        throw InvalidArgument();                                        // b3rfsh aethafe 7agy
    }                       
    else
    {
        m_hp = maxHp;
        m_maxHp = maxHp;
    }
}


HealthPoints& HealthPoints::operator+=(const int extraHealth)
{
    if((m_hp+extraHealth)>m_maxHp)
    {
        m_hp = m_maxHp;
    }
    else if((m_hp+extraHealth)<0)
    {
        m_hp = 0;
    }
    else
    {
        m_hp += extraHealth;
    }
    return *this;
}


HealthPoints HealthPoints::operator+(const int extraHealth) 
{
    HealthPoints result(*this);
    return(result += extraHealth);
}

HealthPoints& HealthPoints::operator-=(const int extraHealth)
{
    int temp = (-1)*(extraHealth);
    return *this += temp;
}


HealthPoints HealthPoints::operator-(const int extraHealth) 
{
    HealthPoints result(*this);
    return(result -= extraHealth);
}

//------------------------------------------------------------------------------------------------

HealthPoints operator+(const int extraHealth, const HealthPoints& health) 
{
    HealthPoints result(health);        //bzbt health+extraHealth ??
    return(result += extraHealth);
 }


 HealthPoints operator-(const int extraHealth, const HealthPoints& health) 
 {
    HealthPoints result(health);             
    result.m_hp = (-1)*result.m_hp ;        
    return result += extraHealth;
}

 //-------------------------------------------------------------------------------------------------

bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2)
{
    return(healthPoints1.m_hp == healthPoints2.m_hp);
}

bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2)
{
    return(!( healthPoints1 ==  healthPoints2));
}

bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2)
{
    if( healthPoints1.m_hp < healthPoints2.m_hp)
    {
        return true;
    }
    return false;
}

bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2)
{
    if(!(healthPoints1 < healthPoints2) && (healthPoints1 !=  healthPoints2) )
    {
        return true;
    }
    return false;
}

bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2)
{
    return(!(healthPoints1 > healthPoints2));
}

bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2)
{
    return(!(healthPoints1 < healthPoints2));
}


std::ostream& operator<<(std::ostream& os , const HealthPoints& healthPoints)
{
    os << healthPoints.m_hp << "(" << healthPoints.m_maxHp  << ")";
    return os;      
}