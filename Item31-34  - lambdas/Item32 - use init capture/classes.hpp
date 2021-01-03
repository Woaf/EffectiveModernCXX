#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <memory>


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


class IsValidAndArchived {
public: 
    using DataType = std::unique_ptr<Widget>;

    explicit IsValidAndArchived (DataType&& ptr);
    
    bool operator () () const;
private: 
    DataType pw;
};


#endif // CLASSES_H
