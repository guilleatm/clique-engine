#ifndef ERROR_MACROS_H
#define ERROR_MACROS_H

#include <iostream>

#define ERROR_IF(condition)                                                         \
    if (condition)                                                                  \
    {                                                                               \
        std::cout << "Error at " << __FILE__ << " line: " << __LINE__ << std::endl; \
    }

#define ERROR_MSG_IF(condition, message)                                                                    \
    if (condition)                                                                                      \
    {                                                                                                   \
        std::cout << "Error at " << __FILE__ << " line: " << __LINE__ << ". " << message << std::endl;  \
    }


#endif // ERROR_MACROS_H