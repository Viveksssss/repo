import QtQuick 2.15
import "./MinAndMax"
import "./Info"
import "./Search"
import "./Info/StackPages"
import QtQuick.Controls
Rectangle{
	id:rightRectangle
	// 主界面
	StackView{
		id:mainStackView
		clip:true
		visible: true
		anchors.top:mainMessage.bottom
		anchors.left:parent.left
		anchors.right:parent.right
		anchors.bottom:parent.bottom
		initialItem: "qrc:/RightPage/Info/StackPages/CloudMusic.qml"
	}
	Item{
		id :mainMessage
		anchors.left: parent.left
		anchors.right:parent.right
		anchors.top:parent.top
		height:50
		// 搜索框
		Search{
			id:searchRow
			anchors.left: parent.left
			anchors.leftMargin: 36
			anchors.rightMargin: 18
			anchors.verticalCenter: parent.verticalCenter
		}

		// 中间的个人信息以及设置等
		Info{
			id:infoTitle
		}

		// 最右侧最大化最小化退出
		MinAndMax{
			spacing:15
			id:miniRow
		}
	}
}
