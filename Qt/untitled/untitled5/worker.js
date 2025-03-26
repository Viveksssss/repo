WorkerScript.onMessage = function func(msg) {
	let listModel = msg.model
	for(let i = 0;i<listModel.count;i++){
		let data = listModel.get(i)
		listModel.set(i,{val1:data.val1+0.1,val2:data.val2+msg.val})
	}
	WorkerScript.sendMessage("nihao")
	listModel.sync() // 同步更新
}
