#!/bin/bash

#incorrect
./exe $1 -fixed_context_dep texts/incorrect/incorrect_en_small.txt \
texts/incorrect/ya_res/fixed_context_dep/ya_res_incorrect_en_small.txt \
texts/incorrect/averaged_results/aver_res_for_all_incorrect.txt

for i in {1..10}
do
    ./exe $1 -fixed_context_dep texts/incorrect/tiny$i.txt \
    texts/incorrect/ya_res/fixed_context_dep/ya_res_tiny$i.txt \
    texts/incorrect/averaged_results/aver_res_for_all_incorrect.txt
done


#correct

./exe $1 -fixed_context_dep texts/correct/small_text_correct.txt \
texts/correct/ya_res/fixed_context_dep/ya_res_small_text_correct.txt \
texts/correct/averaged_results/aver_res_for_all_correct.txt

./exe $1 -fixed_context_dep texts/correct/test_text_HPOP.txt \
texts/correct/ya_res/fixed_context_dep/ya_res_test_text_HPOP.txt \
texts/correct/averaged_results/aver_res_for_all_correct.txt

./exe $1 -fixed_context_dep texts/correct/mid1.txt \
texts/correct/ya_res/fixed_context_dep/ya_res_mid1.txt \
texts/correct/averaged_results/aver_res_for_all_correct.txt

./exe $1 -fixed_context_dep texts/correct/mid2.txt \
texts/correct/ya_res/fixed_context_dep/ya_res_mid2.txt \
texts/correct/averaged_results/aver_res_for_all_correct.txt

./exe $1 -fixed_context_dep texts/correct/large1.txt \
texts/correct/ya_res/fixed_context_dep/ya_res_large1.txt \
texts/correct/averaged_results/aver_res_for_all_correct.txt

for i in {1..12}
do
    ./exe $1 -fixed_context_dep texts/correct/tiny$i.txt \
    texts/correct/ya_res/fixed_context_dep/ya_res_tiny$i.txt \
    texts/correct/averaged_results/aver_res_for_all_correct.txt
done


g++ -std=c++11 averaging/calc_aver/main.cpp -o aver
./aver

# очищаем файл, чтобы при следующем запуске работать с ним как с новым, т.к. в него идет дозапись
truncate -s 0 texts/correct/averaged_results/aver_res_for_all_correct.txt
truncate -s 0 texts/incorrect/averaged_results/aver_res_for_all_incorrect.txt
