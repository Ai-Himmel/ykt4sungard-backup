<%@ page pageEncoding="GBK"%>
<%@ page import="java.util.Map" %>
<%@ page import="org.king.schedulemanage.domain.Classschedulemodel" %>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<title>复旦大学迎新工作管理信息系统</title>
		<meta http-equiv="Content-Type" content="text/html;">


		<SCRIPT language=javascript>
function on_validate(){
	document.all("classSchedulemanage.fromtime").value=document.all("stime").getTime();
	document.all("classSchedulemanage.titime").value=document.all("etime").getTime();
	var fromTiHour=parseInt(document.all("stime").getTime().substring(0,2),10);
	var fromTiMini=parseInt(document.all("stime").getTime().substring(3,5),10);
	var toTiHour=parseInt(document.all("etime").getTime().substring(0,2),10);
	var toTiMini=parseInt(document.all("etime").getTime().substring(3,5),10);
	
	var fromtime = parseInt(document.all("stime").getTime().substring(0,2) + document.all("stime").getTime().substring(3,5),10);

	var totime = parseInt(document.all("etime").getTime().substring(0,2) + document.all("etime").getTime().substring(3,5),10);

	var cft = parseInt(document.all("schedulemanage.fromtime").value,10);

	var ctt = parseInt(document.all("schedulemanage.totime").value,10);

	
	if(document.all("classSchedulemanage.fromtime").value == ''){
		alert('请选择起始时间');			
		return false;
	}else if(document.all("classSchedulemanage.positon").value == ''){
		alert('请输入地点');				
		return false;
	}else if(document.all("classSchedulemanage.mission").value == ''){
		alert('请输入任务');			
		return false;		
	}else if(document.all("classSchedulemanage.titime").value == ''){
		alert('请选择结束时间');	
		return false;
	}else if(document.all("classSchedulemanage.classId").value == ''){
		alert('请选择班级');	
		return false;
	}else if(document.all("classSchedulemanage.mission").value.length > 200){
		alert('"任务"描述最多不能超过200字');
		return false;
	}else if(!(fromtime >= cft && totime <= ctt)){
			alert('班级日程安排时间应介于书院日程安排时间');
			return false;
	}else if(fromtime >= totime){
			alert('日程安排起始时间应小于日程结束时间');
			return false;
	}
	else{
	   return true;}
}

function on_FD(){
	document.all("sd").click();
}
function on_TD(){
	document.all("ed").click();
}



