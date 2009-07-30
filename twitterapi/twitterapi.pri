VER_MAJ = 0
VER_MIN = 8
VER_PAT = 2
VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

win32: TWITTERAPI_LIB = -ltwitterapi$${VER_MAJ}
else:  TWITTERAPI_LIB = -ltwitterapi

INCLUDEPATH += $$TOP/twitterapi
DEPENDPATH  += $$TOP/twitterapi
