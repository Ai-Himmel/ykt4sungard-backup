<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
    <head>
        <title>校园一卡通考勤管理系统</title>
        <meta http-equiv="Content-Type" content="text/html;">

        <%@ include file="/pages/common/meta.jsp"%>
        <%@ include file="/pages/components/calendar/calendar.jsp"%>
        <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel="stylesheet">
        <link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel="stylesheet">
        <script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
        <%String typename = request.getAttribute("typename").toString();
          String activename =request.getAttribute("activename").toString();
          String noactivename = request.getAttribute("noactivename").toString();
         %>
    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium"><%=typename%> </font> </strong>
        </div>
        <div id="lineDiv" class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine">
                    
                    </td>
                </tr>
            </table>
        </div>
    
        <div id="lineDiv" class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                 <td class="tdborderLine"></td>
                </tr>
            </table>
        </div>
        
         <div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td align="right">
						&nbsp;&nbsp;
						<input name="Submit22" type="button" class="submitButton"
							value="关   闭" onclick="window.close();">
					</td>
				</tr>

			</table>
		</div>
        
        <div id="tableDiv">
            <ec:table items="list" var="classcheckdetail" rowsDisplayed="50" action="dailyclassstudentdetail.do?method=getClassOther">
                <ec:exportXls fileName="classCheckDetailList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="coursename" title="课程" width="100" />
                    <ec:column property="classname" title="班级" width="180" />
                    <ec:column property="stuempno" title="学工号" width="60" />
                    <ec:column property="custname" title="姓名" width="80" />
                    <ec:column property="usedate" title="考勤日期" width="80" />  
                    <ec:column property="checktime" title="刷卡时间" width="150" />                 
                </ec:row>
            </ec:table>
        </div>
        
         <div id="lineDiv" class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine"></td>
                </tr>
                 <div id="titleDiv" class="pageTitle">
                 <strong> <font class="medium"><%=activename%> </font> </strong>
                </div>
                
            </table>
        </div>
        
        <div id="tableDiv">
            <ec:table items="activeList" var="activedetail" rowsDisplayed="10" action="dailyclassstudentdetail.do?method=getClassOther">
                <ec:exportXls fileName="activeDetailList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="id" title="选择" width="50" >
                       <input type="checkbox" name="stu1" value="${activedetail.id}" style="border:0px" />
                     </ec:column>
                    <ec:column property="coursename" title="课程" width="100" />
                    <ec:column property="classname" title="班级" width="180" />
                    <ec:column property="stuempno" title="学工号" width="60" />
                    <ec:column property="custname" title="姓名" width="80" />
                    <ec:column property="checkdate" title="考勤日期" width="80" />  
                    <ec:column property="checktime" title="刷卡时间" width="150" />
                    <ec:column property="isactivate" title="是否有效" width="150" />                 
                </ec:row>
            </ec:table>
        </div>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td align="right">
						&nbsp;&nbsp;
						<input name="Submit22" type="button" class="submitButton"  value="取消确认" onclick="cancel();">
					</td>
				</tr>

			</table>
         <div id="lineDiv" class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine"></td>
                </tr>
                <div id="titleDiv" class="pageTitle">
                 <strong> <font class="medium"><%=noactivename%> </font> </strong>
                </div>
             
            </table>
        </div>
        
        <div id="tableDiv">
            <ec:table items="noactiveList" var="noactivedetail" rowsDisplayed="10" action="dailyclassstudentdetail.do?method=getClassOther">
                <ec:exportXls fileName="noactiveDetailList.xls" tooltip="导出 Excel" />
                <ec:row>
                     <ec:column property="id" title="选择" width="50" >
                       <input type="checkbox" name="stu2" value="${noactivedetail.id}" style="border:0px" />
                     </ec:column>
                    <ec:column property="coursename" title="课程" width="100" />
                    <ec:column property="classname" title="班级" width="180" />
                    <ec:column property="stuempno" title="学工号" width="60" />
                    <ec:column property="custname" title="姓名" width="80" />
                    <ec:column property="checkdate" title="考勤日期" width="80" />  
                    <ec:column property="checktime" title="刷卡时间" width="150" />   
                    <ec:column property="isactivate" title="是否有效" width="150" />                    
                </ec:row>
            </ec:table>
        </div>
          
          <form action="/check/dailyclassstudentdetail.do?method=updateUnplanStudent"  name="studentform" id="studentform"    method="post">
            <input type="hidden" name="student"> 
            <input type="hidden" name="cmd"> 
          </form>  

		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td align="right">
						&nbsp;&nbsp;
						<input name="Submit22" type="button" class="submitButton"  value="确   认" onclick="confirm();">
					</td>
				</tr>

			</table>
		</div>

	</body>
</html>
<script language="javascript">
 function confirmselect(){
		var len = document.getElementsByName("stu2").length; 
        var retstr = ""; 
        for (i = 0; i < len; i++) 
        { 
            if (document.getElementsByName("stu2")[i].checked == true) 
            {   
                retstr = retstr + document.getElementsByName("stu2")[i].value +","; 
            } 
        } 
        return retstr;
 }
  function cancelselect(){
		var len = document.getElementsByName("stu1").length; 
        var retstr = ""; 
        for (i = 0; i < len; i++) 
        { 
            if (document.getElementsByName("stu1")[i].checked == true) 
            {   
                retstr = retstr + document.getElementsByName("stu1")[i].value +","; 
            } 
        } 
        return retstr;
 }
 function confirm(){
     if(confirmselect()==""){
        alert("请选择未确认学生");
        return false;
     }
   	 if(confirmselect()!=""){
   	    document.studentform.student.value=confirmselect();
   	    document.studentform.cmd.value="confirm";
   	 	document.studentform.submit();
   	 }
   }
   function cancel(){
     if(cancelselect()==""){
        alert("请选择已确认学生");
        return false;
     }
   	 if(cancelselect()!=""){
   	    document.studentform.student.value=cancelselect();
   	    document.studentform.cmd.value="cancel";
   	 	document.studentform.submit();
   	 }
   } 
 </script>  