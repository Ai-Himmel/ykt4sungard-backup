#!/usr/bin/env python
# vim: encoding=cp936:

import sys, os, time, traceback, types,string

import wx                  # This module uses the new wx namespace
import wx.html
import z18demo

_menu_tree = (
    ['设置物理ID',0],
    ['初始化设备',1],
)
def opj(path):
    """Convert paths to the platform-specific separator"""
    str = apply(os.path.join, tuple(path.split('/')))
    # HACK: on Linux, a leading / gets lost...
    if path.startswith('/'):
        str = '/' + str
        return str

class OpenCOMDlg(wx.Dialog):
    def __init__(self,parent,title):
        wx.Dialog.__init__(self,parent,-1,title,size=(300,150))
        self.Center(wx.BOTH)

        sizer = wx.BoxSizer(wx.VERTICAL)

        label = wx.StaticText(self,-1,"选择串口")
        sizer.Add(label,-1,wx.ALIGN_CENTRE|wx.ALL,5)


        box = wx.BoxSizer(wx.HORIZONTAL)

        label = wx.StaticText(self,-1,"串口")
        box.Add(label,-1,wx.ALIGN_CENTRE|wx.ALL,5)

        self.comport = wx.ComboBox(self,-1,"COM1",size=(80,-1),style=wx.CB_DROPDOWN,
                             choices=['COM1','COM2','COM3','COM4','COM5'])
        box.Add(self.comport,-1,wx.ALIGN_CENTRE|wx.ALL,5)

        sizer.Add(box, 0, wx.GROW|wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5) 

        box = wx.BoxSizer(wx.HORIZONTAL)
        label = wx.StaticText(self,-1,"波特率")
        box.Add(label,-1,wx.ALIGN_CENTRE|wx.ALL,5)

        self.combaud = wx.ComboBox(self,-1,"57600",size=(80,-1),style=wx.CB_READONLY,
                             choices=['9600','19200','38400','57600','115200'])
        box.Add(self.combaud,-1,wx.ALIGN_CENTRE|wx.ALL,5)

        sizer.Add(box, 0, wx.GROW|wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5) 


        btnsizer = wx.StdDialogButtonSizer()

        btn = wx.Button(self,wx.ID_OK)
        btn.SetDefault()
        btnsizer.AddButton(btn)

        btn = wx.Button(self,wx.ID_CANCEL)
        btnsizer.AddButton(btn)
        btnsizer.Realize()

        sizer.Add(btnsizer,0,wx.ALIGN_RIGHT|wx.ALL,5)

        self.SetSizer(sizer)
        sizer.Fit(self)


class MainLog:
    def __init__(self,textctrl):
        self.text = textctrl

    def log(self,msg):
        self.text.AppendText(msg+'\n')


class MainNB(wx.Notebook):
    def __init__(self,parent,id=-1):
        wx.Notebook.__init__(self,parent,id,size=(21,21))

