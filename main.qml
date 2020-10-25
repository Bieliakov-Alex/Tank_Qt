import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tanks")

    Rectangle {
        color: "#000000"

        width: player.tank_size
        height: player.tank_size

        x: player.x_pos
        y: player.y_pos
    }
}
