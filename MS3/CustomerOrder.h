// Name: Hao Han Kao
// Seneca Student ID: 151604220
// Seneca email: hkao@myseneca.ca
// Date of completion: 2024/07/19
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"
#include "Utilities.h"
#include <cstddef>
#include <iostream>
#include <string>
namespace seneca {

struct Item {
  std::string m_itemName;
  size_t m_serialNumber{0};
  bool m_isFilled{false};

  Item(const std::string &src) : m_itemName(src){};
};

class CustomerOrder {
  std::string m_name{};
  std::string m_product{};
  size_t m_cntItem{};
  Item **m_lstItem{nullptr};
  // class variable =They can be accessed directly using the class name
  static size_t m_widthField;

public:
  CustomerOrder() = default;
  // reference to an unmodifiable string
  CustomerOrder(const std::string &cusOrderRecord);
  // a CustomerOrder object should not allow copy operations.
  CustomerOrder(const CustomerOrder &cusOrder);
  CustomerOrder operator=(const CustomerOrder &cusOrder) = delete;
  // move constructor. This constructor should
  //"promise" that it doesn't throw exceptions.
  CustomerOrder(CustomerOrder &&cusOrder) noexcept;
  CustomerOrder &operator=(CustomerOrder &&cusOrder) noexcept;

  //
  void fillItem(Station &station, std::ostream &os);
  void display(std::ostream &os) const;
  bool isOrderFilled() const;
  ~CustomerOrder();
  bool isItemFilled(const std::string &itemName) const;
};

} // namespace seneca

#endif