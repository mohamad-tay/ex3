#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H


class HealthPoints
{
    private:
    int m_hp;
    int m_maxHp;

    public:
    HealthPoints(int maxHp=100);
    HealthPoints(HealthPoints health&)=defult;
    ~HealthPoints()=defult;    
    HealthPoints& operator+=(const int extraHealth); 
    HealthPoints operator+(const int extraHealth) const; 
    HealthPoints& operator-=(const int extraHealth) const;
    HealthPoints operator-(const int extraHealth); 

    HealthPoints operator+(const int extraHealth, const HealthPoints& health) const;           //fsh 7agy refrence lano int
    HealthPoints operator-(const int extraHealth, const HealthPoints& health) const;           // rkm-h?? 

    bool operator==(const HealthPoints healthPoints1, const HealthPoints healthPoints1);        //friend??
    bool operator!=(const HealthPoints healthPoints1, const HealthPoints healthPoints1);
    bool operator<(const HealthPoints healthPoints1, const HealthPoints healthPoints1);
    bool operator>(const HealthPoints healthPoints1, const HealthPoints healthPoints1);
    bool operator<=(const HealthPoints healthPoints1, const HealthPoints healthPoints1);
    bool operator>=(const HealthPoints healthPoints1, const HealthPoints healthPoints1);

    friend std::ostream& operator<<(std::ostream os , const HealthPoints healthPoints);



    class InvalidArgument{ int m_Invalid;};
    
};






#endif //EX3_HEALTHPOINTS_H