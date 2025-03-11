# Projecto 2 - IAED 2022/2023

## Enunciado

O enunciado do projecto está disponível em [enunciado.md](enunciado.md). 

## Data de entrega: 14 de abril de 2023, às 19h59

Informações detalhadas sobre o processo de submissão estão disponíveis em [informacoes.md](informacoes.md).



# Evaluation

2023-04-13T00:50:44

## Test 1: [- Command terminated by signal (11: SIGSEGV)-].

## Test 2: [- Wrong Answer-].


## Test 3: [+ Accepted+].
## Test 4: [+ Accepted+].
## Test 5: [+ Accepted+].
## Test 6: [+ Accepted+].
## Test 7: [- Wrong Answer-].


## Test 8: [- Wrong Answer-].


## Test 9: [+ Accepted+].
## Test 10: [+ Accepted+].
## Test 11: [+ Accepted+].
## Test 12: [+ Accepted+].
## Test 13: [+ Accepted+].
## Test 14: [+ Accepted+].
## Test 15: [+ Accepted+].
## Test 16: [+ Accepted+].
## Test 17: [+ Accepted+].
## Test 18: [- Wrong Answer-].


## Test 19: [- Wrong Answer-].


## Test 20: [- Wrong Answer-].


## Test 21: [- Wrong Answer-].


## Test 22: [+ Accepted+].
## Test 23: [- Wrong Answer-].


## Test 24: [- Wrong Answer-].


## Test 25: [- Wrong Answer-].


## Test 26: [- Wrong Answer-].


## Test 27: [- Command terminated by signal (11: SIGSEGV)-].

## Test 28: [- Time Limit Exceeded-].

## Test 29: [- Time Limit Exceeded-].

## Test 30: [- Time Limit Exceeded-].

## Test 31: [- Time Limit Exceeded-].

## Test 32: [- Command terminated by signal (6: SIGABRT)-].



## Number of passed tests: 14/32


## Valgrind Output:


```
==16173== Memcheck, a memory error detector
==16173== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==16173== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==16173== Command: ./proj.out
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D08: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x109588: origemOuDestino (project2.c:367)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D33: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x109588: origemOuDestino (project2.c:367)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D08: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x109597: origemOuDestino (project2.c:367)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D33: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x109597: origemOuDestino (project2.c:367)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D08: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x1095AD: origemOuDestino (project2.c:367)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D33: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x1095AD: origemOuDestino (project2.c:367)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D08: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x1095F7: origemOuDestino (project2.c:371)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D33: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x1095F7: origemOuDestino (project2.c:371)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x109609: origemOuDestino (project2.c:380)
==16173==    by 0x10975E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x10978E: errLigacoes (project2.c:357)
==16173==    by 0x10BDB5: adicionaLiagacoes (project2.c:252)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x10A37F: updateCarreira (project2.c:623)
==16173==    by 0x10BE10: adicionaLiagacoes (project2.c:253)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x10A385: updateCarreira (project2.c:623)
==16173==    by 0x10BE10: adicionaLiagacoes (project2.c:253)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x10A9F4: guardarLigacoes (project2.c:677)
==16173==    by 0x10BE45: adicionaLiagacoes (project2.c:254)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x10A9FD: guardarLigacoes (project2.c:677)
==16173==    by 0x10BE45: adicionaLiagacoes (project2.c:254)
==16173==    by 0x10923C: main (project2.c:184)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D08: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x10ADCB: removerCustoDestino (project2.c:743)
==16173==    by 0x10B26E: removeParagem (project2.c:294)
==16173==    by 0x1092CC: main (project2.c:190)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x4839D33: strcmp (vg_replace_strmem.c:848)
==16173==    by 0x10ADCB: removerCustoDestino (project2.c:743)
==16173==    by 0x10B26E: removeParagem (project2.c:294)
==16173==    by 0x1092CC: main (project2.c:190)
==16173== 
==16173== Conditional jump or move depends on uninitialised value(s)
==16173==    at 0x10ADCE: removerCustoDestino (project2.c:743)
==16173==    by 0x10B26E: removeParagem (project2.c:294)
==16173==    by 0x1092CC: main (project2.c:190)
==16173== 
==16173== 
==16173== HEAP SUMMARY:
==16173==     in use at exit: 0 bytes in 0 blocks
==16173==   total heap usage: 8 allocs, 8 frees, 21,152 bytes allocated
==16173== 
==16173== All heap blocks were freed -- no leaks are possible
==16173== 
==16173== For counts of detected and suppressed errors, rerun with: -v
==16173== Use --track-origins=yes to see where uninitialised values come from
==16173== ERROR SUMMARY: 59 errors from 17 contexts (suppressed: 0 from 0)

```


Your code will not be reevaluated if you submit before 2023-04-13 01:00:44 @ Lisbon, Portugal. You need to wait 10 minute(s).

