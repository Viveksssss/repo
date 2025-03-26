import QtQuick 2.15
import QtQuick.Controls
import "../../Info"

Rectangle{
	id:mainStackView
	StackView{
		anchors.top:infoTitle.top
		anchors.left:infoTitle.left
		anchors.right:infoTitle.right
		anchors.bottom:infoTitle.bottom
		color:"red"
	}
}

