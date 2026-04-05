# **Trident** - Technical documentation

## __Summary :__
### - How it works
### - Add an operator

---
---

# Add an operator :
- Add the Macro
- Add the function
- Add the operation execution
- Let the parser know about it
### • __**Add the Macro**__
In ``src/trident.hpp``,  
Add your operator's macro in ``enum OperatorType``.  
The format is: **OP``t``_``NAME``:**  
**t is a lowercase letter that describe the kind of function:**
- 'n' for numbers, like ``OPn_ADD`` for a+b.
- 'b' for booleans, like ``OPb_NOT`` for !a
- 'c' for comparators, like ``OPc_UNEQUAL`` for a!=b 
- NAME should be uppercase in most case,  
But you can add lowercase for specification, like what we hava with ``OPc_strictINF`` and ``OPc_equalINF``  

### __** • Add the function**__
Put the declaration in ``src/values.hpp``  
At the end, with other functions-operators, like ``round_equal(Value, Value)`` or ``value_cos(Value)``  
Add its implementation at the end of ``src/definitions/values.cpp``
It should input Values, and output a Value.

### __** • Add the operation execution**__
In the file ``src/definitions/arguments.cpp``, go to the function ``ArgumentExecuter::do_operation()``
You can see a huge switch case, with each operation.
There are 3 presets defined:
- ``OPERATOR(<OPt_NAME>, <operator_symbol>)`` (for Value::operator overloadings)
- ``FUNCTION(<OPt_NAME>, <function_Name>)`` (for functions with two inputs)
- ``FUNCMONO(<OPt_NAME>, <function_Name>)`` (for functions with only one inputs)  
  
But if you need a more complexe implementation, you just need to know about those functions :
- ``pop_last_arg()`` : pop a value from the calculation stack, and returns it.
- ``add_val(Value input)`` : add the value inputed in the calculation stack.  

For simple argument number beyond two, you can simply do:
```
case OPt_MYPECULIAROPERATOR:
        add_val(
                pop_last_arg(),
                pop_last_arg(),
                pop_last_arg(),
        );
        break;
```
Or (if you want to do weirder things, idk)
```
case OPt_MYPECULIAROPERATOR:
        Value third_argument = pop_last_arg();
        Value second_argument = pop_last_arg();
        Value first_argument = pop_last_arg();

        Value return_value = ... ;
        //your code

        add_val(return_value);
        break;
```
### __**• Let the parser know about it**__
In the file ``src/definitions/parser.cpp``,  
Go to the ``string_to_value()`` function.
Add a string test: ``TEST_STR("<your string>", <op macro>)`` which will transform your keyword written into the operator.  
For exemple:
```
TEST_STR("cos", OPn_COS  );
```  
  
## And now, you have a working opertor for .trd !
I mean, you do have to compile the project.
Test it easely in a ``code.trd`` file:
```
say "result of my operator:" <arg1> <args...> myoperator
say "should be 1:" 0 cos
say "should be 0:" pi 2 / cos   #=cos(pi/2)
```
result:
```
result of my operator : <the result>
should be 1 : 1
should be 0 : 0
```  
---
end of the **Add an operator** section  

---  

