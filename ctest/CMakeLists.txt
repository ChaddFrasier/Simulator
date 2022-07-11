project(SimulatorTests LANGUAGES C)

add_executable(LapTimerTests src/TimerTests/sim_timer.laptimer.test.c)
add_executable(ZeroTimerTests src/TimerTests/sim_timer.zerotimer.test.c)

target_link_libraries(LapTimerTests PRIVATE SIM_TIMER)
target_link_libraries(ZeroTimerTests PRIVATE SIM_TIMER)

add_test(NAME LapTimerTests COMMAND LapTimerTests)
add_test(NAME ZeroTimerTests COMMAND ZeroTimerTests)