set (Platform_SRCS
	main.cpp
	server.cpp
	socket.cpp
	window.cpp
)
set (Platform_HDRS
	server.h
	socket.h
	window.h
)

qt5_wrap_cpp (Platform_SRCS ${Platform_HDRS})
add_executable (platforma ${Platform_SRCS})
target_link_libraries (platforma ${QtWidgets_LIBRARIES} ${Qt5Network_LIBRARIES})

