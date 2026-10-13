# **Trident** - Add an Type
[Go back to Menu](../Trident.md)
--
### To test this, i'll create the point index, i think

Let's say you want to add a type called "TypeName"
It will be a representation of a type in c++ called "C_typename"

## trident.hpp
add value in trident.hpp (before VALUE_VALTYPECOUNT)  
``enum ValueType : unsigned int {`` 
``VALUE_NEWTYPENAME``  
  
## values.hpp
in values.hpp, in ``struct Value{}``

- add the value data in the **union** : ``C_typename val_typename``
or ``C_typename * val_typename`` if it's a higher level data type 

- constructors by Value Type
``Value (C_typename value_typename);``
Tough you can make the constructor more specific, like with *Value (int value_variable, bool is_reference);*

## definitions/values.cpp
- constructors by Value Type
Add and define Value Value::(C_typename value_typename);

- constructors by Copy
add your type in
Value::Value (Value const& val); //constructor by copy

- edit affectation in values.cpp  
``Value& Value::operator = (const Value & new_value)``  

- destructor
If val_typename is higher level, then add its destructor 
 
- Make the Value displayable
in the IF() statement of ``String Value::string()``

and display in debug options :
``String get_value_color(ValueType vtype)``

### get_asnumber(), get_bool() and operators
By default, all operator with VALUE_NEWTYPENAME will return Undefined Value by default.

## test in main.cpp

## make it summonable in trident