#ifndef QFVARIANTWRAPPER_H
#define QFVARIANTWRAPPER_H

#include <QVariant>
#include <QFuture>
#include <QJSValue>
#include <QFutureWatcher>
#include <QPointer>
#include <QJSEngine>

class QFVariantWrapperBase {
public:
    virtual inline ~QFVariantWrapperBase() {
    }

    virtual bool isFinished(const QVariant& v) = 0;
    virtual void onFinished(QPointer<QJSEngine> engine, const QVariant& v, const QJSValue& func) = 0;

};

template <typename T>
class QFVariantWrapper : public QFVariantWrapperBase {
public:

    virtual bool isFinished(const QVariant& v) {
        QFuture<T> future = v.value<QFuture<T> >();
        return future.isFinished();
    }

    virtual void onFinished(QPointer<QJSEngine> engine, const QVariant& v, const QJSValue& func) {
        if (!func.isCallable()) {
            qWarning() << "Future.onFinished: Callback is not callable";
            return;
        }

        QFuture<T> future = v.value<QFuture<T> >();
        QFutureWatcher<T> *watcher = 0;

        auto listener = [=]() {

            if (!engine.isNull()) {
                QJSValue value = engine->toScriptValue<T>(future.result());
                QJSValue callback = func;
                QJSValue ret = callback.call(QJSValueList() << value);

                if (ret.isError()) {
                    QString message = QString("%1:%2: %3: %4")
                                      .arg(ret.property("fileName").toString())
                                      .arg(ret.property("lineNumber").toString())
                                      .arg(ret.property("name").toString())
                                      .arg(ret.property("message").toString());
                    qWarning() << message;
                }
            }
            if (watcher != 0) {
                delete watcher;
            }
        };

        if (future.isFinished()) {
            //@FIXME - call listener by queued connection
            listener();
        } else {
            watcher = new QFutureWatcher<T>();
            watcher->setFuture(future);
            QObject::connect(watcher, &QFutureWatcherBase::finished, listener);
        }
    }

};

#endif // QFVARIANTWRAPPER_H