</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<%String collegeId = request.getParameter("collegeId");%>
		<html:form method="post" action="scheduleAction.do?method=classSplitSave" onsubmit="javascript:return on_validate();">
			<html:hidden property="schedulemanage.collegeId" value="<%=collegeId%>" />
			<html:hidden property="schedulemanage.scheduleId" />
			<html:hidden property="classSchedulemanage.scheduleId" />
			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium">书院日程安排分拆</font></strong>
					</td>
				</tr>
				<tr>
					<td height="20" align="center" valign="top">
						&nbsp;
					</td>
				</tr>
				<tr>
					<td align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							<tbody>
								<tr align="center" valign=middle>
									<td width="15%" height="28" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										日期
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<c:out value="${date}" />
									</td>
									<td height="28" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										班级
									</td>
									<td colspan="3" align="left" valign="middle" class="tableHeader3">
										<html:select property="classSchedulemanage.classId" styleClass="select01">
											<option value=''>
												请选择班级
											</option>
											<option value='all' <logic:equal name="scheduleForm" property="classSchedulemanage.classId" value="all">selected</logic:equal>>
												该书院所有班级
											</option>
											<html:options collection="classes" property="classId" labelProperty="classNo" />
										</html:select>
									</td>
								</tr>
								<tr align="center" valign=middle>
									<td height="28" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">书院安排起始时间</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<c:out value="${fromtime}" />
										<html:hidden property="schedulemanage.fromtime" />
									</td>
									<td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">书院安排结束时间</span>
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<c:out value="${totime}" />
										<html:hidden property="schedulemanage.totime" />
									</td>
								</tr>
								<tr align="center" valign=middle>
									<td height="28" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">班级安排起始时间</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr>

												<html:hidden property="classSchedulemanage.fromtime" />

												<td width="130">
													<OBJECT id="stime" class="TxtInput" border="1" style="HEIGHT: 16; WIDTH: 120;" tabIndex="4" type="text/x-scriptlet" VIEWASTEXT>
														<PARAM NAME="URL"
															VALUE="timesetup.do?timeStr=<logic:present name="scheduleForm" property="classSchedulemanage.fromtime"><bean:write name="scheduleForm" property="classSchedulemanage.fromtime"/></logic:present><logic:notPresent name="scheduleForm" property="classSchedulemanage.fromtime">0600</logic:notPresent>">
													</OBJECT>
												</td>
											</tr>
										</table>
									</td>
									<td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										班级安排结束时间
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr>

												<html:hidden property="classSchedulemanage.titime" />

												<td width="130">
													<OBJECT id="etime" class="TxtInput" border="1" style="HEIGHT: 16; WIDTH: 120;" tabIndex="4" type="text/x-scriptlet" VIEWASTEXT>
														<PARAM NAME="URL"
															VALUE="timesetup.do?timeStr=<logic:present name="scheduleForm" property="classSchedulemanage.titime"><bean:write name="scheduleForm" property="classSchedulemanage.titime"/></logic:present><logic:notPresent name="scheduleForm" property="classSchedulemanage.titime">0605</logic:notPresent>">
													</OBJECT>
												</td>
											</tr>
										</table>
									</td>
								</tr>
								<tr align="center" valign=middle>
									<td height="28" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										地点
									</td>
									<td colspan="3" align="left" valign="middle" class="tableHeader3">
										<html:text property="classSchedulemanage.positon" styleClass="input_box" style="width:200" maxlength="50" />
									</td>
								</tr>
								<tr align="center" valign=middle>
									<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										任务
									</td>
									<td colspan="3" align="left" valign="middle" class="tableHeader3">
										<html:textarea property="classSchedulemanage.mission" cols="70" rows="2" />
									</td>
								</tr>
								<tr align="center" valign=middle>
									<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										备注
									</td>
									<td colspan="3" align="left" valign="middle" class="tableHeader3">
										<bean:write name="scheduleForm" property="schedulemanage.remark" />
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>

					<td height="40" align="right" valign="middle">
						<logic:notPresent name="scheduleForm" property="classSchedulemanage.scheduleId">
							<input name="Submit" type="submit" class="button_nor" value="确 定" />
						</logic:notPresent>
						<logic:present name="scheduleForm" property="classSchedulemanage.scheduleId">
							<input name="Submit" type="submit" class="button_nor" value="修 改" />
						&nbsp;&nbsp;
						<input name="Submit2" type="button" class="button_nor" value="删 除" onclick="javascript:if(confirm('删除这项日程？')){document.scheduleForm.action='scheduleAction.do?method=classDelete';document.scheduleForm.submit();}" />
						</logic:present>
						&nbsp;&nbsp;
						<input name="Submit2" type="button" class="button_nor" value="取 消" onclick="javascript:howtoreturn();" />
					</td>

				</tr>
			</table>
		</html:form>
		<table width="100%" border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff >
			<tr align="center">
				<td colspan="4">
					该书院日程下已安排的班级日程
				</td>
			</tr>
			<tr align="center" valign="middle">
				<td valign="middle" width="80" class="tableHeader">
					班级时间
				</td>
				<td valign="middle" width="80" class="tableHeader">
					班级
				</td>
				<td valign="middle" width="150" class="tableHeader">
					地点
				</td>
				<td valign="middle" class="tableHeader">
					任务
				</td>
			</tr>
			<%java.util.List scheduleList = (java.util.List) request
					.getAttribute("classSchedules");
			for (int i = 0; i < scheduleList.size(); i++) {
				Map map = (Map)scheduleList.get(i);
				Classschedulemodel classschedulemodel = (Classschedulemodel) map.get("classschedule");
				String classNo = (String)map.get("classNo");		

				%>
				<tr align="center" valign="middle">
					<td>
						<%=classschedulemodel.getFromtime().substring(0,
										2)%>:<%=classschedulemodel.getFromtime().substring(2)%>--<%=classschedulemodel.getTitime().substring(0, 2)%>:<%=classschedulemodel.getTitime().substring(2)%>
					</td>
					<td>
						<%=classNo%>班
					</td>
					<td>
						<%=classschedulemodel.getPositon()%>
					</td>
					<td>
						<%=classschedulemodel.getMission()%>
					</td>
				</tr>
			<%}
				if(scheduleList.size() == 0){
			%>
			<tr align="center">
				<td colspan="4">
					暂无
				</td>
			</tr>
			<%}%>
		</table>
		<SCRIPT language=javascript>
		function howtoreturn(){
			window.location.href='scheduleAction.do?method=load4classList';
		}			
		
