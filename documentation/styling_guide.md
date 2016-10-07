#[RECOMMENDED READ](https://google.github.io/styleguide/cppguide.html)
#Comments
-Use short, descriptive comments  
-Include your name/nickname in your files/functions/modifications to other people's work
#Vars/Constants naming
##Constants
-ALL_CAPITAL_LETTERS   
-Strings used in-game will probably be kept in one file and we'll be refering to that file. E.g. if there's a description of a particular
upgrade it'll look something like (S_ obligatory in case of constant strings):  
S_UPGRADE1_DESCRIPTION = "...";  
S_MAINMENU_BUTTON1_CAPTION = "Join game";  
##Variables
-Initialise when declaring  
-Static variables are **not allowed**  
-Use g_name for global variables
#Style
##Tabs, brackets, if statements
-We use tabs. Use proper indentation (nesting)  
-Use {} in if statements, even if it's just one instruction (easier to read!)  
-New line after opening a curly bracket, new line before closing a curly bracket  
Example: 
```c++
if(x > y){  
  do_this();  
}else{  
  do_this();  
}  
```
-
```c++
if(x > y){ do_something(); } 
```
is **allowed** if it's just one instruction and there's no 'else'
