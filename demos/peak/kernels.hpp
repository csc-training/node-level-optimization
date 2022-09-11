#include <stdio.h>
#include <omp.h>

// Template metaprogramming for unrolling N operations

// Fused multiply add
template<int N, typename T> class FMA {
  public:
     static void fma(T* fa, T* fb, T* fc) {
        // register T *far = fa;
        // *far = (*far) * (*fb) + (*fc);
        *fa = (*fa) * (*fb) + (*fc);
        FMA<N-1, T>::fma(fa + VECTOR_WIDTH, fb, fc);
      }
};

template<typename T> class FMA<0,T> {
  public:
     static void fma(T* fa, T* fb, T* fc) {
        return;
     }
};

template <int N, typename T> inline void fma(T* fa, T* fb, T* fc)
{
    FMA<N, T>::fma(fa, fb, fc);
}

// Multiply
template<int N, typename T> class MUL {
  public:
     static void mul(T* fa, T* fb, T* fc) {
        *fa = (*fa) * (*fb); 
        MUL<N-1, T>::mul(fa + VECTOR_WIDTH, fb, fc);
      }
};

template<typename T> class MUL<0,T> {
  public:
     static void mul(T* fa, T* fb, T* fc) {
        return;
     }
};

template <int N, typename T> inline void mul(T* fa, T* fb, T* fc)
{
    MUL<N, T>::mul(fa, fb, fc);
}

// Add
template<int N, typename T> class ADD {
  public:
     static void add(T* fa, T* fb, T* fc) {
        *fa = (*fa) + (*fc);
        ADD<N-1, T>::add(fa + VECTOR_WIDTH, fb, fc);
      }
};

template<typename T> class ADD<0,T> {
  public:
     static void add(T* fa, T* fb, T* fc) {
        return;
     }
};

template <int N, typename T> inline void add(T* fa, T* fb, T* fc)
{
    ADD<N, T>::add(fa, fb, fc);
}

// Divide
template<int N, typename T> class DIV {
  public:
     static void div(T* fa, T* fb, T* fc) {
        *fa = (*fa) / (*fb); 
        DIV<N-1, T>::div(fa + VECTOR_WIDTH, fb, fc);
      }
};

template<typename T> class DIV<0,T> {
  public:
     static void div(T* fa, T* fb, T* fc) {
        return;
     }
};

template <int N, typename T> inline void div(T* fa, T* fb, T* fc)
{
    DIV<N, T>::div(fa, fb, fc);
}

