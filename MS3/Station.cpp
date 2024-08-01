// Name: Hao Han Kao
// Seneca Student ID: 151604220
// Seneca email: hkao@myseneca.ca
// Date of completion: 2024/07/19
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Station.h"
#include "Utilities.h"

namespace seneca {
size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station(const std::string &line) {
  m_id = ++id_generator;

  Utilities util;
  size_t next_pos = 0;
  bool more = true;
  m_item = util.extractToken(line, next_pos, more);
  // casting to string type
  m_serialNumber = std::stoi(util.extractToken(line, next_pos, more));
  m_currentStockNum = std::stoi(util.extractToken(line, next_pos, more));
  if (m_widthField < util.getFieldWidth()) {
    m_widthField = util.getFieldWidth();
  }
  m_description = util.extractToken(line, next_pos, more);
}

const std::string &Station::getItemName() const { return m_item; }

size_t Station::getNextSerialNumber() { return m_serialNumber++; }
size_t Station::getQuantity() const { return m_currentStockNum; }
void Station::updateQuantity() {
  m_currentStockNum -= 1;
  if (m_currentStockNum < 0) {
    m_currentStockNum = 0;
  }
}
void Station::display(std::ostream &os, bool full) const {
  os.width(3);
  os.fill('0');
  os << m_id << " | ";

  os.width(m_widthField);
  os.fill(' ');
  os.setf(std::ios::left);
  os << m_item << " | ";
  os.unsetf(std::ios::left);

  os.width(6);
  os.fill('0');
  os << m_serialNumber << " | ";
  os.fill(' ');

  if (full) {
    os.width(4);
    os << m_currentStockNum << " | ";

    os << m_description << std::endl;
  } else {
    os << std::endl;
  }
}

} // namespace seneca