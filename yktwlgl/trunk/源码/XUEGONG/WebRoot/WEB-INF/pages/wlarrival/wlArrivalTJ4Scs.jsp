<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.web.util.Constants"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

		<SCRIPT language=javascript>
function DoExport(){
   wlArrivalDtlSearchForm.action="<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=tj4Scs&doexl=1";
   wlArrivalDtlSearchForm.submit();

}
function DHTJ(){
    wlArrivalDtlSearchForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=tj4Scs";
	wlArrivalDtlSearchForm.submit();
}
function DoView(scsid,dlid,xlid,wlid){
		wlArrivalDtlSearchForm.action="wlArrivalDtlAction4Search.do?method=loadList4TJ&dlid="+dlid+"&xlid="+xlid+"&wlid="+wlid+"&scsid="+scsid;
    	wlArrivalDtlSearchForm.submit();
}

</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" style="padding-left:10px">
		<br>
		<html:form action="/lf/wlArrivalDtlAction4Search" method="post">
		<input type="hidden" name="liSize" value="<%=request.getAttribute("liSize")%>">
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td align="left" valign="top">


						<tr>
							<td height="25" align="left" valign="top">
									<table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr><td width="10" bgcolor="#0066CA">&nbsp;</td>
											<td bgcolor="#0066CA" class="mediumwhite">按生产商统计</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
										</tr>
									</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="center" valign="top">
								<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>

									<tbody>
        <tr align="center" valign="center">
          <td width="13%" class="tableHeader2" >物料大类</td>
          <td width="20%" class="tableHeader3" >
               <html:select property="search_dlid" styleClass="select01" onchange="changeXl(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="dllist" labelProperty="dlmc" property="id" />
               </html:select></td>
          <td width="13%" class="tableHeader2" >物料小类</td>
          <td width="20%" class="tableHeader3" >
               <html:select property="search_xlid" styleClass="select01" onchange="changeWl(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="xllist" labelProperty="xlmc" property="id" />
               </html:select>
          </td>
          <td width="13%" class="tableHeader2" >物料名称</td>
          <td width="20%" class="tableHeader3" >
          	   <html:select property="search_wlid" styleClass="select01">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="wllist" labelProperty="wlmc" property="id" />
               </html:select>
          </td>
        </tr>							
										<tr align="center" valign=center>
										     <td align="left" valign="middle" class="tableHeader2" >生产厂家</td>
          									 <td align="left" valign="middle" class="tableHeader3" >          	   
          											<html:select property="search_producterId" styleClass="select01">
                 									<html:option value="">请选择	</html:option>	
				 									<html:options collection="scslist" labelProperty="companyName" property="id" />
            										</html:select>
            								 </td>
											<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
												登记日期
											</td>
											<td align="left" valign="middle" class="tableHeader3" colspan=3>
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td>
															<html:text property="search_regTimeStart" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectregTimeStart" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="开始日期" style="cursor:pointer">
														</td>
														<td>&nbsp;－&nbsp;</td>
														<td>
															<html:text property="search_regTimeEnd" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectregTimeEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="结束日期" style="cursor:pointer">
														</td>
													</tr>
												</table>
											</td>
											
										</tr>
									</tbody>

								</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<input name="Submit" type="button" class="button_nor" onClick="DHTJ()" value="统 计">
								&nbsp;
								<input name="Submit" type="button" class="button_nor" onClick="DoClear()" value="重 置">
							</td>
						</tr>

						<tr>
							<td height="35" align="center" valign="middle" class="mediumblack">
								按生产商统计列表
							</td>
						</tr>
								      <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         <a href="javascript:DoExport()"><IMG src="<c:url value="/pages/style/default/images/xls.gif"/>" border="0"></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      
      </td>
      </tr> 
						<tr>
       <td height="24" align="center" valign="middle"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#3F738B bordercolordark=#ffffff id=maintable>
          <tbody>
            <tr align="center" valign=center>
              <td valign="middle" class="tableHeader" >生产厂商</td>
              <td valign="middle" class="tableHeader" >物料大类</td>
              <td valign="middle" class="tableHeader" >物料小类</td>
              <td valign="middle" class="tableHeader" >物料名称</td>             
              <td valign="middle" class="tableHeader" >到货数量</td>
              <%if(request.getAttribute("ifLimit").equals("0")){%>
              <td valign="middle" class="tableHeader" >到货金额</td>        
              <%}%>
            </tr>           
            <logic:present name="tjList" scope="request">   
            <logic:iterate name="tjList" id="tj" type="java.util.Map"  indexId="i">
            <tr align="center" valign="middle" bgcolor="#F6F4F5">
              <td align="center" valign="middle" ><bean:write name="tj" property="companyName" />&nbsp;</td>
              <td align="center" valign="middle" ><input type=hidden name="a2" value="<bean:write name="tj" property="companyName" />"><bean:write name="tj" property="dlmc" />&nbsp;</td>
              <td align="center" valign="middle" ><input type=hidden name="a3" value="<bean:write name="tj" property="companyName" />"><input type=hidden name="b3" value="<bean:write name="tj" property="dlmc" />"><bean:write name="tj" property="xlmc" />&nbsp;</td>
              <td align="center" valign="middle" ><bean:write name="tj" property="wlmc"/>&nbsp;</td>
              <td align="center" valign="middle" >
              <a href="javascript:DoView('<bean:write name="tj" property="scsid" />','<bean:write name="tj" property="dlid" />','<bean:write name="tj" property="xlid" />','<bean:write name="tj" property="wlid"/>')"><bean:write name="tj" property="wlArrivalNum" /></a>&nbsp;
              </td>
              <%if(request.getAttribute("ifLimit").equals("0")){%>
              <td align="center" valign="middle" ><bean:write name="tj" property="wlArrivalPrice" />&nbsp;</td>
              <%} %>
            </tr>                       
            </logic:iterate>
            </logic:present>
            <logic:present name="tjTotal" scope="request">
            <logic:iterate name="tjTotal" id="tjt" type="java.util.Map">
            <tr height="26" align="center" valign="middle" bgcolor="#FF9999" style="font-weight:bold"> 
              <td align="center" valign="middle" >总 计</td>
              <td align="center" valign="middle" >--</td>
              <td align="center" valign="middle" >--</td>
              <td align="center" valign="middle" >--</td>
              <td align="center" valign="middle" ><bean:write name="tjt" property="wlArrivalNum" />&nbsp;
              </td>
              <%if(request.getAttribute("ifLimit").equals("0")){%>
              <td align="center" valign="middle" ><bean:write name="tjt" property="wlArrivalPrice" />&nbsp;</td>
              <%} %>
            </tr>
            </logic:iterate> 
           </logic:present>              
          </tbody>
        </table></td>
						</tr>
						<tr>
						        <td><table width="100%" border="0">
		</table></td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
						</html:form>
	</body>

