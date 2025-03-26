import QtQuick 2.15
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import "../Info"
import "../../BasicConfig"
Row{
	id:infoTitle
	spacing:10
	anchors.rightMargin:10
	anchors.right : miniRow.left
	anchors.verticalCenter: parent.verticalCenter
	// 登录组
	Item{
		height:30
		width:140
		anchors.verticalCenter: parent.verticalCenter
		Row{
			anchors.verticalCenter: parent.verticalCenter
			spacing:8
			Rectangle{
				id:userRectangle
				width:25
				height:width
				radius:width/2
				color:"#2d2d37"



				Image{
					id:userImg
					source:"/Img/Resources/title/user.png"
					anchors.verticalCenter: parent.verticalCenter
					anchors.centerIn: parent
					scale:0.68

					layer.enabled:false
					layer.effect: ColorOverlay{
						color:"cyan"
						source:userImg
					}

					MouseArea{
						hoverEnabled: true
						anchors.fill:parent
						onEntered: {
							userImg.layer.enabled = true
						}
						onExited: {
							userImg.layer.enabled = false
						}
					}
				}

				// 未登录文本
				Text{
					id:loginStatus
					text:"未登录"
					color:"#75777f"
					font.pixelSize: 14
					font.family: BasicConfig.commFont
					anchors.left :userImg.right
					anchors.verticalCenter: userRectangle.verticalCenter
					MouseArea{
						anchors.fill:parent
						hoverEnabled: true
						onEntered: {
							loginStatus.color = "cyan"
						}
						onExited: {
							loginStatus.color = "#75777f"
						}
						onClicked: {
							BasicConfig.openLoginPopup()
						}
					}
				}
				// 会员表示
				Item{
					anchors.leftMargin: 10
					id:vip
					height:userImg.height
					width:loginStatus.implicitWidth*1.2
					anchors.verticalCenter: parent.verticalCenter
					anchors.left:loginStatus.right
					Rectangle{
						id:vipRectangle
						width:parent.width
						height:12
						color:"#dadada"
						anchors.left : parent.left
						anchors.verticalCenter: parent.verticalCenter
						radius:height/2

						Label{
							text:"vip开通"
							anchors.left : parent.left
							anchors.leftMargin: parent.radius
							color:"#f8f9f9"
							font.pixelSize: parent.height/2+2
							font.family: BasicConfig.commFont
							anchors.verticalCenter: parent.verticalCenter
						}
					}

					Rectangle{
						id:bgBorderRect
						width:vipRectangle.height+4
						height:width
						radius:width/2
						color:"#dadada"
						anchors.verticalCenter: parent.verticalCenter
						border.color:"#13131a"
						border.width:1
					}

				}


			}
		}
	}
	// 登录下按
	Image {
		id: loginImg
		anchors.verticalCenter: parent.verticalCenter
		source:"/Img/Resources/title/arrow.png"
		rotation:-90
		layer.enabled: false
		layer.effect: ColorOverlay{
			source:loginImg
			color:"yellow"
		}
		MouseArea{
			anchors.fill:parent
			hoverEnabled:true
			onEntered: {
				loginImg.layer.enabled = true
			}
			onExited: {
				loginImg.layer.enabled = false
			}
		}
	}
	// 消息重心
	Image {
		id: messageImg
		anchors.verticalCenter: parent.verticalCenter
		source:"/Img/Resources/title/message.png"
		scale:0.8
		layer.enabled: false
		layer.effect: ColorOverlay{
			source:messageImg
			color:"yellow"
		}
		MouseArea{
			anchors.fill:parent
			hoverEnabled:true
			onEntered: {
				parent.layer.enabled = true
			}
			onExited: {
				parent.layer.enabled = false
			}
		}
	}
	// 设置
	Image {
		id: settingImg
		anchors.verticalCenter: parent.verticalCenter
		source:"/Img/Resources/title/setting.png"
		scale:0.8
		layer.enabled: false
		layer.effect: ColorOverlay{
			source:settingImg
			color:"yellow"
		}
		MouseArea{
			anchors.fill:parent
			hoverEnabled:true
			onEntered: {
				parent.layer.enabled = true
			}
			onExited: {
				parent.layer.enabled = false
			}
			onClicked: {
				mainStackView.push("/RightPage/Info/StackPages/Settings.qml")
			}
		}
	}
	// 换肤
	Image {
		id: skinImg
		anchors.verticalCenter: parent.verticalCenter
		source:"/Img/Resources/title/skin.png"
		scale:0.7
		layer.enabled: false
		layer.effect: ColorOverlay{
			source:skinImg
			color:"yellow"
		}
		MouseArea{
			anchors.fill:parent
			hoverEnabled:true
			onEntered: {
				parent.layer.enabled = true
			}
			onExited: {
				parent.layer.enabled = false
			}
		}
	}
	// 分割线
	Rectangle{
		height:24
		width:1
		color:"#2d2d37"
		anchors.verticalCenter: parent.verticalCenter
		anchors.left:skinImg
		anchors.leftMargin: 10
	}



}