//==================================================== 参数设定部分 =======================================================
var bMoveable=true;		//设置日历是否可以拖动
var _VersionInfo="Version:2.0&#13;2.0作者:walkingpoison&#13;1.0作者: F.R.Huang(meizz)&#13;MAIL: meizz@hzcnc.com"	//版本信息

//==================================================== WEB 页面显示部分 =====================================================
var strFrame;		//存放日历层的HTML代码
document.writeln('<iframe id=meizzDateLayer Author=wayx frameborder=0 style="position: absolute; width: 144; height: 211; z-index: 9998; display: none"></iframe>');
strFrame='<style>';
strFrame+='INPUT.button{BORDER-RIGHT: #6699FF 1px solid;BORDER-TOP: #6699FF 1px solid;BORDER-LEFT: #6699FF 1px solid;';
strFrame+='BORDER-BOTTOM: #6699FF 1px solid;BACKGROUND-COLOR: #fff8ec;font-family:宋体;}';
strFrame+='TD{FONT-SIZE: 9pt;font-family:宋体;}';
strFrame+='</style>';
strFrame+='<scr' + 'ipt>';
strFrame+='var datelayerx,datelayery;	/*存放日历控件的鼠标位置*/';
strFrame+='var bDrag;	/*标记是否开始拖动*/';
strFrame+='function document.onmousemove()	/*在鼠标移动事件中，如果开始拖动日历，则移动日历*/';
strFrame+='{if(bDrag && window.event.button==1)';
strFrame+='	{var DateLayer=parent.document.all.meizzDateLayer.style;';
strFrame+='		DateLayer.posLeft += window.event.clientX-datelayerx;/*由于每次移动以后鼠标位置都恢复为初始的位置，因此写法与div中不同*/';
strFrame+='		DateLayer.posTop += window.event.clientY-datelayery;}}';
strFrame+='function DragStart()		/*开始日历拖动*/';
strFrame+='{var DateLayer=parent.document.all.meizzDateLayer.style;';
strFrame+='	datelayerx=window.event.clientX;';
strFrame+='	datelayery=window.event.clientY;';
strFrame+='	bDrag=true;}';
strFrame+='function DragEnd(){		/*结束日历拖动*/';
strFrame+='	bDrag=false;}';
strFrame+='</scr' + 'ipt>';
strFrame+='<div style="z-index:9999;position: absolute; left:0; top:0;" onselectstart="return false"><span id=tmpSelectYearLayer Author=wayx style="z-index: 9999;position: absolute;top: 3; left: 19;display: none"></span>';
strFrame+='<span id=tmpSelectMonthLayer Author=wayx style="z-index: 9999;position: absolute;top: 3; left: 78;display: none"></span>';
strFrame+='<table border=1 cellspacing=0 cellpadding=0 width=142 height=160 bordercolor=#6699FF bgcolor=#6699FF Author="wayx">';
strFrame+='  <tr Author="wayx"><td width=142 height=23 Author="wayx" bgcolor=#FFFFFF><table border=0 cellspacing=1 cellpadding=0 width=140 Author="wayx" height=23>';
strFrame+='      <tr align=center Author="wayx"><td width=16 align=center bgcolor=#6699FF style="font-size:12px;cursor: hand;color: #ffffff" ';
strFrame+='        onclick="parent.meizzPrevM()" title="向前翻 1 月" Author=meizz><b Author=meizz>&lt;</b>';
strFrame+='        </td><td width=60 align=center style="font-size:12px;cursor:default" Author=meizz ';
strFrame+='onmouseover="style.backgroundColor=\'#0099FF\'" onmouseout="style.backgroundColor=\'white\'" ';
strFrame+='onclick="parent.tmpSelectYearInnerHTML(this.innerText.substring(0,4))" title="点击这里选择年份"><span Author=meizz id=meizzYearHead></span></td>';
strFrame+='<td width=48 align=center style="font-size:12px;cursor:default" Author=meizz onmouseover="style.backgroundColor=\'#0099FF\'" ';
strFrame+=' onmouseout="style.backgroundColor=\'white\'" onclick="parent.tmpSelectMonthInnerHTML(this.innerText.length==3?this.innerText.substring(0,1):this.innerText.substring(0,2))"';
strFrame+='        title="点击这里选择月份"><span id=meizzMonthHead Author=meizz></span></td>';
strFrame+='        <td width=16 bgcolor=#6699FF align=center style="font-size:12px;cursor: hand;color: #ffffff" ';
strFrame+='         onclick="parent.meizzNextM()" title="向后翻 1 月" Author=meizz><b Author=meizz>&gt;</b></td></tr>';
strFrame+='    </table></td></tr>';
strFrame+='  <tr Author="wayx"><td width=142 height=18 Author="wayx">';
strFrame+='<table border=1 cellspacing=0 cellpadding=0 bgcolor=#6699FF ' + (bMoveable? 'onmousedown="DragStart()" onmouseup="DragEnd()"':'');
strFrame+=' BORDERCOLORLIGHT=#6699FF BORDERCOLORDARK=#FFFFFF width=140 height=20 Author="wayx" style="cursor:' + (bMoveable ? 'move':'default') + '">';
strFrame+='<tr Author="wayx" align=center valign=bottom><td style="font-size:12px;color:#FFFFFF" Author=meizz>日</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>一</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>二</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>三</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>四</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>五</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>六</td></tr>';
strFrame+='</table></td></tr><!-- Author:F.R.Huang(meizz) http://www.meizz.com/ mail: meizz@hzcnc.com 2002-10-8 -->';
strFrame+='  <tr Author="wayx"><td width=142 height=120 Author="wayx">';
strFrame+='    <table border=1 cellspacing=2 cellpadding=0 BORDERCOLORLIGHT=#6699FF BORDERCOLORDARK=#FFFFFF bgcolor=#fff8ec width=140 height=120 Author="wayx">';
var n=0; for (j=0;j<5;j++){ strFrame+= ' <tr align=center Author="wayx">'; for (i=0;i<7;i++){
strFrame+='<td width=20 height=20 id=meizzDay'+n+' style="font-size:12px" Author=meizz onclick=parent.meizzDayClick(this.innerText,0)></td>';n++;}
strFrame+='</tr>';}
strFrame+='      <tr align=center Author="wayx">';
for (i=35;i<39;i++)strFrame+='<td width=20 height=20 id=meizzDay'+i+' style="font-size:12px" Author=wayx onclick="parent.meizzDayClick(this.innerText,0)"></td>';
strFrame+='        <td colspan=3 align=right Author=meizz><span onclick=parent.closeLayer() style="font-size:12px;cursor: hand"';
strFrame+='         Author=meizz title="' + _VersionInfo + '"><u>关闭</u></span>&nbsp;</td></tr>';
strFrame+='    </table></td></tr><tr Author="wayx"><td Author="wayx">';
strFrame+='        <table border=0 cellspacing=1 cellpadding=0 width=100% Author="wayx" bgcolor=#FFFFFF>';
strFrame+='          <tr Author="wayx"><td Author=meizz align=left><input Author=meizz type=button class=button value="<<" title="向前翻 1 年" onclick="parent.meizzPrevY()" ';
strFrame+='             onfocus="this.blur()" style="font-size: 12px; height: 20px"><input Author=meizz class=button title="向前翻 1 月" type=button ';
strFrame+='             value="< " onclick="parent.meizzPrevM()" onfocus="this.blur()" style="font-size: 12px; height: 20px"></td><td ';
strFrame+='             Author=meizz align=center><input Author=meizz type=button class=button value=今天 onclick="parent.meizzToday()" ';
strFrame+='             onfocus="this.blur()" title="当前日期" style="font-size: 12px; height: 20px; cursor:hand"></td><td ';
strFrame+='             Author=meizz align=right><input Author=meizz type=button class=button value=" >" onclick="parent.meizzNextM()" ';
strFrame+='             onfocus="this.blur()" title="向后翻 1 月" class=button style="font-size: 12px; height: 20px"><input ';
strFrame+='             Author=meizz type=button class=button value=">>" title="向后翻 1 年" onclick="parent.meizzNextY()"';
strFrame+='             onfocus="this.blur()" style="font-size: 12px; height: 20px"></td>';
strFrame+='</tr></table></td></tr></table></div>';

