The purpose of this lab is to implement a Lexical Analyzer(Scanner) using Flex to automate the tokenization and quantative counting of a program's source code elements. 
Lexical analysis is the initial phase of a compiler, responsible for reading a stream of input characters, grouping them into meaningful sequences called lexemes, and mapping
them to predefined grammatical tokens. Flex acheives this by converting user-defined Regular Expressions into a highly efficient Deterministic Finite Automata(DFA) state machine.
The program is structured into three essential Flex sections: the Definition Section, which initializes the integer memory counters; the Rules Section, which pairs regex patterns 
with corresponding C actions to identify keywords, identifiers, constants, strings, operators, and delimiters; and the User Subroutines Section, which controls program execution 
by utilizing the core yylex() scanner loop to generate a final token count sumary upon reaching the End-Of-File(EOF) marker.

 
