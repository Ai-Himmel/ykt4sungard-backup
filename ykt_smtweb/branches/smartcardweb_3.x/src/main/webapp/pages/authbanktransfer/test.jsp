<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ page import="com.kingstargroup.fdykt.dto.CustomerDTO"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>JavaScript 仿LightBox内容显示效果</title>
<link href="../css/css.css" rel="stylesheet" type="text/css" />
<script language="javascript">
		function MM_swapImgRestore() { //v3.0
		  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
		}
		
		function MM_preloadImages() { //v3.0
		  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
		    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
		    if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
		}
		
		function MM_findObj(n, d) { //v4.01
		  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
		    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
		  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
		  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
		  if(!x && d.getElementById) x=d.getElementById(n); return x;
		}
		
		function MM_swapImage() { //v3.0
		  var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
		   if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
		}
        function addnum(num)
        {
		if(logonForm.all.password.value.length < 6){
			logonForm.all.password.value+=num;
		}
        }
        function cancelnum()
        {
			logonForm.all.password.value=logonForm.all.password.value.substring(0,logonForm.all.password.value.length-1);
        }
        function tab()
        {
            logonForm.all.password.focus();
        }
 	</script>

	<style type="text/css">
		.样式12 {
		font-family: "宋体"; 
		color: #000000; 
		font-size: 16px; 
		}
	</style>
</head>

<body>
<script>

var isIE = (document.all) ? true : false;

var isIE6 = isIE && ([/MSIE (\d)\.0/i.exec(navigator.userAgent)][0][1] == 6);

var $ = function (id) {
	return "string" == typeof id ? document.getElementById(id) : id;
};

var Class = {
	create: function() {
		return function() { this.initialize.apply(this, arguments); }
	}
}

var Extend = function(destination, source) {
	for (var property in source) {
		destination[property] = source[property];
	}
}

var Bind = function(object, fun) {
	return function() {
		return fun.apply(object, arguments);
	}
}

var Each = function(list, fun){
	for (var i = 0, len = list.length; i < len; i++) { fun(list[i], i); }
};

var Contains = function(a, b){
	return a.contains ? a != b && a.contains(b) : !!(a.compareDocumentPosition(b) & 16);
}


var OverLay = Class.create();
OverLay.prototype = {
  initialize: function(options) {

	this.SetOptions(options);
	
	this.Lay = $(this.options.Lay) || document.body.insertBefore(document.createElement("div"), document.body.childNodes[0]);
	
	this.Color = this.options.Color;
	this.Opacity = parseInt(this.options.Opacity);
	this.zIndex = parseInt(this.options.zIndex);
	
	with(this.Lay.style){ display = "none"; zIndex = this.zIndex; left = top = 0; position = "fixed"; width = height = "100%"; }
	
	if(isIE6){
		this.Lay.style.position = "absolute";
		//ie6设置覆盖层大小程序
		this._resize = Bind(this, function(){
			this.Lay.style.width = Math.max(document.documentElement.scrollWidth, document.documentElement.clientWidth) + "px";
			this.Lay.style.height = Math.max(document.documentElement.scrollHeight, document.documentElement.clientHeight) + "px";
		});
		//遮盖select
		this.Lay.innerHTML = '<iframe style="position:absolute;top:0;left:0;width:100%;height:100%;filter:alpha(opacity=0);"></iframe>'
	}
  },
  //设置默认属性
  SetOptions: function(options) {
    this.options = {//默认值
		Lay:		null,//覆盖层对象
		Color:		"#fff",//背景色
		Opacity:	50,//透明度(0-100)
		zIndex:		1000//层叠顺序
    };
    Extend(this.options, options || {});
  },
  //显示
  Show: function() {
	//兼容ie6
	if(isIE6){ this._resize(); window.attachEvent("onresize", this._resize); }
	//设置样式
	with(this.Lay.style){
		//设置透明度
		isIE ? filter = "alpha(opacity:" + this.Opacity + ")" : opacity = this.Opacity / 100;
		backgroundColor = this.Color; display = "block";
	}
  },
  //关闭
  Close: function() {
	this.Lay.style.display = "none";
	if(isIE6){ window.detachEvent("onresize", this._resize); }
  }
};



