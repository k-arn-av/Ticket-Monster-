
#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include "Ticket.hpp"

class BinaryHeap{

    public:
        enum class HeapType{
            MIN,
            MAX
        };

    private:
        HeapType type;
        std::vector<Ticket>elements;//contiguous array for storing tickets, uses parent/child indices instead of pointers

        //helper methods for restoring heap order; the type decides what element should move above another

        bool higherPriority(const Ticket& first_ticket, const Ticket& second_ticket)const;
        void heapifyUp(size_t givenIndex);
        void heapifyDown(size_t givenIndex);
        size_t findIndexById(int ticketId)const;

    public:
        //constructor: takes a user selected heap type, MAX by default for ticket prioritization
        BinaryHeap(HeapType selected_type=HeapType::MAX): type(selected_type), elements(){}

        //heap operations
        void heappush(const Ticket& ticket);
        Ticket heappop();
        Ticket peek()const; //returns the root without modifying the elements
        void heapify(const std::vector<Ticket>& user_data); //converts existing ticket data into a heap according to type

        //ticket modifications; id is used to locate the element in the vector
        bool removeById(int ticketId);
        bool updatePriority(int ticketId, int newPriority);
        bool updateDescription(int ticketId, const std::string& new_description);
        bool findTicket(int ticketId, Ticket& result)const;
        std::vector<Ticket> getTickets()const; //returns a priority ordered copy for displaying/saving, original heap stays unchanged

        //getters
        bool isEmpty()const { return elements.empty();}
        size_t size()const { return elements.size();}
};
