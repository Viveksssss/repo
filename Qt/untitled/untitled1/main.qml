import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window
import Qt5Compat.GraphicalEffects


Window {
	width: 640
	height: 480
	visible: true
	title: "main window"
	color:"white"

	// Text {

	// 	id: text

	// 	text: qsTr("helloasdasdadsadasdasdasdasdsa")
	// 	font.family:"黑体"
	// 	color:"red"
	// 	font.pixelSize: 20
	// 	width:200
	// 	height:200
	// 	wrapMode: Text.Wrap
	// 	// anchors.centerIn: parent
	// 	z:100
	// 	elide:Text.ElideRight
	// }
	// Item{
	// 	x:300
	// 	y:200
	// 	width:200
	// 	height:100
	// 	children: Rectangle{
	// 		anchors.centerIn: parent
	// 		color:"cyan"
	// 		width:100
	// 		height:100
	// 		anchors.fill: parent
	// 		visible: true
	// 		opacity:0.5
	// 	}
	// 	scale: 2
	// 	rotation:45

	// }



	// Rectangle{
	// 	color:"#876"
	// 	width:200
	// 	height:200
	// 	x:200
	// 	y:200
	// 	id:res
	// }
	// Rectangle{
	// 	color:"cyan"
	// 	width:50
	// 	height:50
	// 	y:200
	// 	// anchors.left:res.right
	// 	// anchors.centerIn: res
	// 	anchors.horizontalCenter: res.left
	// 	anchors.verticalCenter: res.verticalCenter
	// 	// anchors.fill:res
	// }


	// Item{
	// 	Rectangle{
	// 		opacity: 0.7
	// 		// radius:20
	// 		color:"cyan"
	// 		width:200
	// 		height:200
	// 		topRightRadius: 200
	// 		topLeftRadius:40
	// 		bottomLeftRadius: 70
	// 		bottomRightRadius: 30
	// 	}

	// }
	// Item{
	// 	/*
	// 		不适用topRightRadius等实现边角圆滑
	// 	*/
	// 	clip:true
	// 	anchors.centerIn: parent
	// 	height:200
	// 	width:200

	// 	Rectangle{
	// 		width:200
	// 		height:200
	// 		color:"red"
	// 		radius:20
	// 		y:20
	// 	}

	// }

	// TextField{
	// 	width:200
	// 	height:50
	// 	leftPadding:20
	// 	rightPadding:20
	// 	background:
	// 		Rectangle{
	// 			anchors.fill:parent
	// 			border.color: "red"
	// 			border.width:2
	// 			color:"yellow"
	// 			radius: 20
	// 	}
	// 	placeholderText:"请输入密码"
	// 	font.pixelSize: 30
	// 	horizontalAlignment: Text.AlignHCenter
	// 	verticalAlignment: Text.AlignVCenter
	// 	echoMode:"Password"
	// 	selectByMouse: true
	// 	maximumLength: 8
	// }

	// TextArea{
	// 	id:aaa
	// 	anchors.fill:parent
	// 	background:Rectangle{
	// 		color:"cyan"
	// 		anchors.fill: parent
	// 		border.color:red
	// 		border.width:2
	// 	}
	// 	wrapMode: "Wrap"
	// 	font.pixelSize: 40
	// 	font.underline: true
	// 	selectByMouse: true
	// 	font.bold: true
	// 	font.italic: true

	// }



	// Image {
	// 	id: name
	// 	source: "/Image/31.png"
	// 	anchors.fill:parent
	// }

	// 事件
	// Rectangle{
	// 	id:aaa
	// 	x:400
	// 	width:20
	// 	height:20
	// 	color:"cyan"
	// 	focus:true
	// 	Drag.active:area.drag.active
	// 	Keys.onPressed: {
	// 			if(event.key === Qt.Key_A){
	// 				console.log("A")
	// 			}
	// 	}
	// 	MouseArea{
	// 		id:area

	// 		hoverEnabled: true
	// 		anchors.fill:parent
	// 		onClicked: {
	// 			aaa.color="red"
	// 		}
	// 		onDoubleClicked: {
	// 			aaa.color="orange"
	// 		}
	// 		onEntered: {
	// 			aaa.color="orange"
	// 		}
	// 		onExited: {
	// 			aaa.color="#454545"
	// 		}
	// 		onPressed: {
	// 			aaa.color="#909090"
	// 		}
	// 		onWheel: {
	// 			if(wheel.angleDelta.y>0)
	// 				console.log("前")
	// 			else console.log("后")
	// 		}
	// 		onReleased: {
	// 			ppp.color="orange"
	// 		}
	// 		drag.target: aaa
	// 		drag.axis: Drag.XAndYAxis

	// 	}

	// }

	// DropArea{

	// 	width:300
	// 	height:200
	// 	Rectangle{
	// 		id:ppp
	// 		color:"red"
	// 		anchors.fill:parent
	// 	}
	// 	onEntered: {
	// 		ppp.color="pink"
	// 	}

	// }

	// Button{
	// 	text: "good"
	// 	display:"TextUnderIcon"
	// 	width:50
	// 	height:50
	// 	icon.source: "/Image/31.png"
	// 	// Rectangle{
	// 	// 	anchors.fill:parent
	// 	// 	color:"red"
	// 	// 	radius:20
	// 	// }

	// 	onClicked: {
	// 		console.log("哎哟")
	// 	}
	// 	onCanceled: {
	// 		console.log("取消")
	// 	}
	// 	onPressed: {
	// 		console.log("good")
	// 	}
	// 	onPressAndHold: {
	// 		console.log("啊。别停")
	// 	}

	// }

	// DelayButton{
	// 	width:200
	// 	delay:2000
	// 	onActivated: {
	// 		console.log("good")
	// 		color="orange"
	// 	}
	// 	onReleased: {
	// 		color="white"
	// 	}
	// 	onProgressChanged: {
	// 		console.log("goooooood!")
	// 	}

	// }

	// Switch{
	// 	x:50
	// 	y:50
	// 	onVisualPositionChanged: {
	// 		console.log("great",visualPosition)
	// 	}
	// 	onPressedChanged: {
	// 		console.log("great too",position)
	// 	}
	// 	onCheckedChanged: {
	// 		console.log("checked",checked)
	// 	}
	// }

	// ButtonGroup{
	// 	id:group
	// 	exclusive: false
	// }


	// RadioButton{
	// 	ButtonGroup.group:group
	// 	y:50
	// 	x:100
	// 	width:50
	// 	scale: 2
	// }
	// RadioButton{
	// ButtonGroup.group:group
	// 	y:100
	// 	x:100
	// 	width:50
	// 	scale: 2
	// }
	// RadioButton{
	// 	y:150
	// 	x:100
	// 	width:50
	// 	scale: 2

	// }


	// Popup{
	// 	id:pop
	// 	width:500
	// 	height:300
	// 	anchors.centerIn: parent
	// 	onAboutToHide: {
	// 		console.log("close")
	// 	}
	// 	onAboutToShow: {
	// 		console.log("open")
	// 	}
	// 	modal: true
	// 	closePolicy:Popup.NoAutoClose
	// 	Button{
	// 		width:50
	// 		anchors.right:parent.right
	// 		onClicked: {
	// 			pop.close()
	// 		}
	// 	}
	// }

	// Button{
	// 	width:50
	// 	y:400

	// 	onClicked: {
	// 		pop.open()
	// 	}
	// }
	// Button{
	// 	width:50
	// 	y:450
	// 	onClicked: {
	// 		pop.close()
	// 	}
	// }

	// Button{
	// 	width:50

	// }
	// Dialog{

	// 	title:"good"
	// 	modal:false
	// 	standardButtons: Dialog.Ok|Dialog.Cancel
	// 	id:ppp
	// 	width:200
	// 	height:200
	// 	onRejected:{
	// 		console.log("no")
	// 	}
	// 	onAccepted: {
	// 		console.log("yes")
	// 	}
	// }


	// Button{
	// 	onClicked: {
	// 		ppp.open()
	// 	}
	// }

	// Window{
	// 	title:"asd"
	// 	visible: true
	// 	modality: Qt.WindowModal
	// 	width:300
	// 	height:250
	// }


	// FileDialog{
	// 	id:ppp
	// 	onAccepted: {
	// 		console.log(currentFile)
	// 	}
	// 	acceptLabel: "选我吧"
	// 	rejectLabel:"不要"
	// 	fileMode: FileDialog.OpenFiles
	// }
	// FolderDialog{
	// 	id:ppp;
	// 	onAccepted: {
	// 		console.log(currentFolder)
	// 	}
	// 	acceptLabel: "选我吧"
	// 	rejectLabel:"不要"
	// }

	// ColorDialog{
	// 	options: ColorDialog.DontUseNativeDialog
	// 	id:ppp
	// 	selectedColor: document.color
	// 	title:"color"
	// 	visible: true

	// }

	// FontDialog{
	// 	id:ppp
	// 	onAccepted: {
	// 		console.log(currentFont)
	// 	}
	// 	visible: true
	// 	// font.pixelSize: 20

	// }

	// MessageDialog{
	// 	title: "asdasdsad"
	// 	id:ppp
	// 	flags:  Qt.Dialog | Qt.CustomizeWindowHint | Qt.WindowTitleHint
	// 	text:"this is a dialog"
	// 	buttons:MessageDialog.Ok|MessageDialog.Cancel

	// }


	// Rectangle{
	// 	id:ppp
	// 	color :"red"
	// 	width:200
	// 	height:200
	// 	anchors.centerIn: parent
	// 	Text {
	// 		id: text
	// 		text: qsTr("哈哈哈")
	// 		font.pixelSize: 50
	// 	}
	// 	MouseArea{
	// 		anchors.fill:parent
	// 		hoverEnabled: true
	// 		onEntered: {
	// 			ppp.state = "from"
	// 		}
	// 		onExited: {
	// 			ppp.state = "to"
	// 		}
	// 	}
	// 	states: [
	// 		State {
	// 			name: "to"
	// 			PropertyChanges {
	// 				target: ppp
	// 				color : "red"

	// 			}
	// 			PropertyChanges {
	// 				target: text
	// 				text :"come"

	// 			}
	// 		},
	// 		State{
	// 			name:"from"
	// 			PropertyChanges {
	// 				target: ppp
	// 				color :"cyan"
	// 			}
	// 			PropertyChanges {
	// 				target: text
	// 				text:"out"

	// 			}
	// 		}
	// 	]


	// 	transitions: [
	// 		Transition {
	// 			from:"from"
	// 			to:"to"
	// 			ColorAnimation {
	// 				target:ppp
	// 				duration: 500
	// 			}
	// 		}
	// 	]
	// }


	// Rectangle{
	// 	id:ppp
	// 	width:100
	// 	height:50
	// 	anchors.centerIn: parent
	// 	color:"red"

	// 	Behavior on width{
	// 		NumberAnimation{
	// 			duration: 300
	// 		}
	// 	}




	// 	// PropertyAnimation{
	// 	// 	duration: 3000
	// 	// 	id:anti
	// 	// 	target:ppp
	// 	// 	property:"width"
	// 	// 	from:100
	// 	// 	to:500
	// 	// }

	// 	// PropertyAnimation{
	// 	// 	id:anti2
	// 	// 	target:ppp
	// 	// 	property:"width"
	// 	// 	from:500
	// 	// 	to:100
	// 	// 	easing.type: Easing.InOutQuad
	// 	// }
	// }

	// Button{
	// 	width:50
	// 	onClicked: {
	// 		ppp.width=400
	// 	}
	// }
	// Button{
	// 	width:50
	// 	x:50
	// 	onClicked: {
	// 		ppp.width=700
	// 	}
	// }


	// Rectangle{
	// 	width:200
	// 	height:200
	// 	anchors.centerIn: parent
	// 	id:ppp
	// 	color:"red"
	// 	MouseArea{
	// 		anchors.fill:parent
	// 		onClicked: {
	// 			// pap.start()
	// 			ppa.start()
	// 		}
	// 	}
	// }

	// 并行动画
	// ParallelAnimation{
	// id:pap
	// 	PropertyAnimation{
	// 		duration: 3000
	// 		id:anti
	// 		target:ppp
	// 		property:"width"
	// 		from:100
	// 		to:500
	// 	}

	// 	PropertyAnimation{
	// 		id:anti2
	// 		target:ppp
	// 		duration:3000
	// 		property:"height"
	// 		from:100
	// 		to:500
	// 		easing.type: Easing.InOutQuad
	// 	}

	// 	PropertyAnimation{
	// 		id:anti3
	// 		target:ppp
	// 		duration:3000
	// 		property:"radius"
	// 		from:0
	// 		to:20
	// 		easing.type: Easing.InOutQuad
	// 	}

	// }

	// 串行动画
	// SequentialAnimation{
	// 	id:ppa
	// 	PropertyAnimation{
	// 		duration: 300
	// 		id:anti11
	// 		target:ppp
	// 		property:"width"
	// 		from:100
	// 		to:500
	// 	}

	// 	PropertyAnimation{
	// 		id:anti222
	// 		target:ppp
	// 		duration:300
	// 		property:"height"
	// 		from:100
	// 		to:500
	// 		easing.type: Easing.InOutQuad
	// 	}

	// 	PropertyAnimation{
	// 		id:anti333
	// 		target:ppp
	// 		duration:300
	// 		property:"radius"
	// 		from:0
	// 		to:20
	// 		easing.type: Easing.InOutQuad
	// 	}

	// 	ScriptAction{
	// 		script:
	// 			console.log("script")
	// 	}
	// }
}



