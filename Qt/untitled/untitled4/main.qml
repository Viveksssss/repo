import QtQuick 2.12
import QtQuick.Window 2.12
import Qt5Compat.GraphicalEffects
import QtQuick
import QtQuick.Controls
import QtQml
import QtQuick.Dialogs
import QtQuick.Layouts

Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("Hello World")

	// RadialGradient{
	// 	anchors.fill:parent
	// 	horizontalRadius: 300
	// 	GradientStop { position: 0.0; color: "white" }
	// 	GradientStop { position: 0.5; color: "green" }
	// 	GradientStop { position: 1.0; color: "transparent" }
	// }
	// ConicalGradient{
	// 	id:ppp
	// 	anchors.fill: parent
	// 	angle: 0.0
	// 	  gradient:Gradient {
	// 		   GradientStop {
	// 		      position: 0.000
	// 		      color: Qt.rgba(1, 0, 0, 1)
	// 		   }
	// 		   GradientStop {
	// 		      position: 0.167
	// 		      color: Qt.rgba(1, 1, 0, 1)
	// 		   }
	// 		   GradientStop {
	// 		      position: 0.333
	// 		      color: Qt.rgba(0, 1, 0, 1)
	// 		   }
	// 		   GradientStop {
	// 		      position: 0.500
	// 		      color: Qt.rgba(0, 1, 1, 1)
	// 		   }
	// 		   GradientStop {
	// 		      position: 0.667
	// 		      color: Qt.rgba(0, 0, 1, 1)
	// 		   }
	// 		   GradientStop {
	// 		      position: 0.833
	// 		      color: Qt.rgba(1, 0, 1, 1)
	// 		   }
	// 		   GradientStop {
	// 		      position: 1.000
	// 		      color: Qt.rgba(1, 0, 0, 1)
	// 		   }
	// 	 }

	// }
	// PropertyAnimation{
	// 	id:pap
	// 	target:ppp
	// 	properties: "angle"
	// 	from:0
	// 	to:360
	// 	duration: 700
	// }


	// Button{
	// 	width:50
	// 	height:50
	// 	onClicked: {
	// 		pap.start()
	// 	}
	// }


	// Rectangle{
	// 	width:500
	// 	height:300
	// 	LinearGradient{
	// 		anchors.fill:parent
	// 		start:Qt.point(0,0)
	// 		end:Qt.point(300,300)
	// 		gradient: Gradient {
	// 			   GradientStop {
	// 			      position: 0.000
	// 			      color: Qt.rgba(1, 0, 0, 1)
	// 			   }
	// 			   GradientStop {
	// 			      position: 0.167
	// 			      color: Qt.rgba(1, 1, 0, 1)
	// 			   }
	// 			   GradientStop {
	// 			      position: 0.333
	// 			      color: Qt.rgba(0, 1, 0, 1)
	// 			   }
	// 			   GradientStop {
	// 			      position: 0.500
	// 			      color: Qt.rgba(0, 1, 1, 1)
	// 			   }
	// 			   GradientStop {
	// 			      position: 0.667
	// 			      color: Qt.rgba(0, 0, 1, 1)
	// 			   }
	// 			   GradientStop {
	// 			      position: 0.833
	// 			      color: Qt.rgba(1, 0, 1, 1)
	// 			   }
	// 			   GradientStop {
	// 			      position: 1.000
	// 			      color: Qt.rgba(1, 0, 0, 1)
	// 			   }
	// 		}
	// 	}
	// }


	// Item{
	// 	id:item
	// 	width:500
	// 	height:400
	// 	anchors.fill: parent
	// }

	// // }
	// // Text{
	// // 	text:"亮度/对比度"
	// // 	anchors.right:sl.left
	// // 	anchors.verticalCenter: sl.verticalCenter
	// // 	z:100
	// // 	color:"red"
	// // }
	// // Slider{
	// // 	id:sl
	// // 	anchors.horizontalCenter: parent.horizontalCenter
	// // 	width:400
	// // 	height: 30
	// // 	z:100
	// // 	from :0
	// // 	to:1
	// // 	onValueChanged: {
	// // 		console.log(value)
	// // 		bc.brightness = value
	// // 		bc.contrast = value
	// // 	}
	// // }
	// // BrightnessContrast{
	// // 	id:bc
	// // 	anchors.fill:item
	// // 	source:ppp
	// // 	brightness: 0.5
	// // 	contrast: 0.5
	// // }

	// // 着色HSL
	// Colorize{
	// 	width:300
	// 	height:300
	// 	id:rize
	// 	anchors.fill:parent
	// 	source:ppp
	// 	hue:0.0 // 0-1
	// 	saturation:0.0 // 0-1
	// 	lightness:0.0 // -1-1
	// }
	// Slider{
	// 	id:sl1
	// 	anchors.horizontalCenter: parent.horizontalCenter
	// 	width:400
	// 	height: 30
	// 	z:100
	// 	from :0
	// 	to:1
	// 	y:0
	// 	onValueChanged: {
	// 		console.log(value)
	// 		rize.hue = value
	// 	}
	// }

	// Slider{
	// 	id:sl2
	// 	anchors.horizontalCenter: parent.horizontalCenter
	// 	width:400
	// 	height: 30
	// 	z:100
	// 	y:50
	// 	from :0
	// 	to:1
	// 	onValueChanged: {
	// 		console.log(value)
	// 		rize.saturation = value
	// 	}
	// }


	// Slider{
	// 	id:sl3
	// 	anchors.horizontalCenter: parent.horizontalCenter
	// 	width:400
	// 	y:80
	// 	height: 30
	// 	z:100
	// 	from :-1
	// 	to:1
	// 	onValueChanged: {
	// 		console.log(value)
	// 		rize.lightness = value
	// 		// sss.desaturation =value
	// 		gamma.gamma =value
	// 	}
	// }


	// Desaturate{
	// 	id:sss
	// 	source:img
	// 	anchors.fill:item
	// 	desaturation:0

	// }

	//伽马调整
	// GammaAdjust{
	// 	id:gamma
	// 	source:img
	// 	gamma:0

	// }


	// HueSaturation{
	// 	id:hs
	// 	source:img
	// 	hue:-0.3
	// 	saturation: -0.3
	// 	lightness: -1
	// }
	// Image {
	// 	id: ppp
	// 	source: "/Image/31.png"
	// 	width:300
	// 	height:300
	// 	// anchors.centerIn: parent
	// 	fillMode: Image.PreserveAspectFit
	// 	smooth: true
	// }

	// Slider{
	// 	id:sl
	// 	from :0
	// 	to:100
	// 	onValueChanged: {
	// 		// ppp.scale = value
	// 		rb.loops = value
	// 	}
	// }
	// 快速模糊
	// FastBlur{
	// 	id:fb
	// 	source:ppp
	// 	anchors.fill: ppp
	// 	scale:0.1
	// 	radius:32
	// }

	// 高斯模糊
	// GaussianBlur{
	// 	id:gs
	// 	source:ppp
	// 	anchors.fill:ppp
	// 	radius:32
	// }

	// 递归模糊
	// RecursiveBlur{
	// 	id:rb
	// 	source:ppp
	// 	anchors.fill:ppp
	// 	radius:2
	// 	loops:70
	// }

	// 遮罩模糊
	// MaskedBlur{
	// 	anchors.fill:ppp
	// 	source:ppp
	// 	radius:10
	// 	maskSource: mask

	// }
	// LinearGradient{
	// 	id:mask
	// 	anchors.fill:ppp
	// 	start:Qt.point(0,0)
	// 	end:Qt.point(300,300)
	// 	gradient:  Gradient {
	// 	   GradientStop{position:0.4;color:"ffffff"}
	// 	   GradientStop{position:1;color:"#00ffff"}
	// 	}
	// 	visible: false
	// }




	// 遮罩模糊
	//    Image {
	//	id: bug
	//	source: "/Image/31.png"
	//	sourceSize: Qt.size(parent.width, parent.height)
	//	smooth: true
	//	visible: true
	//    }

	 //     LinearGradient{
		// id:mask
		// anchors.fill:bug
		// gradient: Gradient{
		// 	GradientStop{position:0.48;color:"#ffffffff"}
		// 	GradientStop{position:0.7;color:"#00ffffff"}
		// }
		// start:Qt.point(0,0)
		// end:Qt.point(500,0)
	 //     }

	 //     MaskedBlur{
		// anchors.fill: bug
		// source:bug
		// maskSource: mask
		// radius:16
		// samples:24
	 //     }
	// 方向模糊
	// DirectionalBlur{
	// 	anchors.fill:bug
	// 	source:bug
	// 	length:32
	// 	samples:32
	// 	// angle:45
	// }

	// 镜像模糊
	// RadialBlur{
	// 	anchors.fill:bug
	// 	source:bug
	// 	samples:32
	// 	angle:20
	// }

	// 缩放模糊
	// ZoomBlur{
	// 	anchors.fill:bug
	// 	source:bug
	// 	samples:32
	// 	length:18
	// }

	// 图片混合
	// Item{
	// 	id:item
	// 	width:500
	// 	height:300
	// 	anchors.centerIn: parent
	// }
	// Image {
	// 	id: bug
	// 	source: "/../../../../Download/aaaaaa.png"
	// 	anchors.fill:parent

	// }
	// Image {
	// 	id: bug2
	// 	source: "/Image/31.png"
	// 	anchors.fill:parent

	// }

	// Blend{
	// 	anchors.fill:item
	// 	source:bug
	// 	foregroundSource: bug2
	// 	mode:"difference"
	// }


	// ColorOverlay{
	// 	anchors.fill:item
	// 	source:bug
	// 	color:"#240000ff"
	// }


	// 投影/模糊
	// DropShadow{
	// 	anchors.fill:ppp
	// 	source:ppp
	// 	horizontalOffset: 10
	// 	verticalOffset: 10
	// 	radius: 10
	// 	samples:20
	// 	transparentBorder: true
	// }

	//内阴影  innershadow
	// InnerShadow{
	// 	anchors.fill:ppp
	// 	source:ppp
	// 	horizontalOffset: -10
	// 	verticalOffset: -10
	// 	radius: 10
	// 	samples:20
	// }

	// 发光
	// Glow{
	// 	anchors.fill:ppp
	// 	source:ppp
	// 	radius: 10
	// 	samples:20
	// 	color:"green"
	// }
	// 内光
	// RectangularGlow{
	// 	anchors.fill:ppp
	// 	color:"blue"
	// 	glowRadius: 10
	// 	cornerRadius: Math.min(ppp.width,ppp.height)/2+glowRadius
	// }


	/*
		视图/代理/模型
		视图不具体显示，但是可以存放数据，以及怎样存放数据
		代理就是决定如何存放，如下rectangle;
		模型就决定存放什么数据，如下'a','b','c'
	*/

	/*
		下面在Text获取model的数据的时候使用了modelData这个属性，这个属性没有提示，没有文档，但是存在
	*/

	// Column{
	// 	spacing:10
	// 	Button{
	// 		text:"添加数据"
	// 		id:add
	// 		onClicked: {
	// 			listmodel.append({name:"的撒旦"+listview.count,cost:"23"})
	// 			// listmodel.insert(0,{name:"的撒旦"+listview.count,cost:"23"})
	// 			listview.positionViewAtEnd()
	// 		}
	// 	}
	// 	Button{
	// 		text:"删除数据"
	// 		id:del
	// 		onClicked:{
	// 			listmodel.remove(listview.positionViewAtBeginning())
	// 			// listmodel.remove(listview.positionViewAtIndex(0,listview.Beginning()))

	// 		}
	// 	}
	// 	anchors.right: parent.right

	// }

	// ListView{
	// 	section{
	// 		criteria: ViewSection.FirstCharacter
	// 		labelPositioning:ListView.SnapOneItem
	// 		delegate: Rectangle{
	// 			width:50
	// 			height:50
	// 			radius:25
	// 			Text{
	// 				text:section
	// 				anchors.centerIn: parent
	// 			}
	// 		}
	// 		property: "name"
	// 	}
	// 	add:Transition {
	// 		NumberAnimation{
	// 			properties:"y"
	// 			duration: 300
	// 		}
	// 	}
	// 	addDisplaced: Transition {
	// 		NumberAnimation{
	// 			properties: "y"
	// 			duration: 300
	// 		}
	// 	}
	// 	remove:Transition {
	// 		NumberAnimation{
	// 			properties: "opacity"
	// 			duration: 800
	// 			from :1
	// 			to : 0
	// 		}

	// 	}
	// 	removeDisplaced: Transition {
	// 		NumberAnimation{
	// 			properties: "y"
	// 			duration: 800
	// 		}
	// 	}
	// 	footerPositioning: ListView.OverlayFooter
	// 	headerPositioning: ListView.OverlayHeader
	// 	cacheBuffer: 400
	// 	id:listview
	// 	highlightMoveDuration:2000
	// 	highlightFollowsCurrentItem: true
	// 	anchors.rightMargin: 200
	// 	anchors.fill: parent
	// 	spacing:10 // 行间距
	// 	highlight:Item{
	// 		// 方法
	// 		function setText(name,cost){
	// 			hl.text = name
	// 			hr.text = cost

	// 		}

	// 		width:parent.width
	// 		height:50
	// 		z:2
	// 		Rectangle{
	// 			id:lefts
	// 			anchors.left : parent.left
	// 			anchors.top : parent.top
	// 			anchors.bottom : parent.bottom
	// 			width:parent.width/2-5
	// 			color:"yellow"
	// 			// opacity: 0.3
	// 			Text{
	// 				id:hl
	// 				anchors.centerIn: parent
	// 				font.pixelSize: 30
	// 			}
	// 		}
	// 		Rectangle{
	// 			id:rights
	// 			width:parent.width/2-5
	// 			anchors.right : parent.right
	// 			anchors.top : parent.top
	// 			anchors.bottom : parent.bottom
	// 			color:"yellow"
	// 			// opacity: 0.3
	// 			Text{
	// 				id:hr
	// 				anchors.centerIn: parent
	// 				font.pixelSize: 30
	// 			}
	// 		}
	// 	}
	// 	header:Rectangle{
	// 		z:3
	// 		width:parent.width
	// 		height:50
	// 		color:"cyan"
	// 		Rectangle{

	// 			anchors.left : parent.left
	// 			anchors.top : parent.top
	// 			anchors.bottom : parent.bottom
	// 			width:parent.width/2-5
	// 			color:"green"
	// 			Text{
	// 				color:"blue"
	// 				anchors.centerIn: parent
	// 				font.pixelSize: 30
	// 				text:"姓名"
	// 			}
	// 		}


	// 		Rectangle{

	// 			anchors.right : parent.right
	// 			anchors.top : parent.top
	// 			anchors.bottom : parent.bottom
	// 			width:parent.width/2-5
	// 			color:"cyan"
	// 			Text{
	// 				anchors.centerIn: parent
	// 				font.pixelSize: 30
	// 				text: "money"
	// 			}
	// 		}
	// 	}
	// 	footer:Rectangle{
	// 		z:3
	// 		width:parent.width
	// 		height:50
	// 		color:"cyan"
	// 		Text {
	// 			anchors.centerIn: parent
	// 			id: name
	// 			font.pixelSize: 50
	// 			text: qsTr("text")

	// 		}


	// 	}
	// 	model:ListModel{
	// 		id:listmodel

	// 		ListElement{
	// 			name:"asd"
	// 			cost:"23"
	// 		}
	// 		ListElement{
	// 			name:"asd"
	// 			cost:"23"
	// 		}
	// 		ListElement{
	// 			name:"asd"
	// 			cost:"23"
	// 		}
	// 		ListElement{
	// 			name:"asd"
	// 			cost:"23"
	// 		}
	// 		ListElement{
	// 			name:"asd"
	// 			cost:"23"
	// 		}

	// 	}
	// 	delegate:Item{
	// 		function dy(hhh){
	// 			console.log("good"+" "+hhh)
	// 		}
	// 		width:listview.width
	// 		height:30
	// 		Rectangle{
	// 			id:left
	// 			anchors.left : parent.left
	// 			anchors.top : parent.top
	// 			anchors.bottom : parent.bottom
	// 			width:parent.width/2-5
	// 			color:"red"
	// 			Text{
	// 				color:"blue"
	// 				anchors.centerIn: parent
	// 				font.pixelSize: 30
	// 				text:model.name
	// 			}
	// 		}


	// 		Rectangle{
	// 			id:right
	// 			anchors.right : parent.right
	// 			anchors.top : parent.top
	// 			anchors.bottom : parent.bottom
	// 			width:parent.width/2-5
	// 			color:"red"
	// 			Text{
	// 				anchors.centerIn: parent
	// 				font.pixelSize: 30
	// 				text: model.cost
	// 			}
	// 		}
	// 		MouseArea{
	// 			anchors.fill:parent
	// 			hoverEnabled: true
	// 			onEntered:{
	// 				listview.currentIndex = index
	// 				listview.highlightItem.setText(name,cost)
	// 			}
	// 			onClicked: {
	// 				// decrementCurrentIndex()
	// 				listview.itemAtIndex(0).dy(listview.currentIndex)
	// 			}
	// 		}
	// 	}
	// }

	// 布局系统
	// Row{
	// 	layoutDirection: Qt.RightToLeft
	// 	spacing: 20
	// 	topPadding: 300
	// 	anchors.centerIn: parent
	// 	leftPadding: 200

	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"red"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"blue"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"cyan"
	// 	}

	// }

	// Column{

	// 	spacing: 20

	// 	anchors.centerIn: parent


	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"red"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"blue"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"cyan"
	// 	}

	// }

	// Grid{
	// 	layoutDirection: Qt.RightToLeft
	// 	columns: 2
	// 	rows: 3
	// 	flow:Grid.TopToBottom
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"red"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"cyan"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"cyan"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"red"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"orange"
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"pink"
	// 	}
	// }

	// RowLayout{
	// 	layoutDirection: Qt.RightToLeft
	// 	spacing: 20

	// 	anchors.fill: parent
	// 	Layout.preferredHeight: 30
	// 	Layout.preferredWidth: 30

	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"red"
	// 		Layout.minimumHeight: 100 // 最低高度
	// 		Layout.minimumWidth: 100 // 最低宽度
	// 		Layout.fillWidth: true  // 始终填满宽度
	// 		Layout.fillHeight: true // 始终填满高度
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"blue"
	// 		Layout.fillWidth: true
	// 		Layout.fillHeight: true
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"cyan"
	// 		Layout.fillWidth: true
	// 		Layout.fillHeight: true
	// 	}

	// }

	// GridLayout{
	// 	anchors.fill: parent
	// 	// Layout.preferredHeight: 30
	// 	// Layout.preferredWidth: 30
	// 	rows: 2
	// 	columns:2
	// 	// rowSpacing: 10
	// 	// columnSpacing: 10

	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"red"
	// 		// Layout.minimumHeight: 50// 最低高度
	// 		// Layout.minimumWidth: 50 // 最低宽度
	// 		// Layout.fillWidth: true  // 始终填满宽度
	// 		// Layout.fillHeight: true // 始终填满高度
	// 		Layout.alignment: Qt.AlignHCenter|Qt.AlignTop|Qt.AlignRight // 水平
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"blue"
	// 		// Layout.fillWidth: true
	// 		// Layout.fillHeight: true
	// 		Layout.alignment: Qt.AlignHCenter // 水平
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"cyan"
	// 		// Layout.fillWidth: true
	// 		// Layout.fillHeight: true
	// 		Layout.alignment: Qt.AlignHCenter // 水平
	// 	}
	// 	Rectangle{
	// 		width:50
	// 		height:50
	// 		color:"pink"
	// 		// Layout.fillWidth: true
	// 		// Layout.fillHeight: true
	// 		Layout.alignment: Qt.AlignHCenter // 水平
	// 	}
	// }





}





