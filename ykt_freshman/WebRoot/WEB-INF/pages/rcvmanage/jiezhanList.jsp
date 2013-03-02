<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>
<!-- <script type="text/javascript" src="<c:url value='/pages/scripts/sorttable.js'/>"></script>  -->
<center>
<html:form action = "rcvmanageAction.do?method=jiezhanfind">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
 
    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生接站信息查询</font></strong></td>
    </tr>
    <tr>
      <td align="center" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="center" valign="top" >
      <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>          
            <tr align="center" valign=center> 
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >学号</td>
              <td width="35%" align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td width="15%" align="right" valign="middle" class="tableHeader2" >班级</td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="classNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            </tr>
            <tr align="center" valign=center>
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >抵沪日期</td>
              <td align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130"> <input 
            name="arriveDate" class="input_box"  maxlength=50 value="" onFocus="ChangeFocus1()" readonly="readonly"> 
                    </td>
                    <td><img name="selectDate" class="img_nor" width="21" height="21" border="0" onclick="setday(this,document.all.arriveDate)"></td>
                  </tr>
                </table></td>
              <td align="right" valign="middle" class="tableHeader2" >抵沪时间</td>
              <td align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <OBJECT id="time" class="TxtInput"  border="1" style="HEIGHT: 16; WIDTH: 120;" tabIndex="4" type="text/x-scriptlet" VIEWASTEXT>
                         <PARAM NAME="URL" VALUE="rcvtimesetup.do">
                    </OBJECT> 
                    </td>
                    <td>
                    <input name="timeselect" type="checkbox" value="15" >需要时间条件<input type="hidden" name="arriveTime" value="">
                    </td>
                  </tr>
                </table></td>
            </tr>
            <tr align="center" valign=center> 
            <td align="right" valign="middle" class="tableHeader2" >抵沪方式</td>
              <td align="left" valign="middle" class="tableHeader3" > 
                <select name="arrivePlace" class="select01">
                  <option value="" selected>请选择</option>                  
                  <option value="01">火车</option>
                  <option value="02">长途汽车</option>
                  <option value="03">飞机</option>
                  <option value="04">自驾车</option>
                  <option value="05">其他</option>
                  <option value="06">本市</option>
                </select></td>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                火车车次</td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="trainNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>              
            </tr> 
             <logic:present name="arriveform" scope="request"> 
            <input name="stuarriveinfo.enrollNo" type="hidden" value="<bean:write name="arriveform" property="enrollNo" />">     
            <input name="stuarriveinfo.arriveDate" type="hidden" value="<bean:write name="arriveform" property="arriveDate" />"> 
            <input name="stuarriveinfo.arriveTime" type="hidden" value="<bean:write name="arriveform" property="arriveTime" />">           
            <input name="stuarriveinfo.arrivePlace" type="hidden" value="<bean:write name="arriveform" property="arrivePlace" />">               
            <input name="stuarriveinfo.trainNo" type="hidden" value="<bean:write name="arriveform" property="trainNo" />">
            </logic:present>
            <logic:notPresent name="arriveform" scope="request">  
            <input name="stuarriveinfo.enrollNo" type="hidden" value="">   
            <input name="stuarriveinfo.arriveDate" type="hidden" value="1900-01-01"> 
            <input name="stuarriveinfo.arriveTime" type="hidden" value="00:00:01">            
            <input name="stuarriveinfo.arrivePlace" type="hidden" value="">                
            <input name="stuarriveinfo.trainNo" type="hidden" value="">  
            </logic:notPresent>
             <logic:present name="classNo" scope="request">
             <input name="hclassNo" type="hidden" value="<bean:write name="classNo" />"> 
             </logic:present>   
             <logic:notPresent name="classNo" scope="request">  
             <input name="hclassNo" type="hidden" value="">
             </logic:notPresent>
             <logic:present name="studentNo" scope="request">
             <input name="hstudentNo" type="hidden" value="<bean:write name="studentNo" />"> 
             </logic:present>   
             <logic:notPresent name="studentNo" scope="request">  
             <input name="hstudentNo" type="hidden" value="">
             </logic:notPresent>         
          </tbody>
        </table></td>
    </tr>
    <tr> 
      <td height="40" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="查 询" onClick="DoFind()"> 
      <input name="Reset" type="button" class="button_nor" value="重 置" onClick="DoClear()"> 
      </td>
    </tr><input type="hidden" name="updateid" value=""> <input name="doexl" type="hidden" value="">    
    <input name="orderby" type="hidden" value="">
    <logic:present name="jzlist">
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         <a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      
      </td>
    </tr>
    </logic:present>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=maintable>
          <tbody>   
           <logic:present name="jzlist">       
           <thead>
            <tr align="center" valign=center> 
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('arriveDate')">抵沪日期</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('arriveTime')">抵沪时间</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('arrivePlace')">抵沪方式</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifDeleted')">抵沪地点</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('trainNo')">火车车次</a></td>
              <td height="24" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')">学号</a></td>
              <td valign="middle" class="tableHeader" nowrap><a style="font-size:14px;color: black" href="javascript:DoSort('enrollNo')">录取通知书号</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('stuName')">姓名</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('classNo')">班级</a></td>                                          
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('companyNum')">陪同人数</a></td>              
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifNeedBus')">坐校车</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('tempconcact')">联系方式</a></td>
            </tr>
           </thead>
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./rcvmanageAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%>
            <pg:param name="method" />
			<pg:param name="hstudentNo" />
			<pg:param name="hclassNo" />			
			<pg:param name="stuarriveinfo.trainNo" />
			<pg:param name="stuarriveinfo.arriveDate" />
			<pg:param name="stuarriveinfo.arriveTime" />
			<pg:param name="stuarriveinfo.arrivePlace" />
			<pg:param name="orderby" />
	  	    <pg:param name="horder" />
           
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="jzlist" id="jl" type="java.util.Map" indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center>  
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="arriveDate"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="arriveTime" formatKey="timeFormat"/></td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${jl.arrivePlace == '01'}">
                    火车
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '02'}">
                    长途汽车
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '03'}">
                    飞机
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '04'}">
                    自驾车
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '05'}">
                    其他
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '06'}">
                    本市
                  </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${jl.ifDeleted == '1'}">
                    上海站
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '2'}">
                    上海南站
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '3'}">
                    虹桥机场
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '4'}">
                    浦东机场
                  </c:when></c:choose>
                  &nbsp;
              </td>            
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="trainNo"/>&nbsp;</td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="jl" property="id"/>')"><bean:write name="jl" property="studentNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="enrollNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="classNo"/></td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${jl.arrivePlace == '01'}">
              <bean:write name="jl" property="companyNum"/>
              </c:when><c:otherwise>
              &nbsp;
              </c:otherwise></c:choose>
              </td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${jl.ifNeedBus == '0'}">
                否
              </c:when></c:choose>
              <c:choose><c:when test="${jl.ifNeedBus == '1'}">
                是
              </c:when></c:choose>              
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="tempconcact"/>&nbsp;</td>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="arriveDate"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="arriveTime" formatKey="timeFormat"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                  <c:choose><c:when test="${jl.arrivePlace == '01'}">
                    火车
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '02'}">
                    长途汽车
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '03'}">
                    飞机
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '04'}">
                    自驾车
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '05'}">
                    其他
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '06'}">
                    本市
                  </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                  <c:choose><c:when test="${jl.ifDeleted == '1'}">
                    上海站
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '2'}">
                    上海南站
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '3'}">
                    虹桥机场
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '4'}">
                    浦东机场
                  </c:when></c:choose>
                  &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="trainNo"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoView('<bean:write name="jl" property="id"/>')"><bean:write name="jl" property="studentNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="enrollNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${jl.arrivePlace == '01'}">
              <bean:write name="jl" property="companyNum"/>
              </c:when><c:otherwise>
              &nbsp;
              </c:otherwise></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${jl.ifNeedBus == '0'}">
                否
              </c:when></c:choose>
              <c:choose><c:when test="${jl.ifNeedBus == '1'}">
                是
              </c:when></c:choose>              
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="tempconcact"/>&nbsp;</td>
            </tr>
            </c:when></c:choose> 
            </pg:item>            
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
            </tbody>
        </table></td>        
    </tr>
    <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./page.jsp" flush="true" />
    </td>
  </tr>
		  </pg:pager>
		  <!-- page offset end -->		  
          </logic:present>
            
          <logic:notPresent name="jzlist" scope="request">                    
          <!--page offset start -->
		  <pg:pager url="./rcvmanagejiezhanpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
			<pg:param name="hstudentNo" />
			<pg:param name="hclassNo" />			
			<pg:param name="stuarriveinfo.trainNo" />
			<pg:param name="stuarriveinfo.arriveDate" />
			<pg:param name="stuarriveinfo.arriveTime" />
			<pg:param name="stuarriveinfo.arrivePlace" />			
           
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
           <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
		  </tbody>
        </table></td>        
    </tr>
            </logic:notPresent>                    
          
    <logic:present name="jzlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
    </td>
    </tr>  
    </logic:present>
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
<logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>
</html:form>
</center>

