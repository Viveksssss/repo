#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
// #include "testsignal.h"
#include <QQmlContext>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    // qmlRegisterType<testSignal>("testSignal",1,0,"Test"); // 注册需要在引擎加载之前
    engine.load(url);
    // QObject*obj = engine.rootObjects().first();
    // // qDebug() << obj;
    // QQmlProperty(obj,"title").write("good"); // 修改窗口的名称
    // // QQmlProperty(obj,"height").write(200);   // 修改组件属性
    // QObject*rect = obj->findChild<QObject*>("rec"); // 寻找子组件
    // // QQmlProperty(rect,"color").write("yellow");
    // QVariant ret;
    // // QMetaObject::invokeMethod(obj,"sig");  // 调用信号
    // testSignal *t = new testSignal;
    // QObject::connect(obj,SIGNAL(sig()),t,SLOT(prints()));
    // QMetaObject::invokeMethod(obj,"func",Q_RETURN_ARG(QVariant,ret),Q_ARG(QVariant,"asdsad")); // 调用方法
    // QMetaObject::invokeMethod(obj,"sig");  // 调用信号
    // engine.rootContext()->setContextProperty("globalProperty","asdasdas");







    return app.exec();
}
