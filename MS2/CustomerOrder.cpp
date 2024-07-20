#include "CustomerOrder.h"

#include <vector>

namespace seneca{
  size_t CustomerOrder::m_widthField=0;
 CustomerOrder::CustomerOrder(const std::string  &cusOrderRecord){
    Utilities util;
    size_t next_pos = 0;
    bool more = true;

    // Extract customer name
    m_name = util.extractToken(cusOrderRecord, next_pos, more);

     // Extract product name
    m_product = util.extractToken(cusOrderRecord, next_pos, more);


    // Handling remaining tokens 
    // Create the start_pos and then next_pos assign to it.

    size_t start_pos = next_pos;
    m_cntItem = 0;

    std::vector<std::string> itemNames;
    
    while (more) {
        
        std::string item =util.extractToken(cusOrderRecord, start_pos, more);
        // check if =" "
        if(item.size()){
            itemNames.push_back(item);
        }
        
        m_cntItem++;
    }
     //Allcoate memeory for items

    m_lstItem = new Item*[m_cntItem];

    for(size_t i =0;i <m_cntItem;i++){
        //create item 
        //so hard
        m_lstItem[i] = new Item(itemNames[i]);
    }
    //his constructor updates CustomerOrder::m_widthField if the current value is smaller than the value 
    //stored in Utilities::m_widthField.
    if(m_widthField<util.getFieldWidth()){
       m_widthField =util.getFieldWidth();
        
    }

 }

    CustomerOrder::CustomerOrder(const CustomerOrder &other) {
        throw std::string("ERROR: Cannot make copies.");
    }


// void fillItem(Station& station, std::ostream& os);
 void CustomerOrder::fillItem(Station& station, std::ostream& os){
    std::string itemName= station.getItemName();
    int index=-1;
    for (size_t i=0;i<m_cntItem; i++){
        if(m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled ){
            index=i;
            break;
        }
    }

    // items handled, and th Station's inventory contains at least one item, 
    if(index>-1){
        if(station.getQuantity()>=1){
            // subtracts 1 from the inventory 
            station.updateQuantity();
            //updates Item::m_serialNumber
            m_lstItem[index]->m_serialNumber = station.getNextSerialNumber();
            m_lstItem[index]->m_isFilled = true;
            os << "    Filled " + m_name + ", " + m_product + " [" + itemName + "]"
        << std::endl;
        }else{
            //if the order contains items handled but unfilled,
            os << "    Unable to fill " + m_name + ", PRODUCT [" + itemName + "]"
             << std::endl;
        }
    }

 }
 void CustomerOrder::display(std::ostream &os) const {
    os << m_name << " - " << m_product << std::endl;
    for (size_t i = 0; i < m_cntItem; i++) {
        os << "[";
        os.width(6);
        os.fill('0');
        os << m_lstItem[i]->m_serialNumber << "] ";
        os.fill(' ');
        os.width(m_widthField);
        os.setf(std::ios::left);
        os << m_lstItem[i]->m_itemName;
        os.unsetf(std::ios::left);
        os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED")
        << std::endl;
    }
    }

    bool CustomerOrder::isOrderFilled() const{
        for(size_t i =0;i<m_cntItem;i++){
            if(! m_lstItem[i]->m_isFilled){
                return false;
            }
        }
        return true;
    }

     CustomerOrder::CustomerOrder(CustomerOrder&& cusOrder)noexcept{

        *this = std::move(cusOrder);

     }

      CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cusOrder)noexcept{
        if(this !=&cusOrder){
            if(m_lstItem!=nullptr){
                for(size_t i =0;i< m_cntItem;i++){
                    delete m_lstItem[i];
                }
                 delete [] m_lstItem;
            }
           
            m_name=cusOrder.m_name;
            m_product = cusOrder.m_product;
            m_cntItem = cusOrder.m_cntItem;
            m_lstItem = cusOrder.m_lstItem;


            cusOrder.m_name="";
            cusOrder.m_product="";
            cusOrder.m_cntItem=0;
            cusOrder.m_lstItem=nullptr;
        }
        return *this;
        }

        CustomerOrder::~CustomerOrder() {
        if (m_lstItem != nullptr) {
            for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
            }
            delete[] m_lstItem;
        }
        }

         bool CustomerOrder::isItemFilled(const std::string& itemName)const{
             bool flag = true;
                for (size_t i = 0; i < m_cntItem; i++) {
                  if(m_lstItem[i]->m_itemName==itemName ){
                    flag = m_lstItem[i]->m_isFilled;
                    break;
                  }
                }
                return flag;
         }
}
       