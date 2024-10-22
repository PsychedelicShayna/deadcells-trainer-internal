TEMPLATE = lib

CONFIG += c++17
CONFIG -= qt

DEFINES += DEADCELLSINTERNALHACK_LIBRARY

SOURCES += \
    "source/dllmain.cpp" \
    "source/player_structure.cpp" \
    "source/apflask.cpp" \
    "source/d3d11_graphics.cpp" \
    "source/imgui_hacks_overlay.cpp" \
    source/dc_asm_patches.cpp \
    source/vmnoclip.cpp


HEADERS += \
    "source/player_structure.hpp" \
    "source/value_modifier_hacks.hpp" \
    "source/apflask.hpp" \
    "source/d3d11_graphics.hpp" \
    "source/imgui_hacks_overlay.hpp" \
    source/dc_asm_patches.hpp \
    source/vmnoclip.hpp


LIBS += -luser32

TARGET = dcinternalhack

# GHT --------------------------------------------------
INCLUDEPATH += $$PWD/../game-hacking-toolkit/source/libght
DEPENDPATH += $$PWD/../game-hacking-toolkit/source/libght
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../game-hacking-toolkit/builds/libght/MSVC19_x86/release/ -llibght
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../game-hacking-toolkit/builds/libght/MSVC19_x86/debug/ -llibght

# D3D11 --------------------------------------------------
LIBS += "-LC:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/um/x86" "-ld3d11"
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/um/"
DEPENDPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/um/"

# MinHook --------------------------------------------------
LIBS += -L$$PWD/dependencies/minhook/lib/ -llibMinHook-x86-v141-mt
INCLUDEPATH += $$PWD/dependencies/minhook/include
DEPENDPATH  += $$PWD/dependencies/minhook/include

# DirectXTK --------------------------------------------------
LIBS += -L$$PWD/dependencies/DirectXTK/Bin/Desktop_2022_Win10/Win32/Release -lDirectXTK
INCLUDEPATH += $$PWD/dependencies/DirectXTK/Inc
DEPENDPATH  += $$PWD/dependencies/DirectXTK/Inc

# ImgGui --------------------------------------------------
SOURCES += \
    "dependencies/imgui/imgui.cpp" \
    "dependencies/imgui/imgui_demo.cpp" \
    "dependencies/imgui/imgui_draw.cpp" \
    "dependencies/imgui/imgui_tables.cpp" \
    "dependencies/imgui/imgui_widgets.cpp" \
    "dependencies/imgui/backends/imgui_impl_win32.cpp" \
    "dependencies/imgui/backends/imgui_impl_dx11.cpp" \

HEADERS += \
    "dependencies/imgui/imgui.h" \
    "dependencies/imgui/imconfig.h" \
    "dependencies/imgui/imgui_internal.h" \
    "dependencies/imgui/imstb_rectpack.h" \
    "dependencies/imgui/imstb_textedit.h" \
    "dependencies/imgui/imstb_truetype.h" \
    "dependencies/imgui/backends/imgui_impl_win32.h" \
    "dependencies/imgui/backends/imgui_impl_dx11.h"

INCLUDEPATH += $$PWD/dependencies/imgui
DEPENDPATH += $$PWD/dependencies/imgui
