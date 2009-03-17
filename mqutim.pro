# #####################################################################
# Automatically generated by qmake (2.01a) ?? ????. 8 21:49:37 2009
# #####################################################################
qtopia_project(qtopia app)
plugins_bin.files = plugins/libicq.so
plugins_bin.files += plugins/libjabber.so
plugins_bin.path = /lib/plugins/
desktop.files = mqutim.desktop
desktop.path = /apps/Applications
desktop.hint = desktop
INSTALLS += plugins_bin \
    desktop
TEMPLATE = app
TARGET = mqutim
DEPENDPATH += . \
    src \
    include \
    src/antispam \
    src/chatwindow \
    src/contactlist \
    src/ex \
    src/globalsettings \
    src/history \
    src/idle \
    src/notifications \
    src/sound
INCLUDEPATH += . \
    src \
    src/contactlist \
    include \
    src/idle \
    src/ex \
    src/chatwindow \
    src/history \
    src/notifications \
    src/antispam \
    src/sound \
    src/globalsettings

# Input
HEADERS += src/aboutinfo.h \
    src/abstractchatlayer.h \
    src/abstractcontactlist.h \
    src/abstractcontextlayer.h \
    src/abstracthistorylayer.h \
    src/abstractlayer.h \
    src/abstractsoundlayer.h \
    src/abstractstatus.h \
    src/accountmanagement.h \
    src/addaccountwizard.h \
    src/console.h \
    src/contactseparator.h \
    src/iconmanager.h \
    src/mainsettings.h \
    src/pluginsettings.h \
    src/pluginsystem.h \
    src/qutim.h \
    src/qutimsettings.h \
    src/statusdialog.h \
    src/statuspresetcaption.h \
    include/qutim/layerinterface.h \
    include/qutim/plugininterface.h \
    include/qutim/protocolinterface.h \
    src/antispam/abstractantispamlayer.h \
    src/antispam/antispamlayersettings.h \
    src/chatwindow/chatemoticonmenu.h \
    src/chatwindow/chatwindowsettings.h \
    src/chatwindow/conferencecontactlist.h \
    src/chatwindow/conferenceitem.h \
    src/chatwindow/conferenceitemmodel.h \
    src/chatwindow/conferencetabcompletion.h \
    src/chatwindow/movielabel.h \
    src/chatwindow/separatechatwindow.h \
    src/chatwindow/separateconference.h \
    src/contactlist/contactlistitemdelegate.h \
    src/contactlist/contactlistitemdelegate_qtopia.h \
    src/contactlist/contactlistproxymodel.h \
    src/contactlist/contactlistsettings.h \
    src/contactlist/proxymodelitem.h \
    src/contactlist/treecontactlistmodel.h \
    src/contactlist/treeitem.h \
    src/contactlist/contactlistview.h \
    src/globalsettings/abstractglobalsettings.h \
    src/history/historyengine.h \
    src/history/historysettings.h \
    src/history/historywindow.h \
    src/idle/idle.h \
    src/notifications/abstractnotificationlayer.h \
    src/notifications/notificationslayersettings.h \
    src/sound/soundlayersettings.h
FORMS += src/aboutinfo.ui \
    src/accountmanagement.ui \
    src/console.ui \
    src/mainsettings.ui \
    src/pluginsettings.ui \
    src/qutim.ui \
    src/qutimsettings.ui \
    src/statusdialogvisual.ui \
    src/statuspresetcaption.ui \
    src/antispam/antispamlayersettings.ui \
    src/chatwindow/chatwindowform.ui \
    src/chatwindow/chatwindowsettings.ui \
    src/chatwindow/conferenceform.ui \
    src/contactlist/contactlistsettings.ui \
    src/history/historysettings.ui \
    src/history/historywindow.ui \
    src/notifications/notificationslayersettings.ui \
    src/sound/soundlayersettings.ui
SOURCES += main.cpp \
    src/aboutinfo.cpp \
    src/abstractchatlayer.cpp \
    src/abstractcontactlist.cpp \
    src/abstractcontextlayer.cpp \
    src/abstracthistorylayer.cpp \
    src/abstractlayer.cpp \
    src/abstractsoundlayer.cpp \
    src/abstractstatus.cpp \
    src/accountmanagement.cpp \
    src/addaccountwizard.cpp \
    src/console.cpp \
    src/contactseparator.cpp \
    src/iconmanager.cpp \
    src/mainsettings.cpp \
    src/pluginsettings.cpp \
    src/pluginsystem.cpp \
    src/qutim.cpp \
    src/qutimsettings.cpp \
    src/statusdialog.cpp \
    src/statuspresetcaption.cpp \
    src/antispam/abstractantispamlayer.cpp \
    src/antispam/antispamlayersettings.cpp \
    src/chatwindow/chatemoticonmenu.cpp \
    src/chatwindow/chatwindowsettings.cpp \
    src/chatwindow/conferencecontactlist.cpp \
    src/chatwindow/conferenceitem.cpp \
    src/chatwindow/conferenceitemmodel.cpp \
    src/chatwindow/conferencetabcompletion.cpp \
    src/chatwindow/movielabel.cpp \
    src/chatwindow/separatechatwindow.cpp \
    src/chatwindow/separateconference.cpp \
    src/contactlist/contactlistitemdelegate.cpp \
    src/contactlist/contactlistitemdelegate_qtopia.cpp \
    src/contactlist/contactlistproxymodel.cpp \
    src/contactlist/contactlistsettings.cpp \
    src/contactlist/proxymodelitem.cpp \
    src/contactlist/treecontactlistmodel.cpp \
    src/contactlist/treeitem.cpp \
    src/contactlist/contactlistview.cpp \
    src/globalsettings/abstractglobalsettings.cpp \
    src/history/historyengine.cpp \
    src/history/historysettings.cpp \
    src/history/historywindow.cpp \
    src/idle/idle.cpp \
    src/idle/idle_mac.cpp \
    src/idle/idle_win.cpp \
    src/idle/idle_x11.cpp \
    src/notifications/abstractnotificationlayer.cpp \
    src/notifications/notificationslayersettings.cpp \
    src/sound/soundlayersettings.cpp
RESOURCES += qutim.qrc
