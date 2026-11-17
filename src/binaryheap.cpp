
#include "BinaryHeap.hpp"
#include <utility>

bool BinaryHeap::higherPriority(const Ticket& first_ticket, const Ticket& second_ticket)const{
    if (first_ticket.priority == second_ticket.priority){
        return first_ticket.id < second_ticket.id; //earlier ticket ids come first when the priorities match
    }

    if (type == HeapType::MAX){
        return first_ticket.priority > second_ticket.priority;
    }
    else{
        return first_ticket.priority < second_ticket.priority;
    }
}

void BinaryHeap::heapifyUp(size_t givenIndex){
    while (givenIndex > 0){
        size_t parent = (givenIndex-1)/2;

        if (!higherPriority(elements[givenIndex], elements[parent])){
            break;
        }

        std::swap(elements[givenIndex], elements[parent]);
        givenIndex=parent;
    }
}

void BinaryHeap::heapifyDown(size_t givenIndex){
    while (true){
        size_t left = 2*givenIndex+1;
        size_t right = 2*givenIndex+2;
        size_t best = givenIndex;

        if (left<elements.size() && higherPriority(elements[left], elements[best])){
            best=left;
        }
        if (right<elements.size() && higherPriority(elements[right], elements[best])){
            best=right;
        }
        if (best == givenIndex){
            break;
        }

        std::swap(elements[givenIndex],elements[best]);
        givenIndex=best;
    }
}

void BinaryHeap::heapify(const std::vector<Ticket>& user_data){
    elements=user_data;

    //starts from the last parent and moves toward the root, no reason to process leaf elements since they are heaps already
    for (size_t i=elements.size()/2; i>0; --i){
        heapifyDown(i-1);
    }
}

void BinaryHeap::heappush(const Ticket& ticket){
    elements.push_back(ticket);
    heapifyUp(elements.size()-1); //new element starts at the last index, moves upward if required
}

Ticket BinaryHeap::heappop(){
    if (elements.empty()){
        throw std::out_of_range("Error: Cannot pop an empty heap.");
    }

    Ticket removed_ticket=elements[0];
    elements[0]=elements.back();
    elements.pop_back();

    if (!elements.empty()){
        heapifyDown(0); //moves the replacement root down until the heap is valid again
    }
    return removed_ticket;
}

Ticket BinaryHeap::peek()const{
    if (elements.empty()){
        throw std::out_of_range("Error: Cannot peek an empty heap.");
    }
    return elements[0];
}

size_t BinaryHeap::findIndexById(int ticketId)const{
    for (size_t i=0; i<elements.size(); ++i){
        if (elements[i].id == ticketId){
            return i;
        }
    }
    return elements.size(); //size is returned as the invalid index, since it is outside the vector
}

bool BinaryHeap::removeById(int ticketId){
    size_t givenIndex=findIndexById(ticketId);
    if (givenIndex == elements.size()){
        return false;
    }

    if (givenIndex == elements.size()-1){
        elements.pop_back();
        return true;
    }

    elements[givenIndex]=elements.back();
    elements.pop_back();

    if (givenIndex>0 && higherPriority(elements[givenIndex],elements[(givenIndex-1)/2])){
        heapifyUp(givenIndex);
    }
    else{
        heapifyDown(givenIndex);
    }
    return true;
}

bool BinaryHeap::updatePriority(int ticketId, int newPriority){
    size_t givenIndex=findIndexById(ticketId);
    if (givenIndex == elements.size()){
        return false;
    }

    elements[givenIndex].priority=newPriority;

    //a changed priority may need to go either up or down; comparing it with the parent decides the direction
    if (givenIndex>0 && higherPriority(elements[givenIndex],elements[(givenIndex-1)/2])){
        heapifyUp(givenIndex);
    }
    else{
        heapifyDown(givenIndex);
    }
    return true;
}

bool BinaryHeap::updateDescription(int ticketId, const std::string& new_description){
    size_t givenIndex=findIndexById(ticketId);
    if (givenIndex == elements.size()){
        return false;
    }

    elements[givenIndex].description=new_description; //description changes dont affect heap order
    return true;
}

bool BinaryHeap::findTicket(int ticketId, Ticket& result)const{
    size_t givenIndex=findIndexById(ticketId);
    if (givenIndex == elements.size()){
        return false;
    }
    result=elements[givenIndex];
    return true;
}

std::vector<Ticket> BinaryHeap::getTickets()const{
    BinaryHeap copied_heap=*this; //pop from a copy so the original heap remains as it is
    std::vector<Ticket>ordered_tickets;
    ordered_tickets.reserve(elements.size());

    while (!copied_heap.isEmpty()){
        ordered_tickets.push_back(copied_heap.heappop());
    }
    return ordered_tickets;
}
