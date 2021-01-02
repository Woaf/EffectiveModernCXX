#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>


class Widget {
public: 
    Widget ();

    bool isValidated () const;
    bool isProcessed () const;
    bool isArchived () const;

    size_t GetId () const noexcept;

private:
    static size_t id_counter;
    size_t id;
};


std::ostream& operator<< (std::ostream& out, const Widget& w);


#endif // CLASSES_H