var LightBox = Class.create();
LightBox.prototype = {
  initialize: function(box, options) {
	
	this.Box = $(box);//显示层
	
	this.OverLay = new OverLay(options);//覆盖层
	
	this.SetOptions(options);
	
	this.Fixed = !!this.options.Fixed;
	this.Over = !!this.options.Over;
	this.Center = !!this.options.Center;
	this.onShow = this.options.onShow;
	
	this.Box.style.zIndex = this.OverLay.zIndex + 1;
	this.Box.style.display = "none";
	
	//兼容ie6用的属性
	if(isIE6){
		this._top = this._left = 0; this._select = [];
		this._fixed = Bind(this, function(){ this.Center ? this.SetCenter() : this.SetFixed(); });
	}
  },
  //设置默认属性
  SetOptions: function(options) {
    this.options = {//默认值
		Over:	true,//是否显示覆盖层
		Fixed:	false,//是否固定定位
		Center:	false,//是否居中
		onShow:	function(){}//显示时执行
	};
    Extend(this.options, options || {});
  },
  //兼容ie6的固定定位程序
  SetFixed: function(){
	this.Box.style.top = document.documentElement.scrollTop - this._top + this.Box.offsetTop + "px";
	this.Box.style.left = document.documentElement.scrollLeft - this._left + this.Box.offsetLeft + "px";
	
	this._top = document.documentElement.scrollTop; this._left = document.documentElement.scrollLeft;
  },
  //兼容ie6的居中定位程序
  SetCenter: function(){
	this.Box.style.marginTop = document.documentElement.scrollTop - this.Box.offsetHeight / 2 + "px";
	this.Box.style.marginLeft = document.documentElement.scrollLeft - this.Box.offsetWidth / 2 + "px";
  },
  //显示
  Show: function(options) {
	//固定定位
	this.Box.style.position = this.Fixed && !isIE6 ? "fixed" : "absolute";

	//覆盖层
	this.Over && this.OverLay.Show();
	
	this.Box.style.display = "block";
	
	//居中
	if(this.Center){
		this.Box.style.top = this.Box.style.left = "50%";
		//设置margin
		if(this.Fixed){
			this.Box.style.marginTop = - this.Box.offsetHeight / 2 + "px";
			this.Box.style.marginLeft = - this.Box.offsetWidth / 2 + "px";
		}else{
			this.SetCenter();
		}
	}
	
	//兼容ie6
	if(isIE6){
		if(!this.Over){
			//没有覆盖层ie6需要把不在Box上的select隐藏
			this._select.length = 0;
			Each(document.getElementsByTagName("select"), Bind(this, function(o){
				if(!Contains(this.Box, o)){ o.style.visibility = "hidden"; this._select.push(o); }
			}))
		}
		//设置显示位置
		this.Center ? this.SetCenter() : this.Fixed && this.SetFixed();
		//设置定位
		this.Fixed && window.attachEvent("onscroll", this._fixed);
	}
	
	this.onShow();
  },
  //关闭
  Close: function() {
	this.Box.style.display = "none";
	this.OverLay.Close();
	if(isIE6){
		window.detachEvent("onscroll", this._fixed);
		Each(this._select, function(o){ o.style.visibility = "visible"; });
	}
  }
};

</script>
			<form action="/smartcardweb/authtransfer.do" method="post"
			name="writeCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/zz.gif" width="314"
									height="82" />
									<input type="hidden" name="org.apache.struts.taglib.Html.TOKEN">
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									  <tr>
                                        <td height="40" class="样式13">
                                           交易参考号
                                        </td>
                                        <td>
                                            
                                        </td>
                                    </tr>
									   <tr>
                                        <td height="40" class="样式13">
                                           银行卡号
                                        </td>
                                        <td>
                                           
                                        </td>
                                    </tr>
									
									<tr>
										<td height="40" class="样式13">
											姓名
										</td>
										<td>
											
										</td>
									</tr>
									
									<tr>
										<td height="40" class="样式13">
											学号
										</td>
										<td>
											
										</td>
									</tr>
									<tr>
                                        <td height="40" class="样式13">
                                           一卡通余额
                                        </td>
                                        <td>
                                            
                                        </td>
                                    </tr>
									<tr>
										<td height="40" class="样式13">
											
										</td>
										<td>
											
										</td>
									</tr>
									
									<tr>
										<td height="80" align="center" class="show" id="errmsg"
											colspan="2">
											<html:errors />请确认放好卡!转账过程可能最多需要等待30秒，请不要轻易移走卡片！
											&nbsp;
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:inputAuthCode();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"
													width="109" height="48" border="0" id="cancel" /> </a>
										</td>
									</tr>
								</table>
							</div>
						</div>
						<div id="content_right"></div>
					</div>
				</div>
			</div>
			<div id="bottom"></div>
			
		</form>
			
					<div id="lightbox" align="center" style="background-color: white;margin-left:auto;">
					<table>
					<tr>
						<td>
							<input name="password" type="password" style="margin-left: 20px;margin-top: 20px;font-size: 24px;font-weight: normal;line-height: normal;" size="12" maxlength="8" />【校验码】	
						</td>
					</tr>
					
					</table>
						<ul>
							<li></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/0.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/0a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/0.gif)"
								onclick="javascript:addnum('0')" ondblclick="javascript:addnum('0')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/1.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/1a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/1.gif)"
								onclick="javascript:addnum('1')" ondblclick="javascript:addnum('1')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/2.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/2a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/2.gif)"
								onclick="javascript:addnum('2')" ondblclick="javascript:addnum('2')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/3.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/3a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/3.gif)"
								onclick="javascript:addnum('3')" ondblclick="javascript:addnum('3')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/4.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/4a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/4.gif)"
								onclick="javascript:addnum('4')" ondblclick="javascript:addnum('4')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/5.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/5a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/5.gif)"
								onclick="javascript:addnum('5')" ondblclick="javascript:addnum('5')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/6.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/6a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/6.gif)"
								onclick="javascript:addnum('6')" ondblclick="javascript:addnum('6')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/7.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/7a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/7.gif)"
								onclick="javascript:addnum('7')" ondblclick="javascript:addnum('7')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/8.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/8a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/8.gif)"
								onclick="javascript:addnum('8')" ondblclick="javascript:addnum('8')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/9.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/9a.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/9.gif)"
								onclick="javascript:addnum('9')" ondblclick="javascript:addnum('9')"></li>
							<li
								onmouseup="this.style.background='url(/smartcardweb/pages/images/del.gif)'"
								onmousedown="this.style.background='url(/smartcardweb/pages/images/dela.gif)'"
								style="cursor:hand; background:url(/smartcardweb/pages/images/del.gif)"
								onclick="javascript:cancelnum()" ondblclick="javascript:cancelnum()"></li>
						</ul>
						<a onclick="javascript:inputAuthCode();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" style="margin-top: 10px"/> </a>
								<a onclick="javascript: window.location='/smartcardweb/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"
													width="109" height="48" border="0" id="cancel" /> </a>
					</div>
<script>

var box = new LightBox("lightbox");


function inputAuthCode (){ 
	box.OverLay.Color = "#000";
	box.Center = true;
	box.Over = true;
	box.OverLay.Opacity = 50;
	box.Fixed = true;
	box.Show(); 
}
</script>

</body>
</html>