window.frames.meizzDateLayer.document.writeln(strFrame);
window.frames.meizzDateLayer.document.close();		//解决ie进度条不结束的问题

//==================================================== WEB 页面显示部分 ======================================================
var outObject;
var outButton;		//点击的按钮
var outDate="";		//存放对象的日期
var odatelayer=window.frames.meizzDateLayer.document.all;		//存放日历对象
function setday(tt,obj) //主调函数
{
	if (arguments.length >  2){alert("对不起！传入本控件的参数太多！");return;}
	if (arguments.length == 0){alert("对不起！您没有传回本控件任何参数！");return;}
	var dads  = document.all.meizzDateLayer.style;
	var th = tt;
	var ttop  = tt.offsetTop;     //TT控件的定位点高
	var thei  = tt.clientHeight;  //TT控件本身的高
	var tleft = tt.offsetLeft;    //TT控件的定位点宽
	var ttyp  = tt.type;          //TT控件的类型
	while (tt = tt.offsetParent){ttop+=tt.offsetTop; tleft+=tt.offsetLeft;}
	dads.top  = (ttyp=="image")? ttop+thei : ttop+thei+6;
	dads.left = tleft;
	outObject = (arguments.length == 1) ? th : obj;
	outButton = (arguments.length == 1) ? null : th;	//设定外部点击的按钮
	//根据当前输入框的日期显示日历的年月
	var reg = /^(\d+)-(\d{1,2})-(\d{1,2})$/;
	var r = outObject.value.match(reg);
	if(r!=null){
		r[2]=r[2]-1;
		var d= new Date(r[1], r[2],r[3]);
		if(d.getFullYear()==r[1] && d.getMonth()==r[2] && d.getDate()==r[3]){
			outDate=d;		//保存外部传入的日期
		}
		else outDate="";
			meizzSetDay(r[1],r[2]+1);
	}
	else{
		outDate="";
		meizzSetDay(new Date().getFullYear(), new Date().getMonth() + 1);
	}
	dads.display = '';

	event.returnValue=false;
}

