#include <QQuickItem>
#include <filesystem>

#include "constants.hpp"
#include "game.hpp"
#include "helper.cpp"
#include "sudoku.hpp"

void Sudoku::load(const QUrl& filePath) {
  std::filesystem::path path{filePath.path().toStdString()};
  auto fileResult = loadFile(path);

  if (!fileResult) {
    std::cerr << fileResult.error() << std::endl;
  }

  Board board;
  auto boardResult = board.loadBoard(fileResult.value());
  if (!boardResult) {
    std::cerr << boardResult.error() << std::endl;
  }
  this->board = board;
  updateGuiBoard();
}

void Sudoku::solve() {
  Game game(board);
  this->board = game.solve();
  updateGuiBoard();
}

void Sudoku::updateGuiBoard() {
  // Access the root object (ApplicationWindow)
  QObject* rootObject = engine.rootObjects().first();

  // Find the GridLayout object (board)
  QObject* gridObject = rootObject->findChild<QObject*>("board");

  if (gridObject) {
    // Find the Repeater inside the GridLayout by ID (boardRepeater)
    QObject* repeater = gridObject->findChild<QObject*>("boardRepeater");

    if (repeater) {
      // Access the number of items (total cells in the board)
      int itemCount = repeater->property("count").toInt();

      // Access individual TextField items using itemAt(index)
      int rowIndex = 0;
      int columnIndex = 0;
      for (int i = 0; i < itemCount; ++i) {
        QQuickItem* field;
        QMetaObject::invokeMethod(repeater, "itemAt", Qt::DirectConnection,
                                  Q_RETURN_ARG(QQuickItem*, field),
                                  Q_ARG(int, i));

        if (field) {
          if (columnIndex == ROW_COLUMN_LENGTH) {
            columnIndex = 0;
            ++rowIndex;
          }
          // Access the text property of the TextField
          QString textFieldText = field->property("text").toString();

          // Set a new text value for the TextField
          field->setProperty("text", QString::number(this->board.getField(
                                         rowIndex, columnIndex)));
          ++columnIndex;
        }
      }
    }
  }
}
