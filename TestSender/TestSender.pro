QT += core network  # 必须添加 network 模块，否则无法使用 QTcpSocket
QT -= gui           # 控制台项目，无需GUI模块

CONFIG += c++11 console
CONFIG -= app_bundle

# 源文件配置
SOURCES += main.cpp

# 版本兼容（匹配Qt 5.12）
DEFINES += QT_DEPRECATED_WARNINGS