var MonHead = new Array(12);    		   //定义阳历中每个月的最大天数
    MonHead[0] = 31; MonHead[1] = 28; MonHead[2] = 31; MonHead[3] = 30; MonHead[4]  = 31; MonHead[5]  = 30;
    MonHead[6] = 31; MonHead[7] = 31; MonHead[8] = 30; MonHead[9] = 31; MonHead[10] = 30; MonHead[11] = 31;

var meizzTheYear=new Date().getFullYear(); //定义年的变量的初始值
var meizzTheMonth=new Date().getMonth()+1; //定义月的变量的初始值
var meizzWDay=new Array(39);               //定义写日期的数组

function document.onclick() //任意点击时关闭该控件	//ie6的情况可以由下面的切换焦点处理代替
{
  with(window.event)
  { if (srcElement.getAttribute("Author")==null && srcElement != outObject && srcElement != outButton)
    closeLayer();
  }
}

function document.onkeyup()		//按Esc键关闭，切换焦点关闭
  {
    if (window.event.keyCode==27){
		if(outObject)outObject.blur();
		closeLayer();
	}
	else if(document.activeElement)
		if(document.activeElement.getAttribute("Author")==null && document.activeElement != outObject && document.activeElement != outButton)
		{
			closeLayer();
		}
  }

