<%@page pageEncoding="UTF-8"%>
<%@page import="java.util.List"%>
<%@page import="org.king.topo.domain.MonitorTopoGroupInfo"%>
<%@page import="java.util.HashMap"%>
<%@page import="org.king.topo.domain.MonitorTopoGroupStatistic"%>
<%@page import="org.king.topo.domain.MonitorTopoServerStatistic"%>
<%@page import="org.apache.bcel.classfile.Constant"%>
<%@page import="org.king.utils.Contants"%>
<%@ include file="../tiles/include.jsp"%>
<%@ taglib prefix="aa" uri="http://ajaxanywhere.sourceforge.net/" %>
<html xmlns:v="urn:schemas-microsoft-com:vml" xmlns:o="urn:schemas-microsoft-com:office:office">

	<head>
		<meta http-equiv=Content-Type content="text/html; charset=UTF-8">
		 
		<style>
		v\:* {behavior:url(#default#VML);}
		o\:* {behavior:url(#default#VML);}
		x\:* {behavior:url(#default#VML);}
		.shape {behavior:url(#default#VML);}
		</style>
        <style type="text/css">
            #fixed1{position:fixed;top:0;left:0;z-index:9998}
        </style>

	<link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <link href="<c:url value="/pages/style/default/info.css"/>" type="text/css" rel=stylesheet>
    <link href="<c:url value="/pages/style/default/selfinfo.css"/>" type="text/css" rel=stylesheet>
	<script type="text/javascript" src="<c:url value='/pages/scripts/aa.js'/>" ></script>
	
	 <script type="text/javascript">
     //当前页面的百分比，用于控制页面缩放
     var percentage = 1.0;
	 function showtuna_jmpinfo(tt){
		 if(document.getElementById("hint_"+tt.id)!=null&&document.getElementById("hint_"+tt.id).value!=''){
			var info = document.getElementById("hint_"+tt.id).value;
		 	var ttop = tt.offsetTop*percentage;    //TT控件的定位点高
		    var thei = tt.clientHeight*percentage;    //TT控件本身的高
		    var tleft = tt.offsetLeft*percentage ;    //TT控件的定位点宽
		    while (tt = tt.offsetParent) {
		        ttop += tt.offsetTop*percentage;
		        tleft += tt.offsetLeft*percentage;
		    }
		    document.getElementById("tuna_jmpinfo").style.top = ttop + thei;
		    document.getElementById("tuna_jmpinfo").style.left = tleft;
		    document.getElementById("pubJumInfo_content").innerHTML = info;
		    document.getElementById("tuna_jmpinfo").style.visibility = "visible";		
		 }	   
	 }
	 function showself(){
		    document.getElementById("tuna_jmpinfo").style.visibility = "visible";		
	 }
	 function notshowself(){
		    document.getElementById("tuna_jmpinfo").style.visibility = "hidden";		
	 }
	 function notshowtuna_jmpinfo(){
		    document.getElementById("tuna_jmpinfo").style.visibility = "hidden";		
	 }

	 function self_showtuna_jmpinfo(tt){
			var info = document.getElementById("self_"+tt.id).value;
		 	var ttop = tt.offsetTop*percentage;    //TT控件的定位点高
		    var thei = tt.clientHeight*percentage;    //TT控件本身的高
		    var tleft = tt.offsetLeft*percentage;    //TT控件的定位点宽
		    while (tt = tt.offsetParent) {
		        ttop += tt.offsetTop*percentage;
		        tleft += tt.offsetLeft*percentage;
		    }   
		    document.getElementById("self_tuna_jmpinfo").style.top = ttop + thei;
		    document.getElementById("self_tuna_jmpinfo").style.left = tleft;
		    document.getElementById("self_pubJumInfo_content").innerHTML = info;
		    document.getElementById("self_tuna_jmpinfo").style.visibility = "visible";			   
	 }
     function zoomIn() {
         percentage = percentage - 0.05;
         var total_view = document.getElementById("total_view");
         var titleArea = document.getElementById("titleArea");
         total_view.style.zoom = percentage;
         titleArea.style.zoom = percentage;
     }
     function zoomOut() {
         percentage = percentage + 0.05;
         var total_view = document.getElementById("total_view");
         var titleArea = document.getElementById("titleArea");
         total_view.style.zoom = percentage;
         titleArea.style.zoom = percentage;
     }
     function recoverView() {
         percentage = 1.0;
         var total_view = document.getElementById("total_view");
         var titleArea = document.getElementById("titleArea");
         total_view.style.zoom = 1.0;
         titleArea.style.zoom = 1.0;
     }
     function zoom() {
         //监听键盘，用于实现缩放，S,s为缩小，L,l为放大，回车为原始比例
         var keycode = event.keyCode;
         if(keycode==13){
            recoverView();
         } else {
             var key = String.fromCharCode(keycode);
            if("S"==key || "s"==key){
                zoomIn();
             } else if("L"==key || "l"==key){
                zoomOut();
             }
         }
     }
     document.onkeypress = zoom;

	 function self_showself(){
		    document.getElementById("self_tuna_jmpinfo").style.visibility = "visible";		
	 }
	 function self_notshowself(){
		    document.getElementById("self_tuna_jmpinfo").style.visibility = "hidden";		
	 }
	 function self_notshowtuna_jmpinfo(){
		    document.getElementById("self_tuna_jmpinfo").style.visibility = "hidden";		
	 }

    function go() {
        ajaxAnywhere.getAJAX('showvml.do?method=updateVML');
    }

    ajaxAnywhere.getZonesToReload = function () {
        return "scriptzone"
    };
    function initTimer(){
        window.setTimeout("go();", 15000);
    }
    ajaxAnywhere.onAfterResponseProcessing = function () {
         initTimer();
    }
    function adjustScreen(){
        var wholeFrame = parent.document.getElementById("wholeFrame");
        var contentFrame = parent.document.getElementById("contentFrame");
        var mainFrame = parent.document.getElementById("mainFrame");
        if(wholeFrame.rows=="0,*,0"){
            //recover
            wholeFrame.rows="62,*,30";
            contentFrame.cols="219,*";
            mainFrame.rows="30,*";
        } else {
            //full screen
            wholeFrame.rows="0,*,0";
            contentFrame.cols="0,*";
            mainFrame.rows="0,*";
        }
	}
	</script>
  </head>

    <body scroll=yes onload="go();" ondblclick="adjustScreen();">
     <%
	  	List list = (List)request.getAttribute("vmlList");
	  	String vml_inner = "<?xml:namespace prefix=v />";
	  	String zoomsize ="<v:group style=\"Z-INDEX:2000;POSITION:absolute;WIDTH:100;HEIGHT:100;TOP:0;LEFT:0\" id=total_view coordsize=\"100,100\">";
	  	vml_inner += zoomsize;
	  	String head_vml = request.getAttribute("headVML")==null?"":request.getAttribute("headVML").toString();
	  	vml_inner += head_vml; 
	  	for(int i=0;i<list.size();i++){
	  		MonitorTopoGroupInfo mtgi = (MonitorTopoGroupInfo)list.get(i);
	  		vml_inner += mtgi.getGroupvml();  		
	  	}
	  	String end = "</v:group>";
	  	vml_inner += end;
	  %>
    <form action="showvml.do?method=updateVML" name="main" method="post">
				<div id="vmlinner"><%=vml_inner %></div>
                <table width="100%" height="50" id="titleArea">
                    <tr>
                        <td align="center"  valign="center"><span  style="color:#2E2E2E;font-weight:bold;font-size:20">一卡通设备拓扑图</span></td>
                        <input type="hidden" name="self_head_cutline_1" value="一卡通设备无异常" />
                        <input type="hidden" name="self_head_cutline_2" value="一卡通设备终端异常数量小于5个并且小于总量10%" />
                        <input type="hidden" name="self_head_cutline_3" value="一卡通服务器出现异常或者设备终端异常数量大于5或者大于10%" />
                    </tr>
                </table>
               <aa:zone name="scriptzone">
             	<%
             		if(request.getAttribute("scriptzoneGroup")!=null){
	             		List groupStatisticList = (List)request.getAttribute("scriptzoneGroup");
	             		Integer groupid = -1;
	             		String wordinfo = "";
	             		String div_txtbox ="";
	             		for(int i=0;i<groupStatisticList.size();i++){
	             			MonitorTopoGroupStatistic mtstat = (MonitorTopoGroupStatistic)groupStatisticList.get(i);
	             			String div_stat = "div_stat_"+mtstat.getMonitorTopoDevgroupInfo().getDevicegroupid()+"_"+mtstat.getMonitorTopoDevgroupInfo().getDevphytype()+"_"+mtstat.getMonitorTopoDevgroupInfo().getDevtypecode();
	             			String hintinfo = mtstat.getHintinfo()==null?"":mtstat.getHintinfo();
	             			String div_hint = "hint_div_img_"+mtstat.getMonitorTopoDevgroupInfo().getDevicegroupid()+"_"+mtstat.getMonitorTopoDevgroupInfo().getDevphytype()+"_"+mtstat.getMonitorTopoDevgroupInfo().getDevtypecode();
	             			%>
	             			<input type="hidden" name="<%=div_hint%>" value='<%=hintinfo%>'/>
	             			<%
	             			if(mtstat.getStatus()==0){
	             				%>
            					 <script type="text/javascript">                	
            					 document.getElementById("<%=div_stat%>").src="/monitorsys/pages/images/vml/green.png";
						         </script>
            					<%
	             			}else if(mtstat.getStatus()==1){
	             				%>
	           					 <script type="text/javascript">                	
	           					document.getElementById("<%=div_stat%>").src="/monitorsys/pages/images/vml/yellow.gif";
							     </script>
	           					<%	             			
           					}else if(mtstat.getStatus()==2){
           						%>
	           					 <script type="text/javascript">                	
	           					 document.getElementById("<%=div_stat%>").src="/monitorsys/pages/images/vml/red.gif";
							     </script>
	           					<%           						
           					}
	             			
	             			if(groupid.compareTo(mtstat.getMonitorTopoDevgroupInfo().getDevicegroupid())!=0){
	             				if(groupid!=-1){
	             					%>
	             					 <script type="text/javascript">                	
	             					 document.getElementById("<%=div_txtbox%>").innerHTML="<b>"+"<%=wordinfo%>"+"</b>";
							         </script>
	             					<%
	             				}
	             				wordinfo="";
	             				groupid = mtstat.getMonitorTopoDevgroupInfo().getDevicegroupid();
	             			}
	             			
	             			wordinfo+=mtstat.getWordinfo()+"<br>";
	         				div_txtbox = "div_txtbox_"+groupid;
	         				if(i==groupStatisticList.size()-1){
	         					%>
            					 <script type="text/javascript">           	
				                	document.getElementById("<%=div_txtbox%>").innerHTML="<b>"+"<%=wordinfo%>"+"</b>";
						         </script>
            					<%
	         					
	         				}
	             		}
	             }%>
	             
	             <%if(request.getAttribute("scriptzoneServer")!=null){
	             		List serverStatisticList = (List)request.getAttribute("scriptzoneServer");
	             		for(int j=0;j<serverStatisticList.size();j++){
	             			MonitorTopoServerStatistic mtserverstat = (MonitorTopoServerStatistic)serverStatisticList.get(j);
	             			if(mtserverstat.getMonitorHost().getHostType()!=null){
	             				String serverhintinfo = mtserverstat.getHintinfo()==null?"":mtserverstat.getHintinfo();
	             				HashMap hostType = (HashMap)Contants.HOST_DIV;
	             				String div_hint = "hint_head_img_"+hostType.get(mtserverstat.getMonitorHost().getHostType());
	             				String div_stat = "head_stat_"+hostType.get(mtserverstat.getMonitorHost().getHostType());
            					%>
	             				<input type="hidden" name="<%=div_hint%>" value='<%=serverhintinfo%>'/>
            					<%
		             			if(mtserverstat.getStatus()==0){
		             				%>
	            					 <script type="text/javascript">                	
	            					 document.getElementById("<%=div_stat%>").src="/monitorsys/pages/images/vml/green.png";
							         </script>
	            					<%
		             			}else if(mtserverstat.getStatus()==1){
		             				%>
		           					 <script type="text/javascript">                	
		           					document.getElementById("<%=div_stat%>").src="/monitorsys/pages/images/vml/yellow.gif";
								     </script>
		           					<%	             			
	           					}else if(mtserverstat.getStatus()==2){
	           						%>
		           					 <script type="text/javascript">          	
		           					 document.getElementById("<%=div_stat%>").src="/monitorsys/pages/images/vml/red.gif";
								     </script>
		           					<%           						
	           					}
	             			}
	             			
	             		}
	             }
	            %>
               </aa:zone>
	</form>
	<div style="visible; visibility: hidden; position: absolute; z-index: 20000; display: block; width: 300px; height: 133px;" id="tuna_jmpinfo" onmouseover="showself()" onmouseout="notshowself()">
	<table width="300px" cellspacing="0" cellpadding="0" class="pubJmpInfo_jmpInfo01" id="main">
        <tbody><tr>
            <td class="top_l"></td><td class="top_m"></td><td class="top_r"></td>
        </tr>
        <tr>
            <td class="middle_l"></td>
            <td class="middle_m">
                 <div class="middle_content">
                    <h1 style="background: transparent none repeat scroll 0% 0%; -moz-background-clip: border; -moz-background-origin: padding; -moz-background-inline-policy: continuous;">异常信息</h1>                
                    <div class="pubJmpInfo_horizontal"></div>
                    <div id="pubJumInfo_content"></div>
                 </div>
            </td>
            <td class="middle_r"></td>
        </tr>
        <tr>
            <td class="bottom_l"></td><td class="bottom_m"></td><td class="bottom_r"></td>
        </tr>
    </tbody></table>
</div>
<div style="visible; visibility: hidden; position: absolute; z-index: 20000; display: block; width: 300px; height: 133px;" id="self_tuna_jmpinfo" onmouseover="self_showself()" onmouseout="self_notshowself()">
	<table width="300px" cellspacing="0" cellpadding="0" class="pubJmpInfo_jmpInfo01" id="main">
        <tbody><tr>
            <td class="top_l"></td><td class="top_m"></td><td class="top_r"></td>
        </tr>
        <tr>
            <td class="middle_l"></td>
            <td class="middle_m">
                 <div class="middle_content">
                    <h1 style="background: transparent none repeat scroll 0% 0%; -moz-background-clip: border; -moz-background-origin: padding; -moz-background-inline-policy: continuous;">提示信息</h1>                
                    <div class="pubJmpInfo_horizontal"></div>
                    <div id="self_pubJumInfo_content"></div>
                 </div>
            </td>
            <td class="middle_r"></td>
        </tr>
        <tr>
            <td class="bottom_l"></td><td class="bottom_m"></td><td class="bottom_r"></td>
        </tr>
    </tbody></table>
</div>
  </body>
</html>
