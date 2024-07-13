// Name: Hao Han Kao 
// Seneca Student ID: 151604220 
// Seneca email: hkao@myseneca.ca
// Date of completion: 2024/07/12
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Utilities.h"

namespace seneca{
         char Utilities::m_delimiter=' ';
        void Utilities::setFieldWidth(size_t newWidth){
            m_withField=newWidth;
        }
        size_t Utilities::getFieldWidth() const{
            return m_withField;
        }
        //example:
            // "itemName     ,12345,   10,   This is a description     ";
            // next_pos最大值就是最後長度index
        std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
           //edge case
            if(next_pos > str.length()-1) {
                more=false;
                return "";
            }
     
            //return index  找到,的數字
            //沒找到會回傳std::npos 
            size_t foundIndex =str.find(m_delimiter,next_pos);
            //reports an exception if a delimiter is found at next_pos.
            if(next_pos==foundIndex){
                 more=false;
                throw std::runtime_error("Delimiter is found at  next_pos");
            }
            if(foundIndex==std::string::npos ){
                more=false;
                std::string token = str.substr(next_pos);
                token.erase(0,token.find_first_not_of(" "));
                token.erase(token.find_last_not_of(" ")+1);
                return token;
            }
            //找到itemName     , 
            //用substr() 第一個arg放起始位子 第二筆放切到哪裡
            //用箱子裝起來 

            std::string token = str.substr(next_pos,foundIndex-next_pos);
            //remove space
            token.erase(0,token.find_first_not_of(" "));
            token.erase(token.find_last_not_of(" ")+1);

            //更新next_pos 位置= foundIndex+1
            next_pos =foundIndex+1;
            more=true;
            if(token.length()>m_withField) {
                m_withField =token.length();
            }
            return token;
            
            

        }
        //初始化
        void Utilities::setDelimiter(char newDelimiter){
            m_delimiter=newDelimiter;
        }
         char Utilities::getDelimiter() {
            return m_delimiter;
        }

}