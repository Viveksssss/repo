import QtQuick
import QtQuick.Controls
import QtQuick.Window
import Qt5Compat.GraphicalEffects
import "../BasicConfig"
import "../RightPage/Search"
import "../RightPage/Info"
Window{
	visible:true
	title: qsTr("Hello World")
	flags:Qt.FramelessWindowHint|Qt.Window|Qt.WindowSystemMenuHint|
	Qt.WindowMaximizeButtonHint|Qt.WindowMinimizeButtonHint

	// 鼠标拖动区域
	MouseArea{
		anchors.fill:parent
		property point clickPositon:"0,0"
		onPressed:function(mouse){
			clickPositon = Qt.point(mouse.x,mouse.y)
		}
		onPositionChanged:function(mouse) {
			let data = Qt.point(mouse.x-clickPositon.x,mouse.y-clickPositon.y)
			mainWindow.x += data.x
			mainWindow.y += data.y
		}
		onDoubleClicked: {
			mainWindow.showNormal()
		}
		onClicked:{
			BasicConfig.blankAreaClicked()
		}
	}

}
