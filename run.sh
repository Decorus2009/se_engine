#!/bin/bash

#incorrect
#./exe -d -fixed_context_dep texts/incorrect/incorrect_en_small.txt
#for i in {1..10}
#do
#    ./exe -d -fixed_context_dep texts/incorrect/tiny$i.txt
#done


#correct
for i in {1..12}
do
    ./exe -d -fixed_context_dep texts/correct/tiny$i.txt
done

./exe -d -fixed_context_dep texts/correct/small_text_correct.txt
./exe -d -fixed_context_dep texts/correct/test_text_HPOP.txt
./exe -d -fixed_context_dep texts/correct/mid1.txt
./exe -d -fixed_context_dep texts/correct/mid2.txt
./exe -d -fixed_context_dep texts/correct/large1.txt
