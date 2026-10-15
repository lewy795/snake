cmake_minimum_required(VERSION 3.14)

# Włącz język OBJCXX tylko dla macOS
if(APPLE)
    project(Snake CXX OBJCXX)
else()
    project(Snake CXX)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml" "/usr/local/opt/sfml")
endif()

find_package(SFML 3 COMPONENTS Graphics Window System Audio Network REQUIRED)

set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets/icon.icns")
file(GLOB_RECURSE ASSETS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
list(REMOVE_ITEM ASSETS_LIST "${APP_ICON}")

set(COMMON_SOURCES
    engine.cpp
    setup.cpp
    mode/game.cpp
    mode/menu.cpp
    objects/food.cpp
    objects/snake.cpp
    objects/world.cpp
    assets/resources.cpp
    ${ASSETS_LIST}
)

if(APPLE)
    set(SPARKLE_FRAMEWORK "${CMAKE_CURRENT_SOURCE_DIR}/libs/Sparkle.framework")
    
    set_source_files_properties("${APP_ICON}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties("${SPARKLE_FRAMEWORK}" PROPERTIES MACOSX_PACKAGE_LOCATION "Frameworks")

    foreach(ASSET_FILE ${ASSETS_LIST})
        file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${ASSET_FILE}")
        get_filename_component(REL_DIR "${REL_PATH}" DIRECTORY)
        if(REL_DIR)
            set_source_files_properties("${ASSET_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/assets/${REL_DIR}")
        else()
            set_source_files_properties("${ASSET_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/assets")
        endif()
    endforeach()

    add_executable(Snake MACOSX_BUNDLE
        ${COMMON_SOURCES}
        updater.mm
        ${APP_ICON}
        ${SPARKLE_FRAMEWORK}
    )

    set_target_properties(Snake PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE "icon.icns"
        MACOSX_BUNDLE_BUNDLE_NAME "Snake"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.lewy795.snake"
        MACOSX_BUNDLE_INFO_PLIST_KEY_SUFeedURL "https://raw.githubusercontent.com/lewy795/snake/main/appcast.xml"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@executable_path/../Frameworks"
    )

    target_link_libraries(Snake PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Network
        "-framework AppKit"
        "-framework Foundation"
        "${SPARKLE_FRAMEWORK}"
    )
else()
    # Konfiguracja dla Windowsa
    add_executable(Snake ${COMMON_SOURCES})

    target_link_libraries(Snake PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Network
    )
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(APPLE)
    install(TARGETS Snake BUNDLE DESTINATION .)
    set(CPACK_PACKAGE_NAME "Snake By lewy795")
    set(CPACK_PACKAGE_VERSION "beta")
    set(CPACK_PACKAGE_VENDOR "lewy795")
    set(CPACK_GENERATOR "DragNDrop")
    include(CPack)
endif()