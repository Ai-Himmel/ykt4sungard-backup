<%@ page contentType="text/html; charset=GBK"%>
<html>
	<head>
		<title>校园卡务</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css">

		</style>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	
	
	<body scroll="no">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer1">
				<div id="mid_center">
					<ul>                            
                            <li onmouseout="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/yhzza.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/yhzz.gif)"
                            onclick="javascript: window.location='/smartcardweb/translogin.do';"></li>

                           <li onmouseout="this.style.background='url(/smartcardweb/pages/images/yhkye.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/yhkye.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/yhkyea.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/yhkye.gif)"
                            onclick="javascript: window.location='/smartcardweb/bankquerylogin.do';"></li> 

						
					</ul>
				</div>
			</div>
			<div id="Layer3">
				<div id="mid_center">
					<ul>
					   <li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/fhcd.gif)"
							onclick="javascript: window.location='/smartcardweb/index.do';"></li>	
							
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form  method="post" name="logonForm" >
          <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0"></object>
		</form>								
	</body>
</html>