class MainFrame(wx.Frame):
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, -1, title, size = (640, 480),
                    style=wx.DEFAULT_FRAME_STYLE | wx.NO_FULL_REPAINT_ON_RESIZE)

        self.SetMinSize((640,480))
        self.log = None
        self.postest = z18demo.Z18POSTest()

        self.CreateStatusBar(1, wx.ST_SIZEGRIP)

        self.mainmenu = wx.MenuBar()
        menu = wx.Menu()

        item = menu.Append(101,"打开串口(&O)","打开读卡器串口")
        item.Enable(True)
        self.Bind(wx.EVT_MENU,self.OnOpenCom,item)
        self.Bind(wx.EVT_UPDATE_UI,self.OnUpdateUI,item)

        item = menu.Append(102,"关闭串口(&C)","关闭读卡器串口")
        item.Enable(False)
        self.Bind(wx.EVT_MENU,self.OnCloseCom,item)
        self.Bind(wx.EVT_UPDATE_UI,self.OnUpdateUI,id=101)

        

        menu.AppendSeparator()

        item = menu.Append(-1,"退出(&X)","退出程序")
        self.Bind(wx.EVT_MENU,self.OnFileClose,item)
        wx.App.SetMacExitMenuItemId(item.GetId())

        self.mainmenu.Append(menu, '文件(&F)')

        menu = wx.Menu()
        item = menu.Append(103,"关于(&A)","关于")
        self.Bind(wx.EVT_MENU,self.OnAbout,item)
        self.mainmenu.Append(menu, '关于(&A)')

        self.SetMenuBar(self.mainmenu)
        self.Center(wx.BOTH)

        splitter = wx.SplitterWindow(self,-1,
                               style=wx.CLIP_CHILDREN | wx.SP_LIVE_UPDATE | wx.SP_3D)

        self.nb = wx.Notebook(splitter)
        self.logtext = wx.TextCtrl(splitter, -1,
                             style = wx.TE_MULTILINE|wx.TE_READONLY|wx.HSCROLL)
        splitter.SplitHorizontally(self.nb,self.logtext, 300)
        splitter.SetMinimumPaneSize(40)

        self.log = MainLog(self.logtext)

        self.setupAllPanel(self.nb)

    def setupAllPanel(self,parent):
        # 设置参数界面
        panel = wx.Panel(parent)
        sizer = wx.BoxSizer(wx.VERTICAL)

        box = wx.BoxSizer(wx.HORIZONTAL)
        label = wx.StaticText(panel,-1,"设备物理ID")
        box.Add(label,-1,wx.ALIGN_CENTRE|wx.LEFT,5)

        edt = wx.TextCtrl(panel,-1,"",size=(80,-1))
        edt.SetMaxLength(8)
        edt.Bind(wx.EVT_CHAR,self.OnPhyIdEnter)
        self.edtPhyId= edt
        box.Add(edt,-1,wx.ALIGN_CENTRE|wx.ALL,5)

        sizer.Add(box,-1,wx.ALL|wx.ALIGN_TOP)

        btnsizer = wx.BoxSizer(wx.HORIZONTAL)
        btn = wx.Button(panel,-1,"设置物理ID")
        btnsizer.Add(btn,-1,wx.RIGHT|wx.ALIGN_RIGHT,5)

        self.Bind(wx.EVT_BUTTON,self.OnSetPhyId,btn)

        btn = wx.Button(panel,-1,"清空流水")
        btnsizer.Add(btn,-1,wx.RIGHT|wx.ALIGN_RIGHT,5)
        self.Bind(wx.EVT_BUTTON,self.OnClearSerial,btn)

        sizer.Add(btnsizer,-1,wx.ALL|wx.ALIGN_BOTTOM)
        panel.SetSizer(sizer)
        self.nb.AddPage(panel,_menu_tree[0][0])

        # demo 界面
        panel = wx.Panel(parent)
        sizer = wx.GridBagSizer(8,8)

        btn = wx.Button(panel,-1,"同步时钟")
        sizer.Add(btn,(1,1),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnSyncTimer,btn)

        btn = wx.Button(panel,-1,"设置消费参数")
        sizer.Add(btn,(1,4),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnSetConsumeParam,btn)

        btn = wx.Button(panel,-1,"设置卡权限")
        sizer.Add(btn,(3,1),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnSetCardRight,btn)

        btn = wx.Button(panel,-1,"采集流水")
        sizer.Add(btn,(3,4),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnCollSerial,btn)

        edt = wx.TextCtrl(panel,3001,"")
        sizer.Add(edt,(5,1),(1,6),flag=wx.EXPAND)
        btn = wx.Button(panel,-1,"设置欢迎信息")
        sizer.Add(btn,(6,1),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnSetWelcome,btn)
        
        edt = wx.TextCtrl(panel,3002,"")
        sizer.Add(edt,(6,4),(1,1),flag=wx.EXPAND)
        btn = wx.Button(panel,-1,"读取EEPROM")
        sizer.Add(btn,(6,5),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnReadEEPROM,btn)
        btn = wx.Button(panel,-1,"计算流水地址")
        sizer.Add(btn,(6,6,),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnCalcSerialAddr,btn)

        btn = wx.Button(panel,-1,"设置测试密钥")
        sizer.Add(btn,(8,1),(1,1))
        self.Bind(wx.EVT_BUTTON,self.OnSetWorkKey,btn)

        panel.SetSizer(sizer)
        self.nb.AddPage(panel,'  Demo  ')


    def showMsg(self,msg,flag=wx.OK|wx.ICON_INFORMATION):
        dlg = wx.MessageDialog(self, msg, 'z18pos', flag)
        r = dlg.ShowModal()
        dlg.Destroy()
        return r

    def OnSyncTimer(self,evt):
        self.log.log('同步时钟')
        self.postest.testSetTimer()

    def OnSetConsumeParam(self,evt):
        self.log.log('设置消费参数')
        self.postest.testConsumeParam()

    def OnSetCardRight(self,evt):
        self.log.log('设置卡权限')
        self.postest.testCardRight()

    def OnSetWorkKey(self,evt):
        self.log.log('设置测试密钥')
        self.postest.testSetWorkKey()

    def OnSetWelcome(self,evt):
        item = self.FindWindowById(3001)
        welcome = item.GetValue()
        if len(welcome) == 0 or len(welcome) > 16:
            self.showMsg('欢饮信息长度不正确')
            item.SetFocus()
            return

        self.log.log('设置欢迎信息 [%s] ' % welcome)
        self.postest.testSetWelcome(welcome)

    def OnCollSerial(self,evt):
        self.log.log('采集流水')
        self.postest.testCollectSerial()

    def OnSetPhyId(self,evt):
        phyid = self.edtPhyId.GetValue()
        if len(phyid) <> 8:
            self.showMsg('输入物理ID不正确')
            return

        if self.showMsg('是否要设置物理ID',wx.YES_NO|wx.ICON_INFORMATION|wx.NO_DEFAULT) == wx.ID_NO:
            return
        self.log.log('读取设备物理ID')
        self.postest.mytest()
        self.log.log('更新设备物理ID')
        self.postest.testPhyId(phyid)

    def OnUpdateUI(self,evt):
        menubar = self.GetMenuBar()
        item101 = menubar.FindItemById(101)
        item102 = menubar.FindItemById(102)
        item102.Enable(not item101.IsEnabled())
            

    def OnClearSerial(self,evt):
        if self.showMsg('是否要清除流水？',wx.YES_NO|wx.ICON_INFORMATION|wx.NO_DEFAULT) == wx.ID_NO:
            return
        self.log.log('清除流水')
        self.postest.testClearSerial()

    def OnPhyIdEnter(self,evt):
        key = evt.GetKeyCode()

        if chr(key) in string.digits or \
            (key >= ord('A') and key <= ord('F')):
            evt.Skip()
        elif key >= ord('a') and key <= ord('f'):
            evt.m_keyCode=key-0x20
            evt.Skip()
        elif key >= 0x21 and key <=0x7E :
            return
        else: evt.Skip()

    def OnOpenCom(self, evt):
        dlg = OpenCOMDlg(self,'打开串口')
        if dlg.ShowModal() == wx.ID_CANCEL:
            return

        self.comport = dlg.comport.GetValue()
        self.combaud = dlg.combaud.GetValue()
        port = int(self.comport[-1:],10)
        port -= 1
        baud = int(self.combaud,10)
        print '%d:%d' % (port,baud)
        if not self.postest.open(port,baud):
            self.log.log('打开串口失败')
            self.showMsg('打开串口失败')
        else:
            self.log.log('打开串口成功')
            self.showMsg('打开串口成功')
            self.GetMenuBar().FindItemById(101).Enable(False)



    def OnCloseCom(self, evt):
        self.postest.close()
        self.log.log('关闭串口')
        self.GetMenuBar().FindItemById(101).Enable(True)

    def OnFileClose(self, evt):
        self.Close()

    def OnSelChanged(self,evt):
        item = evt.GetItem()
        itemText = self.tree.GetItemText(item)
        self.loadpanel(itemText)
        
    def OnCalcSerialAddr(self,evt):
        dlg = wx.TextEntryDialog(self, '输入流水号?','z18tool', 'z18tool')
        dlg.SetValue("1")

        if dlg.ShowModal() == wx.ID_OK:
            serial = int(dlg.GetValue())
            addr = serial * 64 + 0x030EC0
            item = self.FindWindowById(3002)
            v = "%X" % addr
            item.SetValue(v)
        dlg.Destroy()
        
    def OnReadEEPROM(self,evt):
        item = self.FindWindowById(3002)
        addr = int(item.GetValue(),16)
        data = self.postest.testReadEEPROM(addr,64)
        self.log.log('读取地址[%X]' % addr)
        self.log.log(data)
        

    def OnAbout(self,evt):
        self.showMsg('Sungard一卡通')

class MyApp(wx.App):
    def OnInit(self):
        """
        Create and show the splash screen.  It will then create and show
        the main frame when it is time to do so.
        """

        wx.SystemOptions.SetOptionInt("mac.window-plain-transition", 1)

        # For debugging
        #self.SetAssertMode(wx.PYAPP_ASSERT_DIALOG)

        # Normally when using a SplashScreen you would create it, show
        # it and then continue on with the applicaiton's
        # initialization, finally creating and showing the main
        # application window(s).  In this case we have nothing else to
        # do so we'll delay showing the main frame until later (see
        # ShowMain above) so the users can see the SplashScreen effect.        
        dlg = MainFrame(None,"z18车载机工具 v1.1")
        dlg.Show()

        return True



#---------------------------------------------------------------------------

def main():
    try:
        demoPath = os.path.dirname(__file__)
        os.chdir(demoPath)
    except:
        pass
    app = MyApp(False)
    app.MainLoop()

if __name__ == '__main__':
    __name__ = 'Main'
    main()
