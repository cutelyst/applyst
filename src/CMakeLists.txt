file(GLOB_RECURSE applyst_SRCS *.cpp *.h)

set(applyst_SRCS
    ${applyst_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(${PROJECT_NAME} SHARED ${applyst_SRCS})

# Link to Cutelyst
target_link_libraries(${PROJECT_NAME}
    AppStreamQt
    Cutelyst::Core
    Cutelyst::StaticSimple
    Cutelyst::View::Grantlee
    Cutelyst::Utils::Pagination
    Cutelyst::Authentication
    Cutelyst::Session
    Grantlee5::Templates
    Qt5::Core
    Qt5::Network
)
