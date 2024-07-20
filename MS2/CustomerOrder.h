#ifndef SENECA_CUSTOMERORDER
#define SENECA_CUSTOMERORDER
#include <cstddef>
#include <string>
#include <iostream>
#include "Utilities.h"
#include "Station.h"
namespace seneca{
   
   
   
    struct Item
{
	std::string m_itemName;
	size_t m_serialNumber{0};
	bool m_isFilled{false};

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder{
    std::string m_name{};
    std::string m_product{};
    size_t m_cntItem{};
    Item** m_lstItem{nullptr};
    //class variable =They can be accessed directly using the class name 
     static size_t m_widthField; 
    public:
    CustomerOrder()=default;
    // reference to an unmodifiable string
    CustomerOrder(const std::string & cusOrderRecord);
    //a CustomerOrder object should not allow copy operations.
    CustomerOrder(const CustomerOrder& cusOrder );
    CustomerOrder operator=(const CustomerOrder& cusOrder )=delete;
    //move constructor. This constructor should 
    //"promise" that it doesn't throw exceptions. 
    CustomerOrder(CustomerOrder&& cusOrder)noexcept;
    CustomerOrder& operator=(CustomerOrder&& cusOrder)noexcept;

    //
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream &os) const;
    bool isOrderFilled() const;
    ~CustomerOrder();
    bool isItemFilled(const std::string& itemName)const;
};

}


#endif