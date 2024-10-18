// sudoku.hpp
#ifndef SUDOKU_H
#define SUDOKU_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "board.hpp"

class Sudoku : public QObject {
  Q_OBJECT

 private:
  Board board;
  QQmlApplicationEngine& engine;
  void updateGuiBoard();

 public:
  Sudoku(QQmlApplicationEngine& engine) : engine(engine) {};
  Q_INVOKABLE void load(const QUrl& filePath);
  Q_INVOKABLE void solve();
};

#endif  // SUDOKU_H
