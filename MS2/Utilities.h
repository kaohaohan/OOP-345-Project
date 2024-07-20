// Name: Hao Han Kao 
// Seneca Student ID: 151604220 
// Seneca email: hkao@myseneca.ca
// Date of completion: 2024/07/12
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.



#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <cstddef>
#include <string>
namespace seneca{
    class Utilities{
        size_t m_withField=1;
        //class variable
        //go to cpp 
        static char m_delimiter;
        public:

        //memeber funntion 
        void setFieldWidth(size_t newWidth);

        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        //class function 
        //every object can use those function 
        static void setDelimiter(char newDelimiter);
        static char getDelimiter() ;

     };
}

#endif