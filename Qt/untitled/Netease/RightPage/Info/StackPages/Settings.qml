import QtQuick 2.15
import QtQuick.Controls
import "../../../BasicConfig"
import "../"

Item{
	// anchors.fill:parent
	Item{
		id:upperTitle
		anchors.left:parent.left
		anchors.top:parent.top
		anchors.leftMargin: 40
		Label{
			id:settingLabel
			font.family: BasicConfig.commFont
			color:"yellow"
			text:"设置"
			font.pixelSize: 32
			anchors.top:parent.top
			anchors.topMargin: 20
		}

		Flow{
			id:settingTitleFlow
			anchors.left:settingLabel.left
			anchors.top:settingLabel.bottom
			anchors.topMargin: 25
			spacing:15
			height:25
			Repeater{
				id:selectIndexRepeater
				anchors.fill:parent
				model:["账号","常规","系统","播放","信息与隐私","快捷键","音质与下载","桌面歌词","工具","关于"]
				property int selectIndex:0
				delegate:Item{
					height:30
					width:selectorLabel.implicitWidth
					Label{
						id:selectorLabel
						text:modelData
						font.pixelSize: 18
						font.bold:true
						font.family: "黑体"
						anchors.fill:parent
						color:selectIndexRepeater.selectIndex === index?"white":"#a1a1a3"
					}
					Rectangle{
						visible:selectIndexRepeater.selectIndex===index
						anchors.left:selectorLabel.left
						anchors.right:selectorLabel.right
						anchors.top:selectorLabel.bottom
						height:2
						color:"#eb4d44"
					}
					MouseArea{
						anchors.fill:parent
						hoverEnabled: true
						onEntered: {
							cursorShape = Qt.PointingHandCursor
						}
						onExited: {
							cursorShape = Qt.ArrowCursor
						}
						onClicked:{
							selectIndexRepeater.selectIndex = index
						}
					}
				}
			}
		}

		Rectangle{
			id:cutRectangle
			anchors.left:parent.left
			anchors.right:parent.right
			anchors.topMargin: 10
			width:670
			anchors.top:settingTitleFlow.bottom
			height:2
			color:"#212127"
		}

	}
	Flickable{
		id:flickContent
		z: 200
		// width: 640
		anchors.top:upperTitle.bottom
		anchors.topMargin: 120
		anchors.right:parent.right
		anchors.left:parent.left

		ScrollBar.vertical: ScrollBar{
			anchors.right:parent.right
			anchors.rightMargin: 5
			width:3
			height:100
			contentItem: Rectangle{
				visible: parent.active
				implicitWidth: 10
				radius:4
				color:"#42424b"
			}
		}

		Column{
			id:contentColumn
			anchors.fill:parent
			anchors.leftMargin: 0
			anchors.rightMargin: 0
			anchors.topMargin: 10
			anchors.bottomMargin: 0
			spacing:30

			//账户
			Item{
				anchors.left:parent.left
				anchors.leftMargin: 0
				height:100
				width:parent.width
				Label{
					id:tmp1
					// height: 76
					text:"账号"
					font.bold:true
					anchors.left:parent.left
					anchors.leftMargin: 38
					anchors.topMargin: 20
					color:"white"
					font.pixelSize: 20
				}
				Label{
					id: tmp2
					text:"登录大胖熊音乐，手机电脑多端同步"
					font.family: "微软雅黑 Light"
					anchors.left:tmp1.right
					anchors.leftMargin: 106
					anchors.verticalCenter: tmp1.verticalAlignment
					color:"white"
					font.pixelSize: 20
				}

				Rectangle{
					id:loginInSetting
					radius:10
					width:100
					height:30
					anchors.left:tmp2.left
					anchors.top:tmp2.bottom
					anchors.topMargin: 10
					color:"#e84d5f"
					Label{
						text:"立即登录"
						font.pixelSize: 18
						font.family: BasicConfig.commFont
						color:"white"
						anchors.centerIn: parent
					}
					MouseArea{
						anchors.fill:parent
						hoverEnabled: true
						onEntered: {
							parent.opacity = 0.8
							cursorShape = Qt.PointingHandCursor
						}
						onExited: {
							parent.opacity = 1
							cursorShape = Qt.ArrowCursor
						}
						onClicked: {
							popupLogin.open()
						}
					}
				}
			}
		}



	}

}




/*##^##
Designer {
    D{i:0}D{i:1;locked:true}D{i:2;locked:true}D{i:3;locked:true}D{i:4;locked:true}D{i:9;locked:true}
D{i:17;locked:true}D{i:18;locked:true}D{i:19;locked:true}
}
##^##*/
