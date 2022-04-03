# Alternative-CPP-STL-String-Library

This is an alternative C++ STL String Library With Buffer Manager. All methods below can handle C-String as well. Interface includes the following primary implemented functionality:




`Assignment Operator` 
Automatic type conversion between C-strings under assignment.
 
`[] Operator`
Retrieve positional char in String

`+ and += Operators`
Extends String object 

`Insert Method`
Given anIndex of insertion, aSubString to be inserted, and aMaxCopyLen that defines the maximum number of characters from aString to be inserted into String object or C-strings, string object will increase in length by aSubString's length. Automatic memory management for overflows.

`Replace Method`
Given anIndex of replacement, aMaxCopyLen that defines the maximum number of characters from aString to be replaced in to String object or C-strings, aSubstring to be replaced, string object will preserve its length. Automatic memory management to handle overflows.

`Erase Method`
Given anIndex, and a size aCount, aCount number of characters will be erased from the String object starting from anIndex

`Compare Method`
Given aString, the String object will be compared based on all char values and return -1 for <, 0 if ==, and 1 if >.

`Find Method`
Given aSubString and anOffset, the starting index at which aSubstring exists will be returned if found. Otherwise returns -1.

