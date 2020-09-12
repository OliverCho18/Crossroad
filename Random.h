#ifndef __random_h__
#define __random_h__

#include <random>

class Random
{
   protected:
     static std::mt19937 rng;
     static std::uniform_int_distribution<int>     randint01;
     static std::uniform_real_distribution<double> randdouble;

   public:
      inline static int  randint() { return Random::randint01(Random::rng); }
      inline static int  randint(int a, int b)
      {
         double u = Random::randdouble(Random::rng);
         int    mappedValue = a + (int)((b - a + 1)*u);
         return(mappedValue);
      }
      inline static double randdouble01()
      {
        return Random::randdouble(Random::rng);
      }
};

// static members must be defined @ file-level scope

#endif