#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>

#include "helper.hpp"
#include "sudoku.hpp"

int main(int argc, char* argv[]) {
  setLogLevel();

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  engine.loadFromModule("sudoku-solver", "Main");

  Sudoku sudoku{engine};
  engine.rootContext()->setContextProperty("sudoku", &sudoku);

  return app.exec();
}
