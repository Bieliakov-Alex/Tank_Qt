import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    signal northDirectionPressed()
    signal eastDirectionPressed()
    signal southDirectionPressed()
    signal westDirectionPressed()

    width: 640
    height: 480
    visible: true
    title: qsTr("Tanks")

    Item {
        anchors.fill: parent
        focus: true

        Keys.onPressed: {
            switch(event.key) {
            case Qt.Key_Left:
                westDirectionPressed();
                event.accepted = true;
                break;
            case Qt.Key_Up:
                northDirectionPressed();
                event.accepted = true;
                break;
            case Qt.Key_Right:
                eastDirectionPressed();
                event.accepted = true;
                break;
            case Qt.Key_Down:
                southDirectionPressed();
                event.accepted = true;
                break;
            default:
                event.accepted = true;
                break;
            }
        }

        Repeater {
            model: enemy_list
            delegate: Rectangle{
                color: "#FF0000"

                x: modelData.x_pos
                y: modelData.y_pos
                width: model.tank_size
                height: model.tank_size
            }
        }

        Rectangle {
            color: "#000000"

            width: player.tank_size
            height: player.tank_size

            x: player.x_pos
            y: player.y_pos
        }

    }

}
