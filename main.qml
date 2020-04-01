import QtQuick 2.12
import QtQuick.Controls 2.14
import QtQuick.Window 2.12
import calculator.calculator 1.0

Window {
    id: root
    color: settings.secondaryColor
    height: 750
    title: "Calculator"
    minimumHeight: 600
    minimumWidth: 300
    width: 400
    visible: true

    QtObject {
        id: settings

        property bool useDarkTheme: false

        property var primaryColor: useDarkTheme ? "#4E0BCB" : "#DF6589"
        property var primaryColorHover: useDarkTheme ? "#5F23D0" : "#C85A7B"
        property var secondaryColor: useDarkTheme ? "#210070" : "#FFF"
        property var secondaryColorHover: useDarkTheme ? "#37197E" : "#DF6589"

        property var btnTextColor: useDarkTheme ? "#FFF" : primaryColor
        property var btnTextColorHover: "#FFF"
    }

    Calculator {
        id: calculator
    }

    FontLoader {
        id: faSolid
        source: "./fonts/FontAwesomeSolid900.otf"
    }

    Column {
        height: parent.height
        width: parent.width

        Column {
            height: 250
            width: parent.width

            Rectangle {
                color: settings.primaryColor
                height: 100
                width: parent.width

                Switch {
                    display: AbstractButton.IconOnly
                    onToggled: () => settings.useDarkTheme = !settings.useDarkTheme

                    Text {
                        x: 73
                        y: 10
                        color: "#FFF"
                        text: "Dark Theme"
                    }
                }
            }

            Rectangle {
                color: settings.primaryColor
                height: 50
                width: parent.width

                Text {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#FFF"
                    font.pixelSize: 20
                    text: calculator.calculation
                }

            }

            Rectangle {
                color: settings.primaryColor
                height: 100
                width: parent.width

                Text {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#FFF"
                    font.pixelSize: 40
                    text: calculator.display
                }
            }
        }

        Column {
            height: parent.height - 250
            width: parent.width

            Row {
                height: parent.height / 5
                width: parent.width

                CalcButton {
                    btnColor: settings.secondaryColor
                    btnColorHover: settings.secondaryColorHover
                    btnTextColor: settings.btnTextColor
                    btnTextColorHover: settings.btnTextColorHover
                    height: parent.height
                    text: "CE"
                    width: parent.width / 4
                    onClick: calculator.clear
                }

                CalcButton {
                    btnColor: settings.secondaryColor
                    btnColorHover: settings.secondaryColorHover
                    btnTextColor: settings.btnTextColor
                    btnTextColorHover: settings.btnTextColorHover
                    height: parent.height
                    text: "C"
                    width: parent.width / 4
                    onClick: () => calculator.clear(true)
                }

                CalcButton {
                    btnColor: settings.secondaryColor
                    btnColorHover: settings.secondaryColorHover
                    btnTextColor: settings.btnTextColor
                    btnTextColorHover: settings.btnTextColorHover
                    height: parent.height
                    isIcon: true
                    text: "\uf55a"
                    width: parent.width / 4

                    onClick: calculator.back
                }

                CalcButton {
                    btnColor: settings.secondaryColor
                    btnColorHover: settings.secondaryColorHover
                    btnTextColor: settings.btnTextColor
                    btnTextColorHover: settings.btnTextColorHover
                    height: parent.height
                    text: "÷"
                    width: parent.width / 4

                    onClick: calculator.divide
                }
            }

            Row {
                height: (parent.height / 5) * 3
                width: parent.width

                Grid {
                    columns: 3
                    height: parent.height
                    rows: 3
                    width: (parent.width / 4) * 3

                    Repeater {
                        model: 9

                        CalcButton {
                            btnColor: settings.secondaryColor
                            btnColorHover: settings.secondaryColorHover
                            btnTextColor: settings.btnTextColor
                            btnTextColorHover: settings.btnTextColorHover
                            height: parent.height / 3
                            text: index + 1
                            width: parent.width / 3

                            onClick: () => {
                                calculator.numberButtonClick(index + 1)
                            }
                        }
                    }
                }

                Column {
                    height: parent.height
                    width: (parent.width / 4) * 3

                    CalcButton {
                        btnColor: settings.secondaryColor
                        btnColorHover: settings.secondaryColorHover
                        btnTextColor: settings.btnTextColor
                        btnTextColorHover: settings.btnTextColorHover
                        height: parent.height / 3
                        text: "×"
                        width: parent.width / 3

                        onClick: calculator.multiply
                    }

                    CalcButton {
                        btnColor: settings.secondaryColor
                        btnColorHover: settings.secondaryColorHover
                        btnTextColor: settings.btnTextColor
                        btnTextColorHover: settings.btnTextColorHover
                        height: parent.height / 3
                        text: "-"
                        width: parent.width / 3

                        onClick: calculator.subtract
                    }

                    CalcButton {
                        btnColor: settings.secondaryColor
                        btnColorHover: settings.secondaryColorHover
                        btnTextColor: settings.btnTextColor
                        btnTextColorHover: settings.btnTextColorHover
                        height: parent.height / 3
                        text: "+"
                        width: parent.width / 3

                        onClick: calculator.add
                    }
                }
            }

            Row {
                height: parent.height / 5
                width: parent.width

                CalcButton {
                    btnColor: settings.secondaryColor
                    btnColorHover: settings.secondaryColorHover
                    btnTextColor: settings.btnTextColor
                    btnTextColorHover: settings.btnTextColorHover
                    height: parent.height
                    text: "+/-"
                    width: parent.width / 4

                    onClick: calculator.switchSign
                }

                CalcButton {
                    btnColor: settings.secondaryColor
                    btnColorHover: settings.secondaryColorHover
                    btnTextColor: settings.btnTextColor
                    btnTextColorHover: settings.btnTextColorHover
                    height: parent.height
                    text: "0"
                    width: parent.width / 4
                    onClick: () => calculator.numberButtonClick(0)

                }

                CalcButton {
                    btnColor: settings.secondaryColor
                    btnColorHover: settings.secondaryColorHover
                    btnTextColor: settings.btnTextColor
                    btnTextColorHover: settings.btnTextColorHover
                    height: parent.height
                    text: "."
                    width: parent.width / 4

                    onClick: calculator.addFloatingPoint
                }

                CalcButton {
                    btnColor: settings.primaryColor
                    btnColorHover: settings.primaryColorHover
                    height: parent.height
                    text: "="
                    width: parent.width / 4

                    onClick: calculator.equals
                }
            }
        }
    }
}

