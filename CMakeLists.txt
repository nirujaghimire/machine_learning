cmake_minimum_required(VERSION 3.24)
project(machine_learning C)

set(CMAKE_C_STANDARD 23)

add_executable(machine_learning
#        gradient_descent.c
#        linear_regression_stochastic.c
#        linear_regression_batch.c
        linear_regression_batch_momentum.c
#        curve_fitting_with_GD.c
        )
