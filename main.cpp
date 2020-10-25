#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "game.h"
#include "tank.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    auto player = std::make_shared<Tank>(295, 215);

    Game game{player};


    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    engine.rootContext()->setContextProperty("player", player.get());
    engine.rootContext()->setContextProperty("enemy_list", game.EnemyList());


    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QObject *root_object = engine.rootObjects().value(0);
    QQuickWindow *main_window = qobject_cast<QQuickWindow *>(root_object);

    QObject::connect(main_window, SIGNAL(westDirectionPressed()), &game, SLOT(MoveWestSlot()));
    QObject::connect(main_window, SIGNAL(northDirectionPressed()), &game, SLOT(MoveNorthSlot()));
    QObject::connect(main_window, SIGNAL(eastDirectionPressed()), &game, SLOT(MoveEastSlot()));
    QObject::connect(main_window, SIGNAL(southDirectionPressed()), &game, SLOT(MoveSouthSlot()));

    return app.exec();
}
