import QtQuick 2.15
import QtQuick.Controls
import "../../BasicConfig"
import Qt5Compat.GraphicalEffects
Popup{
	id:popupLogin
	width:380
	height:450
	clip:true
	closePolicy: Popup.NoAutoClose
	modal:true
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
		anchors.fill:parent
		color:"#1b1b23"
		radius:10
		border.width:1
		border.color:"#75777f"


		Image{
			id:closeLoginImg
			source:"/Img/Resources/title/close.png"
			anchors.top:parent.top
			anchors.right:parent.right
			anchors.topMargin: 20
			anchors.rightMargin: 20
			scale:1.5
			layer.enabled: false
			layer.effect: ColorOverlay{
				source:closeLoginImg
				color:"yellow"
			}
			MouseArea{
				anchors.fill:parent
				hoverEnabled: true
				onEntered: {
					closeLoginImg.layer.enabled = true
				}
				onExited: {
					closeLoginImg.layer.enabled = false
				}
				onClicked: {
					popupLogin.close()
				}
			}
		}

		Label{
			id:loginText
			color:"#75757f"
			text:"扫码登录"
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.top:parent.top
			anchors.topMargin: 45
			font.bold:true
			font.family: "微软雅黑 Light"
			font.pixelSize: 25
		}

		Label{
			id:labelBehindCodeImg
			visible:codeImg.scale === 0.2 || codeImg.scale === 0.3
			y:codeImg.y+(codeImg.scale === 0.2?500:560)
			height:20
			anchors.horizontalCenter: codeImg.horizontalCenter
			width:codeImg.scale === 0.2 ? 200 :300
			wrapMode: Text.WrapAnywhere
			horizontalAlignment: Text.AlignHCenter
			textFormat: Text.RichText
			text:
			"
				<span style=\"font-size:15px;color:#75777f;font-family : '微软雅黑 Light';\">使用</span>
					<span style=\"font-size:18px;font-family:'微软雅黑 Light';color:#99ffff;\">
						<a href = \"https://github.com/\">大胖熊APP</a>
					</span>
				<span style=\"font-size:15px;color:#75777f;font-family:'微软雅黑 Light';\">扫码登陆</span>
			"
		}

		Image {
			id:pic
			x:-20
			y:55
			scale:0.6
			source: "/Img/Resources/mianPopups/ele_001.png"
		}
		Image {
			id:codeImg
			x:-140
			// x:-215
			y:-180
			// transformOrigin: Item.Center // 围绕中心缩放
			scale:0.2
			source: "/Img/Resources/mianPopups/qrcode.jpg"
			MouseArea{
				anchors.fill:parent
				hoverEnabled: true
				onEntered: {
					showAnimation.start()
					showAnimation.showFlag = true
				}
				onExited: {
					showAnimation.start()
					showAnimation.showFlag = false
				}
			}
		}

		Text{
			color:"#75777f"
			anchors.bottom:parent.bottom
			anchors.bottomMargin: 20
			anchors.horizontalCenter: parent.horizontalCenter
			text:"选择其他方式登录 >"
			font.pixelSize: 15
			font.family: BasicConfig.commFont
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
					popupLogin.close()
					otherLogin.open()
				}

			}
		}

		ParallelAnimation{
			id:showAnimation
			property bool showFlag:false

			NumberAnimation{
				target: codeImg
				property:"x"
				duration:500
				from :showAnimation.showFlag?-130:-215
				to :showAnimation.showFlag?-215:-130
			}

			NumberAnimation{
				target:codeImg
				property: "scale"
				duration:500
				from :showAnimation.showFlag?0.2:0.3
				to:showAnimation.showFlag?0.3:0.2
			}

			NumberAnimation{
				target:pic
				property:"x"
				duration: 500
				from :showAnimation.showFlag?-20:70
				to:showAnimation.showFlag?70:-20
			}

			NumberAnimation{
				target:pic
				property: "opacity"
				duration:500
				from :showAnimation.showFlag?1:0
				to:showAnimation.showFlag?0:1
			}
		}
	}

	Connections{
		target:BasicConfig
		function onOpenLoginPopup(){
			popupLogin.open()
		}
	}
}
