# Project's name
project (wumpus)

set (SOURCES
	wumpus.cpp
	square.cc
	world.cc
	gamer.cc
	agent.cc
)



add_executable(wumpus ${SOURCES})


target_link_libraries(wumpus ncurses)
