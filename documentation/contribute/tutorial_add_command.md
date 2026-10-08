# **Trident** - Add a Command
[Go back to Menu](../Trident.md)
---

## commande enum
trident.hpp : enum CommandType : char {}
add your own ``CMD_CUSTOM``
- name should be "CMD_" + the name of your command in Uppercase _(screaming snake case)_
- put it **before** ``CMD_NUMBEROFCOMMANDS`` as it is the 

##  parser command  
``CommandType cmdtext_get_cmdtype(String cmd_firsttoken)``  
add  
``GETCMD("custom", CMD_CUSTOM);``
string of how to recognise the command in the .atl files
then the enum index of the command you're trying to create 

## command execution 

## command execution
StepData Command::run(Index PC, Index CodeSize) const {}

===
## Optional for debug 
when displaying the command information with ``debug_display_command()``, The command index will be converted to string with _trident.cpp :_``String commandtype_string(CommandType CmdType)``
To make your command visible in debug, add your own :
``case CMD_CUSTOM: return "CUSTOM"``
Otherwise, it will display : ``CMD[42]:Forgotten in commandtype_string()`` (42 being your custom command's enum index)