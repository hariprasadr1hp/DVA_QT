set(SOURCES
    mainwindow.cpp 
    dva.cpp 
    primary.cpp 
    secondary.cpp 
    excitation.cpp 
    qcustomplot.cpp 
    solcir.cpp 
    holcir.cpp 
    rec.cpp 
    sqr.cpp 
    ise.cpp 
    help.cpp
)

set(HEADERS
    mainwindow.h 
    dva.h 
    primary.h 
    secondary.h 
    excitation.h 
    functions.h 
    qcustomplot.h 
    solcir.h 
    holcir.h 
    rec.h 
    sqr.h 
    ise.h 
    help.h
)

set(FORMS   
    mainwindow.ui 
    dva.ui 
    primary.ui 
    secondary.ui 
    excitation.ui 
    solcir.ui 
    holcir.ui 
    rec.ui 
    sqr.ui 
    ise.ui 
    help.ui
)

add_library(dva
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_link_libraries (dva ${QT5_LIBRARIES})