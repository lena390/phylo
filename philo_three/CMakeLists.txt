cmake_minimum_required(VERSION 3.17)
project(philo_two C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(philo_two
        libft.c
        main.c
        parse.c
        phylo.h
        simulation_utils.c
        simulation_utils2.c)