function meizzWriteHead(yy,mm)  //往 head 中写入当前的年与月
  {
	odatelayer.meizzYearHead.innerText  = yy + " 年";
    odatelayer.meizzMonthHead.innerText = mm + " 月";
  }

function tmpSelectYearInnerHTML(strYear) //年份的下拉框
{
  if (strYear.match(/\D/)!=null){alert("年份输入参数不是数字！");return;}
  var m = (strYear) ? strYear : new Date().getFullYear();
  if (m < 1000 || m > 9999) {alert("年份值不在 1000 到 9999 之间！");return;}
  var n = m - 80;
  if (n < 1000) n = 1000;
  if (n + 26 > 9999) n = 9974;
  var s = "<select Author=meizz name=tmpSelectYear style='font-size: 12px' "
     s += "onblur='document.all.tmpSelectYearLayer.style.display=\"none\"' "
     s += "onchange='document.all.tmpSelectYearLayer.style.display=\"none\";"
     s += "parent.meizzTheYear = this.value; parent.meizzSetDay(parent.meizzTheYear,parent.meizzTheMonth)'>\r\n";
  var selectInnerHTML = s;
  for (var i = n; i < n + 161; i++)
  {
    if (i == m)
       {selectInnerHTML += "<option Author=wayx value='" + i + "' selected>" + i + "年" + "</option>\r\n";}
    else {selectInnerHTML += "<option Author=wayx value='" + i + "'>" + i + "年" + "</option>\r\n";}
  }
  selectInnerHTML += "</select>";
  odatelayer.tmpSelectYearLayer.style.display="";
  odatelayer.tmpSelectYearLayer.innerHTML = selectInnerHTML;
  odatelayer.tmpSelectYear.focus();
}

function tmpSelectMonthInnerHTML(strMonth) //月份的下拉框
{
  if (strMonth.match(/\D/)!=null){alert("月份输入参数不是数字！");return;}
  var m = (strMonth) ? strMonth : new Date().getMonth() + 1;
  var s = "<select Author=meizz name=tmpSelectMonth style='font-size: 12px' "
     s += "onblur='document.all.tmpSelectMonthLayer.style.display=\"none\"' "
     s += "onchange='document.all.tmpSelectMonthLayer.style.display=\"none\";"
     s += "parent.meizzTheMonth = this.value; parent.meizzSetDay(parent.meizzTheYear,parent.meizzTheMonth)'>\r\n";
  var selectInnerHTML = s;
  for (var i = 1; i < 13; i++)
  {
    if (i == m)
       {selectInnerHTML += "<option Author=wayx value='"+i+"' selected>"+i+"月"+"</option>\r\n";}
    else {selectInnerHTML += "<option Author=wayx value='"+i+"'>"+i+"月"+"</option>\r\n";}
  }
  selectInnerHTML += "</select>";
  odatelayer.tmpSelectMonthLayer.style.display="";
  odatelayer.tmpSelectMonthLayer.innerHTML = selectInnerHTML;
  odatelayer.tmpSelectMonth.focus();
}

function closeLayer()               //这个层的关闭
  {
    document.all.meizzDateLayer.style.display="none";
  }

