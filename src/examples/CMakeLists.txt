CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

# The library dependencies of the clients and servers.
SET(LIBRARY_DEPENDENCIES
    pthread
    zmq
)

# The source dependencies of the clients and servers.
SET(SRC_DEPENDENCIES
    zmq_util.cc
)

# REQ-REP
ADD_EXECUTABLE(req_rep_client req_rep_client.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(req_rep_client ${LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(req_rep_server req_rep_server.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(req_rep_server ${LIBRARY_DEPENDENCIES})

# PUB-SUB
ADD_EXECUTABLE(pub_sub_client pub_sub_client.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(pub_sub_client ${LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(pub_sub_server pub_sub_server.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(pub_sub_server ${LIBRARY_DEPENDENCIES})

# PUSH-PULL
ADD_EXECUTABLE(push_pull_source push_pull_source.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(push_pull_source ${LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(push_pull_worker push_pull_worker.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(push_pull_worker ${LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(push_pull_sink push_pull_sink.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(push_pull_sink ${LIBRARY_DEPENDENCIES})

# poll
ADD_EXECUTABLE(poll_client
    poll_client.cc
    timer_file_descriptor.cc
    ${SRC_DEPENDENCIES}
)
TARGET_LINK_LIBRARIES(poll_client ${LIBRARY_DEPENDENCIES})

# Extended REQ-REP
ADD_EXECUTABLE(ext_req_rep_client ext_req_rep_client.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(ext_req_rep_client ${LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(ext_req_rep_server ext_req_rep_server.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(ext_req_rep_server ${LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(ext_req_rep_proxy ext_req_rep_proxy.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(ext_req_rep_proxy ${LIBRARY_DEPENDENCIES})

# Multithreaded REQ-REP server
ADD_EXECUTABLE(multithreaded_req_rep_server multithreaded_req_rep_server.cc ${SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(multithreaded_req_rep_server ${LIBRARY_DEPENDENCIES})
