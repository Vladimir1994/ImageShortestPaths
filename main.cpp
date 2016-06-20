#include "imageprovider.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ImageProvider *imProv = new ImageProvider;
    engine.rootContext()->setContextProperty("ImageProvider", imProv);
    engine.addImageProvider("ImageProvider", imProv);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

