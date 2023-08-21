#include "vec.h"


data_t dotproduct(vec_ptr u, vec_ptr v) {
   data_t sum = 0;

   long length = vec_length(u);
   data_t *udata = get_vec_start(u);
   data_t *vdata = get_vec_start(v);
   for (long i = 0; i < length; i++) { // we can assume both vectors are same length
      sum += udata[i] * vdata[i];
   }
   return sum;
}