</html>
<script>
	var idcount=0;
    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("dxlist")!=null)
       resultset=(String[][])request.getAttribute("dxlist");//读取大小类对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应小类id、小类名称、大类id
     <%
     }
   }
   %>
   datacount=<%=count%>;

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("xmlist")!=null)
       resultset2=(String[][])request.getAttribute("xmlist");//读取小类、名称对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//产生javascript二维数组，对应名称id、物料名称、物料单位、小类id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>
<script>
function DoClear(){
    document.wlArrivalDtlSearchForm.elements["search_dlid"].value="";
    document.wlArrivalDtlSearchForm.elements["search_xlid"].value="";
    document.wlArrivalDtlSearchForm.elements["search_wlid"].value="";
    document.wlArrivalDtlSearchForm.elements["search_producterId"].value="";
    document.wlArrivalDtlSearchForm.elements["search_regTimeStart"].value="";
    document.wlArrivalDtlSearchForm.elements["search_regTimeEnd"].value="";
}

setTimeout('DoInit()',30);
function DoInit(){
  var dl,xl,wl,dept,wxs,uc,ifap,j;

     var dllist = document.wlArrivalDtlSearchForm.elements["search_dlid"];
     var xllist = document.wlArrivalDtlSearchForm.elements["search_xlid"];
     var wllist = document.wlArrivalDtlSearchForm.elements["search_wlid"];
     dl = dllist.options[dllist.selectedIndex].value;
     xl = xllist.options[xllist.selectedIndex].value;
     wl = wllist.options[wllist.selectedIndex].value;


   if(dl!="")
      changeXl(dllist);
   for(j=0;j<xllist.length;j++){
      if(xllist[j].value==xl)
	     xllist[j].selected=true;
   }		 
   
   if(xl!="")
        changeWl(xllist);
   for(j=0;j<wllist.length;j++){
      if(wllist[j].value==wl)
	     wllist[j].selected=true;
   }
   
   if(wl!="")
       changeDW(wllist);
        if(document.all.maintable!=null)
      uniteTable(document.all.maintable,3);

}