<script language="JavaScript">

setTimeout('init()',200);

function init(){
  
  document.all.studentNo.value=document.all.hstudentNo.value;
  if(document.forms[0].elements["stuarriveinfo.arriveDate"].value!='1900-01-01')  
      document.all.arriveDate.value=document.forms[0].elements["stuarriveinfo.arriveDate"].value;   
       
  document.all.classNo.value=document.all.hclassNo.value;
  document.all.trainNo.value=document.forms[0].elements["stuarriveinfo.trainNo"].value;
  
  if(document.forms[0].elements["stuarriveinfo.arriveTime"].value!='00:00:01'){
     document.all.time.setTime(document.forms[0].elements["stuarriveinfo.arriveTime"].value);
     document.all.timeselect.checked=true;
  }
  
  for(var i=0;i<document.all.arrivePlace.length;i++){
     
      if(document.forms[0].elements["stuarriveinfo.arrivePlace"].value==document.all.arrivePlace.options[i].value)
          document.all.arrivePlace.options[i].selected=true;
          
  }   
  
  if(document.all.hmsg.value=='1')
      alert("导出Excel成功!");
  else if(document.all.hmsg.value=='0')
      alert("无内容!");
}

function DoClear(){
  
   document.all.studentNo.value="";
   document.all.classNo.value="";
   document.all.arriveDate.value="";
   document.all.timeselect.checked=false;
   document.all.trainNo.value="";
   document.all.arrivePlace.options[0].selected=true;
   
   document.all.hstudentNo.value="";
   document.all.hclassNo.value="";
   document.forms[0].elements["stuarriveinfo.enrollNo"].value="";
   document.forms[0].elements["stuarriveinfo.trainNo"].value="";
   document.forms[0].elements["stuarriveinfo.arriveDate"].value="1900-01-01";
   document.forms[0].elements["stuarriveinfo.arriveTime"].value="00:00:01";
   document.forms[0].elements["stuarriveinfo.arrivePlace"].value="";
   //alert(document.all.arriveDate.value);
   //alert(document.forms[0].elements["stuarriveinfo.arriveDate"].value);
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		DoFind();
		return false;
	}
}

