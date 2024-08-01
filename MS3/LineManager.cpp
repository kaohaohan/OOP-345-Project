#include "LineManager.h"
#include <iostream>
#include <fstream>
#include "Utilities.h"

namespace seneca{
    //so freakishly hard
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
        std::ifstream  sourceFile(file);
        if(!sourceFile){
            throw std::string("Can't open [") + file + "] file.";
        }
        //box
        //findStation 

        m_cntCustomerOrder = g_pending.size();

        Utilities u;
        u.setDelimiter('|');
        
        std::string line;
        std::vector <std::string> secondStations;
        
        while (std::getline(sourceFile, line)) { // Corrected getline syntax
            size_t next_pos =0;
            bool more=true;
            std::string firstStation = u.extractToken(line, next_pos, more);
            std::string secondStation="";

            if (more) {
                secondStation = u.extractToken(line, next_pos, more);
            }

            if(!secondStation.empty()){
                secondStations.push_back(secondStation);
            }else{
                secondStations.push_back(firstStation);
            }

            auto it = std::find_if(stations.begin(), stations.end(), [firstStation](Workstation* station) {
                return firstStation ==station->getItemName();
            });
            
            // Check if the element was found
            if (it != stations.end()) {
                m_activeLine.push_back(*it);
            } else {
                std::cout << "First station Not found" << std::endl;
            }

            if (!secondStation.empty()) {
                //second
                auto it2 = std::find_if(stations.begin(), stations.end(), [secondStation](Workstation* station) {
                    return secondStation ==station->getItemName();
                });
                
                if (it2  != stations.end()) {
                    m_activeLine.back()->setNextStation(*it2);          
                } else {
                    m_activeLine.back()->setNextStation(nullptr);
                }
            }

            

        }
        //find first station 
       for(auto &station :m_activeLine){
          auto it =std::find_if(secondStations.begin(), secondStations.end(),[station](std::string stationName){
            return station->getItemName() == stationName;
          });
          if(it ==secondStations.end()){
                m_firstStation=station;
                break;
          }
        }
        
    }

    void LineManager::reorderStations(){
       std::vector<Workstation*> stations;
        Workstation* currentStation = m_firstStation ;
        while(currentStation){
            stations.push_back(currentStation);
            currentStation=currentStation->getNextStation();
        }
        m_activeLine = stations;
    }
    bool LineManager::run(std::ostream& os){
//keeps track of the current iteration number (use a local variable)
        static size_t count=0;
        //inserts into stream os the iteration number
        //how many times this function has been called by the client
        os << "Line Manager Iteration: " << ++count << std::endl;
        //moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue. 
        //This function moves only one order to the line on a single iteration.
        if(!g_pending.empty()){
            *m_firstStation += std::move(g_pending.front());
            // remove it from the queue. 
           g_pending.pop_front();

        }

 
        //for each station on the line, executes one fill operation
        for(auto &station :m_activeLine){
            station->fill(os);
        }
        //each station on the line, attempts to move an order down the line
        for(auto &station :m_activeLine){
            station->attemptToMoveOrder();
        }
        //return true if all customer orders have been filled or cannot be filled, otherwise returns false.
        bool allComplete=(g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
        return allComplete;
    }
    // this query displays all active stations on the assembly line in their current order
    void LineManager::display(std::ostream& os) const{
        for(auto &station :m_activeLine){
            station->display(os);
        }

    }
}