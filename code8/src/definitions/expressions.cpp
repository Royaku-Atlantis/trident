#include "../trident.hpp"
#include "../expressions.hpp"

/* CLASS ARG/EXPRESSION ELEMENT LIST */
ExpressionElement::ExpressionElement(const Value & val)
{
        value = val;
        ptr_next = nullptr;
}
ExpressionElement::~ExpressionElement()
{
        if (ptr_next!=nullptr)
        {
                delete ptr_next;
        }
}

ExpressionElement * ExpressionElement::append_expressionelement(const Value & new_value)
{
        //create the new expression element
        ExpressionElement * new_expression_element_ptr = new ExpressionElement(new_value);

        //add it to the current expression element
        if (ptr_next != nullptr)
        {
                say("ho no! this element is not the tail:", value.string());
                delete ptr_next;
        }
        ptr_next = new_expression_element_ptr;

        //return the pointer of the new tail element we just created
        return new_expression_element_ptr;
}

