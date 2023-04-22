# Regex-to-dfa-convertor

This is an application that for a given regular expression r constructs a deterministic finite automaton M = (Q, Σ, δ, q0, F), such that the language described by r is precisely the language recognized by M.

Define a function that takes a valid regular expression r as a parameter and returns an object of type deterministic finite automaton. The returned automaton must recognize the language represented by r. Auxiliary classes and functions will also be defined and constructed as needed to solve the problem.

In the main function, a regular expression is read from a file. It is checked for validity and, only if it is valid, the corresponding DFA is obtained, and there is the possibility of checking a word in the automaton.

This application was developed for the LFC lab (Limbaje Formale si Compilatoare) as second homework.
