QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    album.cpp \
    albumController.cpp \
    autor.cpp \
    autorController.cpp \
    banda.cpp \
    bandaController.cpp \
    colaborador.cpp \
    colaboradorController.cpp \
    conexao.cpp \
    form_album.cpp \
    form_autenticacao.cpp \
    form_autor.cpp \
    form_banda.cpp \
    form_colaborador.cpp \
    form_grupo.cpp \
    form_livro.cpp \
    form_musica.cpp \
    form_serie.cpp \
    global.cpp \
    grupo.cpp \
    grupoController.cpp \
    livro.cpp \
    livroAutor.cpp \
    livroAutorController.cpp \
    livroController.cpp \
    main.cpp \
    form_principal.cpp \
    musica.cpp \
    musicaController.cpp \
    serie.cpp \
    serieController.cpp \
    status.cpp \
    statusController.cpp

HEADERS += \
    album.h \
    albumController.h \
    autor.h \
    autorController.h \
    banda.h \
    bandaController.h \
    colaborador.h \
    colaboradorController.h \
    conexao.h \
    form_album.h \
    form_autenticacao.h \
    form_autor.h \
    form_banda.h \
    form_colaborador.h \
    form_grupo.h \
    form_livro.h \
    form_musica.h \
    form_principal.h \
    form_serie.h \
    global.h \
    grupo.h \
    grupoController.h \
    livro.h \
    livroAutor.h \
    livroAutorController.h \
    livroController.h \
    musica.h \
    musicaController.h \
    serie.h \
    serieController.h \
    status.h \
    statusController.h

FORMS += \
    form_album.ui \
    form_autenticacao.ui \
    form_autor.ui \
    form_banda.ui \
    form_colaborador.ui \
    form_grupo.ui \
    form_livro.ui \
    form_musica.ui \
    form_principal.ui \
    form_serie.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    arquivos.qrc