function uniteTable(thistab,colLength){
var rn = thistab.rows.length;
var rowspann=0;
for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列
	for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查
		if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText&&thistab.rows[i].cells[j].colSpan==thistab.rows[i-1].cells[j].colSpan){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。
			if(thistab.rows[i].cells[j].children(0)!=null&&thistab.rows[i].cells[j].children(0).value==thistab.rows[i-1].cells[j].children(0).value){//把前面一列的值放入隐藏域里,如果隐藏域有值就判断是否与上一行的值一样如果一样就合计当前行的合并行数，并删除当前行。

				rowspann+=thistab.rows[i].cells[j].rowSpan;
				thistab.rows[i].deleteCell(j);
			}else if(thistab.rows[i].cells[j].children(0)==null){//如果隐藏域无值即象第一列那样就只管合并即可
				rowspann+=thistab.rows[i].cells[j].rowSpan;
				thistab.rows[i].deleteCell(j);
			}else{
				thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
				rowspann=0;
			}
		}else{
			thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
			rowspann=0;
		}
		//检测无表头的表
		if(i==0&&rowspann>0){
			thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
			rowspann=0;
		}
	}
}
}
function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   

   document.wlArrivalDtlSearchForm.elements["search_xlid"].length=1; //清空原小类列表

   document.wlArrivalDtlSearchForm.elements["search_wlid"].length=1; //清空原名称列表      


   if(id!="")
                 
      for (i=0;i < datacount; i++)
      {

         if (dataset[i][2] == id)
          {   

             document.wlArrivalDtlSearchForm.elements["search_xlid"].options[document.wlArrivalDtlSearchForm.elements["search_xlid"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.wlArrivalDtlSearchForm.elements["search_xlid"].options[document.wlArrivalDtlSearchForm.elements["search_xlid"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   xllist = document.wlArrivalDtlSearchForm.elements["search_xlid"];

}

function changeWl(sel){
   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   document.wlArrivalDtlSearchForm.elements["search_wlid"].length=1; //清空原名称列表        
   
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.wlArrivalDtlSearchForm.elements["search_wlid"].options[document.wlArrivalDtlSearchForm.elements["search_wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
      
       for (i=0;i < datacount2; i++)
      {
          document.wlArrivalDtlSearchForm.elements["search_wlid"].options[document.wlArrivalDtlSearchForm.elements["search_wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   wllist = document.wlArrivalDtlSearchForm.elements["search_wlid"];

}
</script>
<script type="text/javascript">
    new calendar("search_regTimeStart", "selectregTimeStart", "%Y-%m-%d");
    new calendar("search_regTimeEnd", "selectregTimeEnd", "%Y-%m-%d");
</script>
