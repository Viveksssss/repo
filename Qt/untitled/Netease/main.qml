import "./LeftPage"
import "./RightPage"
import "./PlayMusic"
import "./Common"
import "./RightPage/Info"


ZWindow {
	width: 1000
	height: 700
	id:mainWindow
	LoginPopup{
		id:popupLogin
		anchors.centerIn: parent

	}
	OtherPopupLogin{
		id:otherLogin
		anchors.centerIn: parent
	}


	// 左侧
	LeftPage{
		id:leftRectangle
		width:255
		anchors.left:parent.left
		anchors.top:parent.top
		anchors.bottom:bottomRectangle.top
		anchors.right:rightRectangle.left
		color:"#1a1a21"
	}
	// 右侧
	RightPage{
		id:rightRectangle
		anchors.left:leftRectangle.right
		anchors.top:parent.top
		anchors.bottom:bottomRectangle.top
		anchors.right:parent.right
		color:"#13131a"
	}

	// 底部
	PlayMusic{
		id:bottomRectangle
		height:70
		anchors.right:parent.right
		anchors.left:parent.left
		anchors.bottom:parent.bottom
		color:"#2d2d37"
	}

}