function DoFind(){
   
   if(document.all.timeselect.checked){
       document.all.arriveTime.value=document.all.time.getTime();
       //alert(document.all.arriveTime.value);
   }
   else
       document.all.arriveTime.value="";
       
   document.forms[0].elements["pager.offset"].value="0";
   document.all.doexl.value="";
   
   document.all.hstudentNo.value=document.all.studentNo.value;
   document.all.hclassNo.value=document.all.classNo.value;
   document.forms[0].elements["stuarriveinfo.enrollNo"].value="";
   document.forms[0].elements["stuarriveinfo.trainNo"].value=document.all.trainNo.value;
   if(document.all.arriveDate.value!='')
       document.forms[0].elements["stuarriveinfo.arriveDate"].value=document.all.arriveDate.value;
       
   if(document.all.timeselect.checked&&document.all.arriveTime.value!='00:00:01')
       document.forms[0].elements["stuarriveinfo.arriveTime"].value=document.all.arriveTime.value;
       
   document.forms[0].elements["stuarriveinfo.arrivePlace"].value=document.all.arrivePlace.value;
   
   document.stuarriveinfoForm.action="rcvmanageAction.do?method=jiezhanfind";
   document.stuarriveinfoForm.submit();
   
}

function DoSort(col){
  document.all.doexl.value="";
  document.all.orderby.value=col;
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.stuarriveinfoForm.action="rcvmanageAction.do?method=jiezhanfind";
  document.stuarriveinfoForm.submit();
}

