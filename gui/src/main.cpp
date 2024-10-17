#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("sudoku-solver", "Main");

  // Access the root object (ApplicationWindow)
  QObject* rootObject = engine.rootObjects().first();

  // Find the GridLayout object (board)
  QObject* gridObject = rootObject->findChild<QObject*>("board");

  if (gridObject) {
    // Find the Repeater inside the GridLayout by ID (boardRepeater)
    QObject* repeaterObject = gridObject->findChild<QObject*>("boardRepeater");
  }

  return app.exec();
}

void set_board(QObject* repeater) {
  if (repeater) {
    // Access the number of items (total cells in the board)
    int itemCount = repeater->property("count").toInt();
    qDebug() << "Total items in Repeater:" << itemCount;

    // Access individual TextField items using itemAt(index)
    for (int i = 0; i < itemCount; ++i) {
      QQuickItem* field;
      QMetaObject::invokeMethod(repeater, "itemAt", Qt::DirectConnection,
                                Q_RETURN_ARG(QQuickItem*, field),
                                Q_ARG(int, i));

      // QObject *textFieldObject = returnedValue.value<QObject*>();

      if (field) {
        // Access the text property of the TextField
        QString textFieldText = field->property("text").toString();
        qDebug() << "Text in TextField" << i << ":" << textFieldText;

        // Set a new text value for the TextField
        field->setProperty("text", QString::number(i));
      }
    }
  }
}
