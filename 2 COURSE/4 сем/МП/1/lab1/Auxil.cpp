 #include "Auxil.h" 
#include <ctime>    
namespace auxil
{
     // функция устанавливает в качестве начального числа для        
     // генератора псевдослучайных чисел текущее значение 
     // системного времени в фомате функции time()
    void start()                          
    {
        srand((unsigned)time(NULL));
    };
    // функция возвращает действительное псевдослучайное число в              
    // диапазоне оn rmin до  rmax
    double dget(double rmin, double rmax) 
    {
        return ((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin;
    };
    int iget(int rmin, int rmax)        
    {
        return (int)dget((double)rmin, (double)rmax);
    };
}