function IsPinYear(year)            //判断是否闰平年
  {
    if (0==year%4&&((year%100!=0)||(year%400==0))) return true;else return false;
  }

function GetMonthCount(year,month)  //闰年二月为29天
  {
    var c=MonHead[month-1];if((month==2)&&IsPinYear(year)) c++;return c;
  }
function GetDOW(day,month,year)     //求某天的星期几
  {
    var dt=new Date(year,month-1,day).getDay()/7; return dt;
  }

function meizzPrevY()  //往前翻 Year
  {
    if(meizzTheYear > 999 && meizzTheYear <10000){meizzTheYear--;}
    else{alert("年份超出范围（1000-9999）！");}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }
function meizzNextY()  //往后翻 Year
  {
    if(meizzTheYear > 999 && meizzTheYear <10000){meizzTheYear++;}
    else{alert("年份超出范围（1000-9999）！");}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }
function meizzToday()  //Today Button
  {
	var today;
    meizzTheYear = new Date().getFullYear();
    meizzTheMonth = new Date().getMonth()+1;
    today=new Date().getDate();
    //meizzSetDay(meizzTheYear,meizzTheMonth);
    if(outObject){
		outObject.value=meizzTheYear + "-" + meizzTheMonth + "-" + today;
    }
    closeLayer();
  }
function meizzPrevM()  //往前翻月份
  {
    if(meizzTheMonth>1){meizzTheMonth--}else{meizzTheYear--;meizzTheMonth=12;}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }
function meizzNextM()  //往后翻月份
  {
    if(meizzTheMonth==12){meizzTheYear++;meizzTheMonth=1}else{meizzTheMonth++}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }

