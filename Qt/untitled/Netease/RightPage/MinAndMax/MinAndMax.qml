import QtQuick 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Controls

Row{
	spacing:10
	id:miniRow
	anchors.rightMargin:mainWindow.width*0.02
	anchors.right:parent.right
	anchors.verticalCenter: parent.verticalCenter
	Image{
		id:miniImage
		anchors.verticalCenter: parent.verticalCenter
		source:"/Img/Resources/title/mini.png"
		layer.enabled: false
		layer.effect: ColorOverlay{
			source:miniImage
			color:"yellow"
		}
		MouseArea{
			anchors.fill:parent
			hoverEnabled: true
			onEntered: {
				miniImage.layer.enabled = true
			}
			onExited: {
				miniImage.layer.enabled = false
			}
		}
	}
	// 最小化
	Item{
		width:miniImage.width-10
		height:miniImage.height

		id:outerMiniRectangle
		Rectangle{
			id:miniRectangle
			width:outerMiniRectangle.width-3
			height:2
			anchors.verticalCenter:parent.verticalCenter
			color:"#75777f"

		}
		MouseArea{
				anchors.fill:parent
				hoverEnabled: true
				onEntered: {
					miniRectangle.color="yellow"
				}
				onExited: {
					miniRectangle.color="#75777f"
				}
				onClicked: {
					mainWindow.showMinimized()
				}
			}
	}
	// 最大化
	Rectangle{
		id:maxRectangle
		width:18
		height:18
		anchors.verticalCenter:parent.verticalCenter
		border.color:"#75777f"
		color:"transparent"
		border.width:1
		radius:3
		property int isFull:0
		MouseArea{
			anchors.fill:parent
			hoverEnabled: true
			onEntered: {
				maxRectangle.border.color="yellow"
			}
			onExited: {
				maxRectangle.border.color="#75777f"
			}
			onClicked: {
				if(maxRectangle.isFull==0){
					mainWindow.showMaximized()
					maxRectangle.isFull = 1
				}else{
					maxRectangle.isFull = 0;
					mainWindow.showNormal()
				}
			}
		}
	}
	// 关闭确认弹窗
	Dialog {
		clip:false
		id: closeDialog
		title: "确认关闭"
		modal: true // 阻止背景交互
		// anchors.centerIn: mainWindow
		standardButtons: Dialog.Yes | Dialog.No
		Label {
		    text: "确定要关闭窗口吗？"
		    anchors.centerIn: parent
		}
		onAccepted: mainWindow.close() // 点击“是”关闭窗口
	}
	// 关闭
	Image{
		id:closeImage
		anchors.leftMargin:7
		anchors.verticalCenter: parent.verticalCenter
		source:"/Img/Resources/title/close.png"
		layer.enabled: false
		layer.effect: ColorOverlay{
			source:closeImage
			color:"yellow"
		}
		MouseArea{
			anchors.fill:parent
			hoverEnabled: true
			onEntered: {
				closeImage.layer.enabled = true
			}
			onExited: {
				closeImage.layer.enabled = false
			}
			onClicked: {
				closeDialog.open()
			}
		}
	}
}
