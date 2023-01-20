#!/bin/bash

make fclean
make
echo /\\/\\/\\/\\ ﾟ✧Test Input✧ﾟ･/\\/\\/\\/\\
echo ./philo -1 600 200 200
./philo -1 600 200 200
echo ./philo 4 -600 200 200
./philo 4 -600 200 200
echo ./philo 4 600 -200 200
./philo 4 600 -200 200
echo ./philo 4 600 200 -200
./philo 4 600 200 -200
echo ./philo 4 600 200 200 -5
./philo 4 600 200 200 -5
echo \\/\\/\\/\\/ ﾟ#✧Inputtests done✧ﾟ･\\/\\/\\/\\/
echo /\\/\\/\\/\\ ﾟ✧Test with 1 800 200 200✧ﾟ･/\\/\\/\\/\\
echo ./philo 1 800 200 200
./philo 1 800 200 200
sleep 3
kill "$!"
echo should die
echo ./philo 1 800 200 200
./philo 1 800 200 200 3
sleep 3
kill "$!"
echo should die
echo /\\/\\/\\/\\ ﾟ✧Test with 5 800 200 200 - stop after 30 sec✧ﾟ･/\\/\\/\\/\\
echo ./philo 5 800 200 200
./philo 5 800 200 200
sleep 20
kill "$!"
echo should NOT die
echo /\\/\\/\\/\\ ﾟ✧Test with 5 800 200 200 - stop after 30 sec✧ﾟ･/\\/\\/\\/\\
echo ./philo 5 800 200 200
./philo 5 800 200 200
kill "$!"
sleep 20
echo should NOT die
echo /\\/\\/\\/\\ ﾟ✧Test with 5 800 200 200 - stop after 30 sec✧ﾟ･/\\/\\/\\/\\
echo ./philo 5 800 200 200
./philo 5 800 200 200
sleep 20
kill "$!"
echo should NOT die
echo /\\/\\/\\/\\ ﾟ✧Test with 5 800 200 200 - stop after 30 sec✧ﾟ･/\\/\\/\\/\\
echo ./philo 5 800 200 200
./philo 5 800 200 200
sleep 20
echo should NOT die
kill "$!"
echo /\\/\\/\\/\\ ﾟ✧Test with 5 800 200 200 7✧ﾟ･/\\/\\/\\/\\
./philo 5 800 200 200 7 > ../test_eval.log
echo "each line should be at least 7"
echo "philo one:"
< ../test_eval.log grep "0 is eating" | wc -l
echo "philo two:"
< ../test_eval.log grep "1 is eating" | wc -l
echo "philo three:"
< ../test_eval.log grep "2 is eating" | wc -l
echo "philo four:"
< ../test_eval.log grep "3 is eating" | wc -l
echo "philo five:"
< ../test_eval.log grep "4 is eating" | wc -l
sleep 2
echo /\\/\\/\\/\\ ﾟ✧Test with 4 410 200 200 - stop after 30 sec✧ﾟ･/\\/\\/\\/\\
echo ./philo 4 410 200 200
./philo 4 410 200 200 &
sleep 15
echo should NOT die
kill "$!"
echo /\\/\\/\\/\\ ﾟ✧Test with 3 310 200 100 - death should occur✧ﾟ･/\\/\\/\\/\\
echo ./philo 3 310 200 100
./philo 3 310 200 100
sleep 5
echo should die
echo /\\/\\/\\/\\ ﾟ✧Tests with 2 philosophers - time of death should never exceed 10ms ✧ﾟ･/\\/\\/\\/\\
echo ./philo 2 010 200 190
./philo 2 400 200 190 &
sleep 10
echo should NOT die
kill "$!"
echo ./philo 2 243 140 100
./philo 2 243 140 100
sleep 4