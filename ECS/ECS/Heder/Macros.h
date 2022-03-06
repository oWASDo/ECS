#pragma once
//#include <vector>
//#include <memory>


#define MACRO(X,Y) \
 ( \
  (cout << "1st arg is:" << (X) << endl), \
  (cout << "2nd arg is:" << (Y) << endl), \
  (cout << "3rd arg is:" << ((X) + (Y)) << endl), \
  (void)0 \
 )

#define NotExistKeyInMap(map, element) \
 ( \
  map.find(element) == map.end() \
 )

#define ExistKeyInMap(map, element) \
 ( \
  map.find(element) != map.end() \
 )



#define ExistElementInVector(vector, element) \
 ( \
std::find(std::begin(vector), std::end(vector), element) == std::end(vector) \
)



#define MaxComponentPeEntyty 7

