import QtQuick 2.15
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import QtQuick
import "../../BasicConfig"
Popup{
	id:otherLogin
	width: 380
	height: 450
	clip:true
	closePolicy: Popup.NoAutoClose
	modal:true
	anchors.centerIn: parent
	Overlay.modal: Rectangle {
	    color: "#2575757f" // 半透明黑色
	}
	enter: Transition {
	    NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 500 }
	}

	// 退出动画
	exit: Transition {
	    NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 500 }
	}


	background: Rectangle{
		id: rectangle
		anchors.fill:parent
		color:"#1b1b23"
		radius:10
		border.width:1
		border.color:"#75777f"


		Image{
			id:closeLoginImg2
			source:"/Img/Resources/title/close.png"
			anchors.top:parent.top
			anchors.right:parent.right
			anchors.topMargin: 20
			anchors.rightMargin: 20
			scale:1.5
			layer.enabled: false
			layer.effect: ColorOverlay{
				source:closeLoginImg2
				color:"yellow"
			}
			MouseArea{
				anchors.fill:parent
				hoverEnabled: true
				onEntered: {
					closeLoginImg2.layer.enabled = true
				}
				onExited: {
					closeLoginImg2.layer.enabled = false
				}
				onClicked: {
					otherLogin.close()
				}
			}
		}


		Image {
			id:codeImg2
			x:-365
			y:-370
			scale:0.1
			source: "/Img/Resources/mianPopups/qrcode.jpg"
			MouseArea{
				anchors.left : parent.left
				anchors.top:parent.top
				height:400
				width:400
				hoverEnabled: true
				onEntered: {
					cursorShape = Qt.PointingHandCursor
				}
				onExited: {
					cursorShape = Qt.ArrowCursor
				}
				onClicked:{
						otherLogin.close()
						popupLogin.open()
				}


				states: [
					State{
						id:defaultState

					},
					State{
						id:afterState
					}
				]
			}
		}

		Row{
			id:titleRow
			anchors.left: parent.left
			anchors.right: parent.right
			spacing: 3	
			anchors.top:parent.top
			anchors.topMargin: 70
			anchors.leftMargin:100

			Image {
				// scale:0.7
				source: "/Img/Resources/title/logo.png"
			}
			Label{
				id:loginText
				color:"white"
				text:"大胖熊音乐"
				anchors.verticalCenter: parent.verticalCenter
				z:2
				font.family: BasicConfig.commFont
				font.pixelSize: 23
			}
		}
		Canvas{
			id:canvass
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			onPaint: {
				let ctx =	canvass.getContext("2d")
				ctx.beginPath()
				ctx.moveTo(90,1)
				ctx.lineTo(1,90)
				ctx.lineTo(90,90)
				ctx.lineTo(90,1)

				ctx.fillStyle = "#1b1b23"
				ctx.fill()
			}
		}


		Column{
			id:loginColumns
			anchors.top:titleRow.bottom
			anchors.topMargin: 40
			anchors.horizontalCenter: parent.horizontalCenter
			TextField{
				id:telNumberText
				width:300
				height:35
				anchors.horizontalCenter: parent.horizontalCenter
				color:BasicConfig.textFieldFont
				topPadding: 7
				placeholderText: "请输入手机号"
				placeholderTextColor: BasicConfig.defaultFontNormalColor
				font.pixelSize: 17
				font.family: BasicConfig.commFont
				leftPadding:80
				verticalAlignment: Text.AlignVCenter

				background: Rectangle{ // 外部举行
					radius: 5
					anchors.fill:parent
					anchors.verticalCenter: parent.verticalAlignment
					color:BasicConfig.fieldBgColor
					border.width:1
					width:telNumberText.leftPadding
					border.color: telNumberText.focus?BasicConfig.fieldBgColor:BasicConfig.fieldBgBordColor
					anchors.leftMargin: 10
					Item{

						width:400
						height:40
						id:countryTelItem
						// color:"transparent"
						anchors.top:parent.top
						anchors.bottom:parent.bottom
						anchors.leftMargin: 10
						Row{
							id:telAndArrowRow
							anchors.verticalCenter: parent.verticalCenter
							anchors.top:parent
							width:200
							x:10
							spacing:14
							Label{
								id:countryTelNumtext
								text:"+86"
								color:"white"
								font.pixelSize: 17
								font.family: BasicConfig.commFont
								anchors.verticalCenter: parent.verticalCenter
							}
							Label{
								id:arrowLabel
								text:">"
								color:"white"
								font.pixelSize: 17
								height:20
								width:20
								anchors.verticalCenter: parent.verticalCenter
							}

						}
						MouseArea{
							x: -27
							y: 50
							anchors.fill: telAndArrowRow
							hoverEnabled: true
							height:48
							width:67
							z:1000
							enabled: true
							propagateComposedEvents: true // 允许事件传递
							onClicked: {
								telDatePopup.open()
							}
						}
					}
					Popup{
						id:telDatePopup
						width:295
						height:200
						y:40
						background:Rectangle{
							color:"#2d2d37"
							radius:10
						}
					}
				}
			}
		}
	}

}
