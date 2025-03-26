import QtQuick 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Basic
import QtQuick.Controls
import QtQuick.Dialogs
import "../../BasicConfig"
Row{
	id:searchRow
	property alias innerRect: innerRectangle
	spacing: 20
	width:300
	// 返回
	Rectangle{
		id:backForwardRect
		width:24
		height:27
		color:"transparent"
		border.width:1
		border.color:"#2b2b31"
		radius:3
		anchors.verticalCenter: parent.verticalCenter
		Image{
			id:backImg
			source:"/Img/Resources/title/arrow.png"
			anchors.centerIn: parent
			layer.enabled: false
			layer.effect:ColorOverlay {
				color:"yellow"
				source:backImg
			}
			MouseArea{
				anchors.fill:parent
				hoverEnabled: true
				onEntered: {
					parent.layer.enabled = true
				}
				onExited:{
					parent.layer.enabled = false
				}
			}
		}
	}
	// 搜索框
	TextField{
		Connections{
			target:BasicConfig
			function onBlankAreaClicked(){
				innerRect.gradientPosition = 1;
			}
		}
		id:searchInput
		focus:true // 必要设置，防止焦点被鼠标事件拦截
		width:140
		height:25
		anchors.left:backForwardRect.right
		anchors.leftMargin: 15
		anchors.verticalCenter: parent.verticalCenter
		color:"red"
		topPadding: 6
		placeholderText:"断桥残雪"
		font.pixelSize: 12
		font.family: "微软雅黑 Light"
		leftPadding:35



		background: Rectangle{ // 外部举行
			// z:1 // 防止被覆盖
			radius: 5
			anchors.fill:parent
			gradient: Gradient{
				orientation: Gradient.Horizontal
				GradientStop{color:"#21283d";position:0}
				GradientStop{color:"#382635";position:1}
			}
			Rectangle{ // 内部举行
				id:innerRectangle
				anchors.fill:parent
				anchors.margins: 1
				property real gradientPosition:1
				gradient: Gradient{
					orientation: Gradient.Horizontal
					GradientStop{color:"#1a1d29";position:0}
					GradientStop{color:"#241c26";position:innerRectangle.gradientPosition}
				}
			}
			Image{
				id:searchIcon
				source:"/Img/Resources/title/search.png"
				anchors.verticalCenter: parent.verticalCenter
				anchors.left:parent.left
				anchors.margins: 3
				scale:0.6
				MouseArea{
					anchors.fill:searchIcon
					onClicked:{
						singModel.insert(0,{singName:searchInput.text});
					}
				}
			}
		}
		MouseArea{
			acceptedButtons: Qt.LeftButton
			anchors.fill:parent
			propagateComposedEvents: true
			onClicked:(mouse)=>{
				if (!searchIcon.contains(mapToItem(searchIcon, mouse.x, mouse.y))) {
					innerRectangle.gradientPosition = 0
					searchPop.open()
				}else
					mouse.accepted = false // 放行事件到下层
			}

		}
		Keys.onPressed:(event)=>{
			if(event.key===Qt.Key_Return||event.key ===Qt.Key_Enter){
				singModel.insert(0,{singName:searchInput.text});
			}
		}

	}
	// 弹出框
	Popup{
		clip:true
		id:searchPop
		width:300
		height:500
		visible: false
		y:25
		x:-20
		closePolicy:Popup.CloseOnPressOutsideParent
		background:Rectangle{
			color:"#1a1a21"
			anchors.fill:parent
			width:parent.width
			height:parent.height
			radius:5
			Flickable{
				z:20
				focus:true
				anchors.fill:parent
				contentHeight: 1000
				ScrollBar.vertical: ScrollBar{
					anchors.right:parent.right
					anchors.rightMargin: 5
					width:10
					contentItem: Rectangle{
						visible: parent.active
						implicitWidth: 10
						radius:4
						color:"#42424b"
					}
				}
				Column{
					anchors.fill:parent
					spacing:20
					anchors.right:parent.right
					// 历史记录+内容
					Item{
						id:historyAndFlowItem
						anchors.left:parent.left
						anchors.right:parent.right
						height:historyItem.implicitHeight+singFlow.implicitHeight
						// 历史记录
						Item{
							id:historyItem
							anchors.left:parent.left
							anchors.right:parent.right
							anchors.top:parent.top
							anchors.topMargin: 15
							anchors.leftMargin: 17
							height:20
							Label{
								id:historyLabel
								color:"#7f7f85"
								text:"搜索历史"
								font.pixelSize: 15
								font.family: BasicConfig.commFont
							}
							Image{
								id:deleteImg
								source:"/Resources/searchBox/remove.png"
								scale:0.6
								anchors.right:parent.right
								anchors.rightMargin: 20
								anchors.verticalCenter: historyLabel.verticalCenter
								layer.enabled: false
								layer.effect:ColorOverlay {
									source:deleteImg
									color:"yellow"
								}
								MouseArea{
									anchors.fill: parent
									hoverEnabled: true;
									onEntered: {
										deleteImg.layer.enabled = true
									}
									onExited: {
										deleteImg.layer.enabled = false
									}
									onClicked: {
										singModel.clear()
									}
								}
							}
						}
						// 历史
						Flow{
							// 内容
							id:singFlow
							anchors.top:historyItem.bottom
							anchors.left:historyItem.left
							anchors.right:parent.right
							anchors.rightMargin: 10
							anchors.topMargin: 20
							spacing: 10
							Repeater{
								id:historyRepeater
								anchors.fill:parent
								model:singModel
								property bool isShow: false
								delegate: Rectangle{
									radius:3
									width:dataLabel.implicitWidth+20
									height:27
									border.width:1
									border.color:"#454546"
									color:"#2d2d37"
									visible:index<(historyRepeater.isShow?14:8)

									Label{
										id:dataLabel
										property int lastIndex:13
										text:index===7&&(historyRepeater.isShow===false)?">":
										(index===lastIndex&&(historyRepeater.isShow)?">":modelData) // 模型只有一个数据时候，直接使用modelData即可
										rotation:index===7&&historyRepeater.isShow==false?90:(index === lastIndex&&historyRepeater.isShow?-90:0)
										font.pixelSize: 15
										height:20
										anchors.centerIn: parent
										color:"#ddd"
										font.family: BasicConfig.commFont
									}
									MouseArea{
										hoverEnabled: true
										anchors.fill: parent
										onEntered: {
											dataLabel.color="white"
											parent.color = "#393943"
											cursorShape = Qt.PointingHandCursor
										}
										onExited: {
											dataLabel.color="#ddd"
											parent.color = "#2d2d37"
											cursorShape = Qt.ArrowCursor
										}
										onClicked: {
											if(historyRepeater.isShow && index === dataLabel.lastIndex){
												historyRepeater.isShow = false
											}
											else if(historyRepeater.isShow == false&&index ===7){
												historyRepeater.isShow = true
											}else{
												searchInput.text = singName
												searchPop.close()
											}

										}
									}
								}
							}
						}
					}
					// 热搜榜
					Item{
						id:singList
						anchors.left:parent.left
						anchors.right:parent.right
						height: childrenRect.height
						Label{
							id:hotSingLabel
							color:"#7f7f85"
							text:"热搜榜"
							height:deleteImg.implicitHeight
							anchors.left:parent.left
							anchors.leftMargin: 17
							anchors.top:parent.top
							anchors.topMargin: 50
							font.pixelSize: 18
							font.family: BasicConfig.commFont
						}
						Column{
							anchors.top:hotSingLabel.bottom
							anchors.left:parent.left
							anchors.right:parent.right
							anchors.bottom:parent.bottom

							Repeater{
								id:hotSingRepeater
								model:hotSingModel
								delegate: Rectangle{
									radius:5
									color:"transparent"
									height:40
									width:singFlow.implicitWidth
									Label{
										id:hotSingIndexLabel
										color:index<3?"#eb4d44":"#818187"
										text:String(index+1)
										anchors.left:parent.left
										anchors.leftMargin: 30
										anchors.verticalCenter: parent.verticalCenter
										font.pixelSize: 15
										font.family: BasicConfig.commFont
									}
									Label{
										id:hotSingNameLabel
										color:"#ddd"
										text:singName
										anchors.left:hotSingIndexLabel.right
										anchors.leftMargin: 30
										anchors.verticalCenter: parent.verticalCenter
										font.pixelSize: 18
										font.family: BasicConfig.commFont
									}
									MouseArea{
										hoverEnabled: true
										anchors.fill:parent
										onEntered: {
											parent.color = "#393943"
											cursorShape = Qt.PointingHandCursor
										}
										onExited: {
											parent.color = "transparent"
											cursorShape = Qt.ArrowCursor
										}
										onClicked: {
											searchInput.text = singName
											searchPop.close()
										}
									}
								}
							}
						}
					}
				}
			}
			// 历史记录模型
			ListModel{
				id:singModel
				ListElement{singName:"想象之中"}
				ListElement{singName:"幻听"}
				ListElement{singName:"拆东墙"}
				ListElement{singName:"大千世界"}
				ListElement{singName:"你若化成风"}
				ListElement{singName:"素颜"}
				ListElement{singName:"灰色头像"}
				ListElement{singName:"断桥残雪"}
				ListElement{singName:"诲人不倦"}
				ListElement{singName:"如约而至"}
				ListElement{singName:"科幻"}
				ListElement{singName:"有何不可"}
				ListElement{singName:"玫瑰花的葬礼"}
				ListElement{singName:"庐州月"}
				ListElement{singName:"清明雨上"}
			}

			// 热搜榜模型
			ListModel{
				id:hotSingModel
				ListElement{singName:"想象之中"}
				ListElement{singName:"幻听"}
				ListElement{singName:"拆东墙"}
				ListElement{singName:"大千世界"}
				ListElement{singName:"你若化成风"}
				ListElement{singName:"素颜"}
				ListElement{singName:"灰色头像"}
				ListElement{singName:"断桥残雪"}
				ListElement{singName:"诲人不倦"}
				ListElement{singName:"如约而至"}
				ListElement{singName:"科幻"}
				ListElement{singName:"有何不可"}
				ListElement{singName:"玫瑰花的葬礼"}
				ListElement{singName:"庐州月"}
				ListElement{singName:"清明雨上"}
			}

	}



	}
	// 语音
	Rectangle{
		id:audioRect
		height:26
		width:height
		// color:"#241c26"
		color:"transparent"
		anchors.left:searchInput.right
		anchors.leftMargin: 10
		anchors.verticalCenter: parent.verticalCenter
		Image{
			id:audioImg
			source:"/Img/Resources/title/record.png"
			anchors.centerIn: parent
			layer.enabled: false
			layer.effect: ColorOverlay{
				color:"yellow"
				source:"audioRect"
			}

			MouseArea{
				anchors.fill:parent
				hoverEnabled: true
				onEntered: {
					audioImg.layer.enabled = true
				}
				onExited: {
					audioImg.layer.enabled = false
				}
			}
		}
	}

}