function ChangeFocus1(){
    document.all.selectDate.focus();
}

function DoView(str){

   document.all.updateid.value=str;   
   document.stuarriveinfoForm.action="rcvmanageAction.do?method=view";
   document.stuarriveinfoForm.submit();
}

function DoExport(){

   document.all.doexl.value="1";
   if(document.all.timeselect.checked){
       document.all.arriveTime.value=document.all.time.getTime();
       //alert(document.all.arriveTime.value);
   }
   else
       document.all.arriveTime.value="";

   document.all.hstudentNo.value=document.all.studentNo.value;
   document.all.hclassNo.value=document.all.classNo.value;
   document.forms[0].elements["stuarriveinfo.enrollNo"].value="";
   document.forms[0].elements["stuarriveinfo.trainNo"].value=document.all.trainNo.value;
   if(document.all.arriveDate.value!='')
       document.forms[0].elements["stuarriveinfo.arriveDate"].value=document.all.arriveDate.value;
       
   if(document.all.timeselect.checked&&document.all.arriveTime.value!='00:00:01')
       document.forms[0].elements["stuarriveinfo.arriveTime"].value=document.all.arriveTime.value;
       
   document.forms[0].elements["stuarriveinfo.arrivePlace"].value=document.all.arrivePlace.value;
   
   document.stuarriveinfoForm.action="rcvmanageAction.do?method=jiezhanfind";
   document.stuarriveinfoForm.submit();

}

</script>

<script language="JavaScript">

//==================================================== 参数设定部分 =======================================================
var bMoveable=true;		//设置日历是否可以拖动
var _VersionInfo="Version:2.0&#13;2.0作者:walkingpoison&#13;1.0作者: F.R.Huang(meizz)&#13;MAIL: meizz@hzcnc.com"	//版本信息

