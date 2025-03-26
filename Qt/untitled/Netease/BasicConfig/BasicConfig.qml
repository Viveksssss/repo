pragma Singleton
import QtQuick 2.15

QtObject{
	signal blankAreaClicked()
	signal openLoginPopup()
	readonly property string commFont:"微软雅黑 Light"
	readonly property string textFieldFont:"#d9d9da"
	readonly property string defaultFontNormalColor:"#a1a1a3"
	readonly property string fieldBgColor:"#222"
	readonly property string fieldBgBordColor:"#303037"
}
