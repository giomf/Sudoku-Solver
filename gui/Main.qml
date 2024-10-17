import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 540
    height: 400
    //minimumWidth: 400
    //minimumHeight: 450
    title: qsTr("Sudoku Board")

    // Calculate font size based on the width of the window
    property real fontSize: Math.min(width / 20, height / 25)
    property int boardSize: 9

    ColumnLayout {
        anchors.fill: parent  // Fill the entire ApplicationWindow
        anchors.margins: 10   // Add some margins around the layout

        GridLayout {
            id: grid
            objectName: "board"
            columns: boardSize
            Layout.fillWidth: true  // Make the grid layout fill the available width
            Layout.fillHeight: true  // Make the grid layout fill the available height

            Repeater {
                objectName: "boardRepeater"
                model: boardSize * boardSize
                TextField {
                    objectName: "field"
                    placeholderText: qsTr("")
                    inputMethodHints: Qt.ImhDigitsOnly  // Only allows digits
                    validator: IntValidator { bottom: 0; top: 9 } // Restrict input to single-digit numbers
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    // Set the minimum size
                    Layout.minimumWidth: 30
                    Layout.minimumHeight: 30
                    // Allow the TextField to grow
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    // Bind font size to the ApplicationWindow's size
                    font.pointSize: fontSize
                }
            }
        }

        RowLayout {
            Layout.fillHeight: true  // Make the row layout fill the available width
            Layout.fillWidth: true  // Make the row layout fill the available width
            Layout.preferredHeight: 60  // Set a preferred height for the button row

            Button {
                id: solveButton
                text: qsTr("Solve")
                onClicked: {
                    console.log("Solve button clicked")
                    // Add your logic to solve the Sudoku
                }
                Layout.fillWidth: true  // Make the button fill the available width
                Layout.fillHeight: true  // Make the button fill the available height
            }

            Button {
                id: loadButton
                text: qsTr("Load")
                onClicked: {
                    console.log("Load button clicked")
                    // Add your logic to load a Sudoku puzzle
                }
                Layout.fillWidth: true  // Make the button fill the available width
                Layout.fillHeight: true  // Make the button fill the available height
            }
        }
    }
}