//==================================================== WEB 页面显示部分 =====================================================
var strFrame;		//存放日历层的HTML代码
document.writeln('<iframe id=meizzDateLayer Author=wayx frameborder=0 style="position: absolute; width: 144; height: 211; z-index: 9998; display: none"></iframe>');
strFrame='<style>';
strFrame+='INPUT.button{BORDER-RIGHT: #FF9999 1px solid;BORDER-TOP: #DCC9CA 1px solid;BORDER-LEFT: #DCC9CA 1px solid;';
strFrame+='BORDER-BOTTOM: #DCC9CA 1px solid;BACKGROUND-COLOR: #DCC9CA;font-family:宋体;}';
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
strFrame+='<table border=1 cellspacing=0 cellpadding=0 width=142 height=160 bordercolor=#DCC9CA bgcolor=#DCC9CA Author="wayx">';
strFrame+='  <tr Author="wayx"><td width=142 height=23 Author="wayx" bgcolor=#FFFFFF><table border=0 cellspacing=1 cellpadding=0 width=140 Author="wayx" height=23>';
strFrame+='      <tr align=center Author="wayx"><td width=16 align=center bgcolor=#DCC9CA style="font-size:12px;cursor: hand;color: #ffffff" ';
strFrame+='        onclick="parent.meizzPrevM()" title="向前翻 1 月" Author=meizz><b Author=meizz>&lt;</b>';
strFrame+='        </td><td width=60 align=center style="font-size:12px;cursor:default" Author=meizz ';
strFrame+='onmouseover="style.backgroundColor=\'#0099FF\'" onmouseout="style.backgroundColor=\'white\'" ';
strFrame+='onclick="parent.tmpSelectYearInnerHTML(this.innerText.substring(0,4))" title="点击这里选择年份"><span Author=meizz id=meizzYearHead></span></td>';
strFrame+='<td width=48 align=center style="font-size:12px;cursor:default" Author=meizz onmouseover="style.backgroundColor=\'#0099FF\'" ';
strFrame+=' onmouseout="style.backgroundColor=\'white\'" onclick="parent.tmpSelectMonthInnerHTML(this.innerText.length==3?this.innerText.substring(0,1):this.innerText.substring(0,2))"';
strFrame+='        title="点击这里选择月份"><span id=meizzMonthHead Author=meizz></span></td>';
strFrame+='        <td width=16 bgcolor=#DCC9CA align=center style="font-size:12px;cursor: hand;color: #ffffff" ';
strFrame+='         onclick="parent.meizzNextM()" title="向后翻 1 月" Author=meizz><b Author=meizz>&gt;</b></td></tr>';
strFrame+='    </table></td></tr>';
strFrame+='  <tr Author="wayx"><td width=142 height=18 Author="wayx">';
strFrame+='<table border=1 cellspacing=0 cellpadding=0 bgcolor=#DCC9CA ' + (bMoveable? 'onmousedown="DragStart()" onmouseup="DragEnd()"':'');
strFrame+=' BORDERCOLORLIGHT=#DCC9CA BORDERCOLORDARK=#FFFFFF width=140 height=20 Author="wayx" style="cursor:' + (bMoveable ? 'move':'default') + '">';
strFrame+='<tr Author="wayx" align=center valign=bottom><td style="font-size:12px;color:#FFFFFF" Author=meizz>日</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>一</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>二</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>三</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>四</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>五</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>六</td></tr>';
strFrame+='</table></td></tr><!-- Author:F.R.Huang(meizz) http://www.meizz.com/ mail: meizz@hzcnc.com 2002-10-8 -->';
strFrame+='  <tr Author="wayx"><td width=142 height=120 Author="wayx">';
strFrame+='    <table border=1 cellspacing=2 cellpadding=0 BORDERCOLORLIGHT=#DCC9CA BORDERCOLORDARK=#FFFFFF bgcolor=#DCC9CA width=140 height=120 Author="wayx">';
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
strFrame+='             Author=meizz align=center><input Author=meizz type=button class=button value=今天 ';
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
		da.borderColorLight="#DCC9CA";
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
					da.borderColorDark="#DCC9CA";
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
					da.borderColorDark="#DCC9CA";
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
					"#FF6666":"#FFCCCC";
			else
			{
				da.style.backgroundColor =(yy==outDate.getFullYear() && mm== outDate.getMonth() + 1 && meizzWDay[i]==outDate.getDate())?
					"#9DD8FF":((yy == new Date().getFullYear() && mm == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate())?
					"#FF6666":"#FFCCCC");
				//将选中的日期显示为凹下去
				if(yy==outDate.getFullYear() && mm== outDate.getMonth() + 1 && meizzWDay[i]==outDate.getDate())
				{
					da.borderColorLight="#FFFFFF";
					da.borderColorDark="#DCC9CA";
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

</script>