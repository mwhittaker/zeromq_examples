CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

# The library dependencies of the key value store clients and servers.
SET(KV_LIBRARY_DEPENDENCIES
    pthread
    zmq
)

# The source dependencies of the key value store clients and servers.
SET(KV_SRC_DEPENDENCIES
    zmq_util.cc
)

# REQ-REP
ADD_EXECUTABLE(req_rep_client req_rep_client.cc ${KV_SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(req_rep_client ${KV_LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(req_rep_server req_rep_server.cc ${KV_SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(req_rep_server ${KV_LIBRARY_DEPENDENCIES})

# PUB-SUB
ADD_EXECUTABLE(pub_sub_client pub_sub_client.cc ${KV_SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(pub_sub_client ${KV_LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(pub_sub_server pub_sub_server.cc ${KV_SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(pub_sub_server ${KV_LIBRARY_DEPENDENCIES})

# PUSH-PULL
ADD_EXECUTABLE(push_pull_source push_pull_source.cc ${KV_SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(push_pull_source ${KV_LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(push_pull_worker push_pull_worker.cc ${KV_SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(push_pull_worker ${KV_LIBRARY_DEPENDENCIES})
ADD_EXECUTABLE(push_pull_sink push_pull_sink.cc ${KV_SRC_DEPENDENCIES})
TARGET_LINK_LIBRARIES(push_pull_sink ${KV_LIBRARY_DEPENDENCIES})
