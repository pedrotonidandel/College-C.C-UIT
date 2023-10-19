FileEncoding, UTF-8


Gui, Margin, 1, 1
Gui, Add, Edit, x20 y65 w300 vText1, Digite o texto aqui
Gui, Add, Edit, vText2 w300, Digite o texto aqui
Gui, Add, Edit, vText3 w300, Digite o texto aqui
Gui, Add, Edit, vText4 w300, Digite o texto aqui
Gui, Add, Edit, vText5 w300, Digite o texto aqui
Gui, Add, Edit, vText6 w300, Digite o texto aqui


Gui, Add, Button, x124 w100 Default, Ativar
Gui, Add, Button, x300 w100 y5, Como Utilizar
Gui, Add, Button, x300 w100 y27, Feedback
GuiControl,, Edit1, Digite o texto aqui
GuiControl,, Edit2, Digite o texto aqui
GuiControl,, Edit3, Digite o texto aqui
GuiControl,, Edit4, Digite o texto aqui
GuiControl,, Edit5, Digite o texto aqui
GuiControl,, Edit6, Digite o texto aqui
Gui, Show, w400 h225, Mapeador de Teclas - Hi Platform
Gui, Add, Picture, x10 y10 w400 h225, background.png

ButtonAtivar:
Gui, Submit, NoHide
text1 := Text1
text2 := Text2
text3 := Text3
text4 := Text4
text5 := Text5
text6 := Text6
if (text1 = "" or text2 = "" or text3 = "" or text4 = "" or text5 = "" or text6 = "")
return
Hotkey, F1, writeText1, On
Hotkey, F2, writeText2, On
Hotkey, F3, writeText3, On
Hotkey, F4, writeText4, On
Hotkey, F5, writeText5, On
Hotkey, F6, writeText6, On
return

ButtonComoUtilizar:
MsgBox, Para usar o mapeador de teclas, você precisa definir o texto que será digitado quando a tecla F1, F2, F3, F4, F5 ou F6 for pressionada. Clique no botão "Ativar" para habilitar o mapeamento de teclas. Ao fechar a janela, as teclas voltam ao normal.
Return

ButtonFeedback:
Run, % "https://forms.gle/UDSUS5oHoJf8X2kz6"
Return

writeText1:
send, % text1
return

writeText2:
send, % text2
return

writeText3:
send, % text3
return

writeText4:
send, % text4
return

writeText5:
send, % text5
return

writeText6:
send, % text6
return

GuiClose:
ExitApp
return

F1::
KeyInput1 := A_ThisHotkey
GuiControl,, KeyInput1, % KeyInput1
return

F2::
KeyInput2 := A_ThisHotkey
GuiControl,, KeyInput2, % KeyInput2
return
F3::
KeyInput3 := A_ThisHotkey
GuiControl,, KeyInput3, % KeyInput3
return
F4::
KeyInput4 := A_ThisHotkey
GuiControl,, KeyInput4, % KeyInput4
return
F5::
KeyInput5 := A_ThisHotkey
GuiControl,, KeyInput5, % KeyInput5
return
F6::
KeyInput6 := A_ThisHotkey
GuiControl,, KeyInput6, % KeyInput6
return