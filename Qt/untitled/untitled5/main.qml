import QtQuick 2.12
import QtQuick.Window 2.12

Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("Hello World")

	// Rectangle{
	// 	objectName:"rec"
	// 	width:538
	// 	height:300
	// 	anchors.centerIn: parent
	// 	color:"red"
	// 	anchors.verticalCenterOffset: 46
	// 	anchors.horizontalCenterOffset: 0
	// 	Text{
	// 		width: 262
	// 		height: 260
	// 		anchors.centerIn: parent
	// 		font.pixelSize: 50
	// 		anchors.verticalCenterOffset: 212
	// 		anchors.horizontalCenterOffset: 0
	// 		text:test.pro1
	// 	}
	// }
	// Test{
	// 	id:test
	// 	Component.onCompleted: {
	// 		test.pro1 = text.getPro2();
	// 	}
	// }
	// signal sig()
	// function func(arg){
	// 	console.log("arg is",arg)
	// }
	// onSig:{
	// 	console.log("function sig")
	// }

	Timer{
		running:true
		interval:1
		repeat:true
		onTriggered: {
			worker.sendMessage({model:listModel,val:20})
			// for(let i = 0;i<listModel.count;i++){
			// 	let data = listModel.get(i)
			// 	listModel.set(i,{val1:data.val1+0.1,val2:data.val2+0.2})
			// }

		}
	}

	WorkerScript{ // 多线程异步处理
		id:worker
		source:"qrc:/worker.js"
		onMessage: {
			console.log(messageObject,typeof(messageObject))
		}
	}

	ListModel{
		id:listModel
		Component.onCompleted: {
			for(let i = 0;i<10000;i++){
				listModel.append({val1:0.001,val2:0.002})
			}
		}
	}

	ListView{
		id:listView
		model:listModel
		anchors.fill:parent
		delegate: Rectangle{
			width:0
			height:40
			color:"white"
			border.width:1
			border.color:"yellow"
			Row{
				spacing: 10
				layoutDirection: Qt.RightToLeft
				Item{
					width:listView.width/2
					height:40

					Text{
						color: "cyan"
						text:val1
						anchors.fill:parent
					}
				}
				Item{
					width:listView.width/2
					height:40

					Text{
						text:val2
						anchors.fill:parent
					}
				}
			}

		}
	}

}
