 'print_component_list.cpp' appears to already have been implemented. (T1.2)
 in readme.html it is stated that '&<C<L<R<|', however an example of ordering primitives it states 'C0.5 < C1 < C2 < R1e-3 < R1 < L0.3 < L10'. I have assumed that L\<R. (T1.3)
 No clear indication of which of (R1|R2|R3|R4) and (R1|R2|R3) is greater. I have assumed that in the case of |, the former is greater, however if we were to replace | with &, the latter would be greater.
 Although it was stated that n1 and n2 formed a potential divider, it didn't state where measurements were to be taken. I assumed that they were in the following configuration: (T3.2)
```
 X---n1---+---Y
          |
          |
          n2
          |
          |
        _____
         ___
          _
```
'make_log_space(0.1,100,3)' is stated as having output [0.1, 10, 100] in readme.html. As these are not evenly spaced logarithmically (log10s are -[-1, 1, 2]) I have disregarded this example and assumed that 'make_log_space(0.1,100,3)' resolves to [0.1, 3.16228, 100] (T3.3)
'print_transfer_function.cpp' appaears to have already been implemented (T3.4)
