// Name: Hao Han Kao 
// Seneca Student ID: 151604220 
// Seneca email: hkao@myseneca.ca
// Date of completion: 2024/07/12
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <cstddef>
#include <string>
#include <iostream>
namespace seneca{
 class Station{
    //Instance Variables

    int m_id{};
    std::string m_item{};
    std::string m_description{};
    size_t m_serialNumber{};
    size_t m_currentStockNum{};

    //class Variables 
    //shared 
    static size_t m_widthField;
    static size_t id_generator;

    public:
    Station()=default;
     Station(const std::string & line);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
 };



}
#endif