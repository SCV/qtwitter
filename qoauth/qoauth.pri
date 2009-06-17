VER_MAJ = 0
VER_MIN = 1
VER_PAT = 0
VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

win32: QOAUTH_LIB = -lqoauth$${VER_MAJ}
else:  QOAUTH_LIB = -lqoauth

INCLUDEPATH += $${TOP}/qoauth
DEPENDPATH  += $${TOP}/qoauth
