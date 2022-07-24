project(SimulatorTests LANGUAGES C)

add_executable(LapTimerTests src/TimerTests/sim_timer.laptimer.test.c)
add_executable(ZeroTimerTests src/TimerTests/sim_timer.zerotimer.test.c)
add_executable(ConfigInitTests src/ConfigSystem/config_system.init.deinit.test.c)

target_link_libraries(LapTimerTests PRIVATE SIM_TIMER)
target_link_libraries(ZeroTimerTests PRIVATE SIM_TIMER)

target_link_libraries(ConfigInitTests PRIVATE CONFIG_SYSTEM LOGGER)

add_test(NAME LapTimerTests COMMAND LapTimerTests)
add_test(NAME ZeroTimerTests COMMAND ZeroTimerTests)
add_test(NAME ConfigInitTests COMMAND ConfigInitTests)