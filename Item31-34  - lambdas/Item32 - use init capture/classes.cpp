#include "classes.hpp"


size_t Widget::id_counter = 0;

Widget::Widget () : 
    id (id_counter++)
{
}

bool Widget::isValidated () const {
    return false;
}

bool Widget::isProcessed () const {
    return false;
}

bool Widget::isArchived () const {
    return false;
}

size_t Widget::GetId () const noexcept {
    return id;
}

std::ostream& operator<< (std::ostream& out, const Widget& w) {
    out << w.GetId ();
    return out;
}