function meizzSetDay(yy,mm)   //主要的写程序**********
{
  meizzWriteHead(yy,mm);
  //设置当前年月的公共变量为传入值
  meizzTheYear=yy;
  meizzTheMonth=mm;

  for (var i = 0; i < 39; i++){meizzWDay[i]=""};  //将显示框的内容全部清空
  var day1 = 1,day2=1,firstday = new Date(yy,mm-1,1).getDay();  //某月第一天的星期几
  for (i=0;i<firstday;i++)meizzWDay[i]=GetMonthCount(mm==1?yy-1:yy,mm==1?12:mm-1)-firstday+i+1	//上个月的最后几天
  for (i = firstday; day1 < GetMonthCount(yy,mm)+1; i++){meizzWDay[i]=day1;day1++;}
  for (i=firstday+GetMonthCount(yy,mm);i<39;i++){meizzWDay[i]=day2;day2++}
  for (i = 0; i < 39; i++)
  { var da = eval("odatelayer.meizzDay"+i)     //书写新的一个月的日期星期排列
    if (meizzWDay[i]!="")
      {
		//初始化边框
		da.borderColorLight="#6699FF";
		da.borderColorDark="#FFFFFF";
		if(i<firstday)		//上个月的部分
		{
			da.innerHTML="<b><font color=gray>" + meizzWDay[i] + "</font></b>";
			da.title=(mm==1?12:mm-1) +"月" + meizzWDay[i] + "日";
			da.onclick=Function("meizzDayClick(this.innerText,-1)");
			if(!outDate)
				da.style.backgroundColor = ((mm==1?yy-1:yy) == new Date().getFullYear() &&
					(mm==1?12:mm-1) == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate()) ?
					 "#0099FF":"#e0e0e0";
			else
			{
				da.style.backgroundColor =((mm==1?yy-1:yy)==outDate.getFullYear() && (mm==1?12:mm-1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())? "#9DD8FF" :
				(((mm==1?yy-1:yy) == new Date().getFullYear() && (mm==1?12:mm-1) == new Date().getMonth()+1 &&
				meizzWDay[i] == new Date().getDate()) ? "#0099FF":"#e0e0e0");
				//将选中的日期显示为凹下去
				if((mm==1?yy-1:yy)==outDate.getFullYear() && (mm==1?12:mm-1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())
				{
					da.borderColorLight="#FFFFFF";
					da.borderColorDark="#6699FF";
				}
			}
		}
		else if (i>=firstday+GetMonthCount(yy,mm))		//下个月的部分
		{
			da.innerHTML="<b><font color=gray>" + meizzWDay[i] + "</font></b>";
			da.title=(mm==12?1:mm+1) +"月" + meizzWDay[i] + "日";
			da.onclick=Function("meizzDayClick(this.innerText,1)");
			if(!outDate)
				da.style.backgroundColor = ((mm==12?yy+1:yy) == new Date().getFullYear() &&
					(mm==12?1:mm+1) == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate()) ?
					 "#0099FF":"#e0e0e0";
			else
			{
				da.style.backgroundColor =((mm==12?yy+1:yy)==outDate.getFullYear() && (mm==12?1:mm+1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())? "#9DD8FF" :
				(((mm==12?yy+1:yy) == new Date().getFullYear() && (mm==12?1:mm+1) == new Date().getMonth()+1 &&
				meizzWDay[i] == new Date().getDate()) ? "#0099FF":"#e0e0e0");
				//将选中的日期显示为凹下去
				if((mm==12?yy+1:yy)==outDate.getFullYear() && (mm==12?1:mm+1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())
				{
					da.borderColorLight="#FFFFFF";
					da.borderColorDark="#6699FF";
				}
			}
		}
		else		//本月的部分
		{
			da.innerHTML="<b>" + meizzWDay[i] + "</b>";
			da.title=mm +"月" + meizzWDay[i] + "日";
			da.onclick=Function("meizzDayClick(this.innerText,0)");		//给td赋予onclick事件的处理
			//如果是当前选择的日期，则显示亮蓝色的背景；如果是当前日期，则显示暗黄色背景
			if(!outDate)
				da.style.backgroundColor = (yy == new Date().getFullYear() && mm == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate())?
					"#0099FF":"#e0e0e0";
			else
			{
				da.style.backgroundColor =(yy==outDate.getFullYear() && mm== outDate.getMonth() + 1 && meizzWDay[i]==outDate.getDate())?
					"#9DD8FF":((yy == new Date().getFullYear() && mm == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate())?
					"#0099FF":"#e0e0e0");
				//将选中的日期显示为凹下去
				if(yy==outDate.getFullYear() && mm== outDate.getMonth() + 1 && meizzWDay[i]==outDate.getDate())
				{
					da.borderColorLight="#FFFFFF";
					da.borderColorDark="#6699FF";
				}
			}
		}
        da.style.cursor="hand"
      }
    else{da.innerHTML="";da.style.backgroundColor="";da.style.cursor="default"}
  }
}

function meizzDayClick(n,ex)  //点击显示框选取日期，主输入函数*************
{
  var yy=meizzTheYear;
  var mm = parseInt(meizzTheMonth)+ex;	//ex表示偏移量，用于选择上个月份和下个月份的日期
	//判断月份，并进行对应的处理
	if(mm<1){
		yy--;
		mm=12+mm;
	}
	else if(mm>12){
		yy++;
		mm=mm-12;
	}

  if (mm < 10){mm = "0" + mm;}
  if (outObject)
  {
    if (!n) {//outObject.value="";
      return;}
    if ( n < 10){n = "0" + n;}
    outObject.value= yy + "-" + mm + "-" + n ; //注：在这里你可以输出改成你想要的格式
    closeLayer();
  }
  else {closeLayer(); alert("您所要输出的控件对象并不存在！");}
}

function isQuoteExist(form1)
{
  var fe = form1.elements;
  for (i=0;i<fe.length;i++)
  {
    if ((fe[i].type=="text" || fe[i].type=="password" || fe[i].type=="textarea") && fe[i].value.indexOf("'")!=-1)
    {
       alert('输入值中不能含有单引号!!!');
       fe[i].focus();
       return true;
    }
  }
}
</SCRIPT>
	</body>
</html>
