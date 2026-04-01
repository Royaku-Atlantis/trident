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

        //check if the current expression is actually not the tail
        if (ptr_next != nullptr)
        {
                say("ho no! this element is not the tail:", value.string());
                delete ptr_next;
        }
        //add it to the current expression element
        ptr_next = new_expression_element_ptr;

        //return the pointer of the new tail element we just created
        return new_expression_element_ptr;
}

ExpressionElement * ExpressionElement::get_tail()
{
        //recursive, but could and should be made iteratively
        //its supposed to be used only on Command creation, so it should be fine, but:
        //TODO make get_tail() iteratif instead of recursive

        if (ptr_next == nullptr) return this;

        else return ptr_next->get_tail();
}