#include <sys/time.h>

class StopWatch
{
public:
   void begin ()
   {
      gettimeofday( &start, NULL );
   }

   void stop ()
   {
      gettimeofday( &end, NULL );
   }

   double duration ()
   {
      return ((end.tv_sec - start.tv_sec)*1000.0 +
	      (end.tv_usec - start.tv_usec)/1000.0 );
   }

private:
   struct timeval start;
   struct timeval end;
};
