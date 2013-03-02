<%@ include file="/html/common/init.jsp" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="org.apache.struts.validator.DynaValidatorForm" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.ResultPage" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.CustomerUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.CardUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.DictionaryUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.PostponeUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.PicDelayUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.postpone.EcardPostponeApply" %>
<%@ page import="com.kingstargroup.ecard.hibernate.card.TPifCard" %>
<%@ page import="com.kingstargroup.ecard.hibernate.picdelay.EcardPicDelay" %>
<%@ page import="com.kingstargroup.ecard.hibernate.picdelay.PostponeFiles" %>
<%@ page import="com.kingstargroup.ecard.util.EcardConstants" %>
<%@ page import="com.kingstargroup.ecard.exceptions.ProcessCardLossException" %>
<%@ page import="com.kingstargroup.ecard.exceptions.CardAlreadyOffException" %>
<%@ page import="com.kingstargroup.ecard.exceptions.CardAlreadyLostException" %>
<%@ page import="com.kingstargroup.ecard.exceptions.DBSystemException" %>
<%@ page import="com.kingstargroup.ecard.util.PermissionUtil" %>
<%@ page import="com.kingstargroup.ecard.util.DateFormatUtil" %>
<portlet:defineObjects />
<%
Portlet portlet = PortletServiceUtil.getPortletById(company.getCompanyId(), portletConfig.getPortletName());
%>