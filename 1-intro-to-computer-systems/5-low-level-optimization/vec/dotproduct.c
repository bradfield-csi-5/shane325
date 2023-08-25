#include "vec.h"


data_t dotproduct(vec_ptr u, vec_ptr v) {
   data_t sum = 0;

   long i;
   long length = vec_length(u);
   long limit = length - 1;
   data_t *udata = get_vec_start(u);
   data_t *vdata = get_vec_start(v);
   for (i = 0; i < limit; i+=2) { // we can assume both vectors are same length
      sum += (udata[i] * vdata[i]) + (udata[i+1] * vdata[i+1]);
   }

   for (; i < length; i++) {
      sum += udata[i] * vdata[i];
   }
   return sum;
}
