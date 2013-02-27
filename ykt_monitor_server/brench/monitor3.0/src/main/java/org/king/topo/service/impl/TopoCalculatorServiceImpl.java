package org.king.topo.service.impl;

import java.text.ParseException;
import java.util.HashMap;
import java.util.List;

import org.king.host.dao.MonitorHostDAO;
import org.king.host.domain.MonitorHost;
import org.king.host.domain.MonitorHostStatus;
import org.king.hostservice.dao.MonitorServiceDAO;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.domain.MonitorServiceStatus;
import org.king.monitor.domain.TDevice;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.topo.dao.MonitorTopoDevgroupInfoDAO;
import org.king.topo.dao.MonitorTopoDeviceDicDAO;
import org.king.topo.dao.MonitorTopoDeviceGroupDAO;
import org.king.topo.dao.MonitorTopoGroupDAO;
import org.king.topo.dao.MonitorTopoGroupInfoDAO;
import org.king.topo.dao.MonitorTopoGroupStatisticDAO;
import org.king.topo.dao.MonitorTopoLocationDAO;
import org.king.topo.dao.MonitorTopoServerStatisticDAO;
import org.king.topo.domain.MonitorTopoDevgroupInfo;
import org.king.topo.domain.MonitorTopoDeviceDic;
import org.king.topo.domain.MonitorTopoGroup;
import org.king.topo.domain.MonitorTopoGroupInfo;
import org.king.topo.domain.MonitorTopoGroupStatistic;
import org.king.topo.domain.MonitorTopoLocation;
import org.king.topo.domain.MonitorTopoServerStatistic;
import org.king.topo.service.TopoCalculatorService;
import org.king.utils.DateUtil;

public class TopoCalculatorServiceImpl implements TopoCalculatorService {
	private MonitorTopoDevgroupInfoDAO monitorTopoDevgroupInfoDAO;
	private MonitorTopoDeviceDicDAO monitorTopoDeviceDicDAO;
	private MonitorTopoDeviceGroupDAO monitorTopoDeviceGroupDAO;
	private MonitorTopoLocationDAO monitorTopoLocationDAO;
	private MonitorTopoGroupDAO monitorTopoGroupDAO;
	private MonitorTopoGroupInfoDAO monitorTopoGroupInfoDAO;
	private MonitorTopoGroupStatisticDAO monitorTopoGroupStatisticDAO;
	private MonitorTopoServerStatisticDAO monitorTopoServerStatisticDAO;
	private MonitorHostDAO monitorHostDAO; 
	private MonitorServiceDAO monitorServiceDAO;

	public void setMonitorTopoGroupDAO(MonitorTopoGroupDAO monitorTopoGroupDAO) {
		this.monitorTopoGroupDAO = monitorTopoGroupDAO;
	}

	public void setMonitorTopoDevgroupInfoDAO(
			MonitorTopoDevgroupInfoDAO monitorTopoDevgroupInfoDAO) {
		this.monitorTopoDevgroupInfoDAO = monitorTopoDevgroupInfoDAO;
	}

	public void setMonitorTopoDeviceDicDAO(
			MonitorTopoDeviceDicDAO monitorTopoDeviceDicDAO) {
		this.monitorTopoDeviceDicDAO = monitorTopoDeviceDicDAO;
	}

	public void setMonitorTopoDeviceGroupDAO(
			MonitorTopoDeviceGroupDAO monitorTopoDeviceGroupDAO) {
		this.monitorTopoDeviceGroupDAO = monitorTopoDeviceGroupDAO;
	}

	public void setMonitorTopoLocationDAO(
			MonitorTopoLocationDAO monitorTopoLocationDAO) {
		this.monitorTopoLocationDAO = monitorTopoLocationDAO;
	}

	public void setMonitorTopoGroupInfoDAO(
			MonitorTopoGroupInfoDAO monitorTopoGroupInfoDAO) {
		this.monitorTopoGroupInfoDAO = monitorTopoGroupInfoDAO;
	}

	public void setMonitorTopoGroupStatisticDAO(
			MonitorTopoGroupStatisticDAO monitorTopoGroupStatisticDAO) {
		this.monitorTopoGroupStatisticDAO = monitorTopoGroupStatisticDAO;
	}
	

	public void setMonitorTopoServerStatisticDAO(
			MonitorTopoServerStatisticDAO monitorTopoServerStatisticDAO) {
		this.monitorTopoServerStatisticDAO = monitorTopoServerStatisticDAO;
	}

	public void setMonitorHostDAO(MonitorHostDAO monitorHostDAO) {
		this.monitorHostDAO = monitorHostDAO;
	}

	public void setMonitorServiceDAO(MonitorServiceDAO monitorServiceDAO) {
		this.monitorServiceDAO = monitorServiceDAO;
	}

	public void calculateDevgroupInfo() {
		try {
			 List statList =  monitorTopoGroupStatisticDAO.getAll();
		        for (int i = 0; i < statList.size(); i++) {
		            monitorTopoGroupStatisticDAO.delete((MonitorTopoGroupStatistic)statList.get(i));
		        }

				List devgrouInfoList = monitorTopoDevgroupInfoDAO.getAll();
				for(int i=0;i<devgrouInfoList.size();i++){
					monitorTopoDevgroupInfoDAO.delete((MonitorTopoDevgroupInfo)devgrouInfoList.get(i));
				}
				String query = "select new map(a.id.devicegroupid as devicegroupid,b.devphytype as devphytype," +
						"b.devtypecode as devtypecode,count(a.id.deviceid) as devtypenum," +
						"to_char(sysdate,'YYYYMMDDHH24miss') as lastupdate) from MonitorTopoDeviceGroup a,TDevice b " +
						"where a.id.deviceid=b.deviceid group by a.id.devicegroupid,b.devphytype,b.devtypecode " +
						"order by a.id.devicegroupid,b.devtypecode";
				List countList = monitorTopoDeviceGroupDAO.find(query);
				for(int j=0;j<countList.size();j++){
					HashMap info = (HashMap)countList.get(j);
					MonitorTopoDevgroupInfo mtdevgroupinfo = new MonitorTopoDevgroupInfo();
					mtdevgroupinfo.setDevicegroupid(Integer.valueOf(info.get("devicegroupid").toString()));
					mtdevgroupinfo.setDevphytype(Integer.valueOf(info.get("devphytype").toString()));
					mtdevgroupinfo.setDevtypecode(info.get("devtypecode").toString());
					mtdevgroupinfo.setDevtypenum(Integer.valueOf(info.get("devtypenum").toString()));
					mtdevgroupinfo.setLastupdate(DateUtil.getNow());			
					monitorTopoDevgroupInfoDAO.save(mtdevgroupinfo);			
				}
				calculateTopoGroupStatistic(0);
		} catch (Exception e) {
			e.printStackTrace();
		}
       
		
	}
	
	public void calculateTopoServerStatistic(int param){
		if(param==0){
			List statList =  monitorTopoServerStatisticDAO.getAll();
			for (int i = 0; i < statList.size(); i++) {
				monitorTopoServerStatisticDAO.delete((MonitorTopoServerStatistic)statList.get(i));
			}
		}
		List hostchecklist = monitorHostDAO.find("from MonitorHostchecks where endTime>(select max(lastupdate) from MonitorTopoServerStatistic)");
		List servicechecklist = monitorServiceDAO.find("from MonitorServiceCheck where endTime>(select max(lastupdate) from MonitorTopoServerStatistic)");
		List staticList = monitorTopoServerStatisticDAO.getAll();
		if((hostchecklist!=null&&hostchecklist.size()>0)||(servicechecklist!=null&&servicechecklist.size()>0)||staticList==null||staticList.size()==0){
			int flag = 0;
			List hostlist = monitorHostDAO.find("from MonitorHost where hostType not in('11','12')");
			for(int i=0;i<hostlist.size();i++){
				MonitorHost mh = (MonitorHost)hostlist.get(i);
				MonitorTopoServerStatistic mtserverstat = null;
				try {
					mtserverstat = monitorTopoServerStatisticDAO.get(mh.getHostId());
				} catch (Exception e) {
					// TODO: handle exception
				}
				
				List hoststatList = monitorHostDAO.find("from MonitorHostStatus where hostId="+mh.getHostId()+" and currentState>0 ");
				if(mtserverstat==null){
					mtserverstat = new MonitorTopoServerStatistic();
					mtserverstat.setMonitorHost(mh);	
					flag=0;
				}else{
					flag=1;
				}
				String hintinfo = "";
				mtserverstat.setStatus(0);
				if(hoststatList!=null&&hoststatList.size()>0){
					MonitorHostStatus mhs = (MonitorHostStatus)hoststatList.get(0);
					hintinfo += "<font color=\"red\" align=\"left\">"+mh.getDisplayName()+"\t"+mh.getHostAddress()+"\t"+mhs.getOutput()+"</font><br>";
					mtserverstat.setStatus(2);
				}else{
					List serviceList = monitorServiceDAO.find("select b from MonitorService a,MonitorServiceStatus b where a.serviceId=b.serviceId and a.monitorHost.hostId="+mh.getHostId()+" and b.currentState>0");
					if(serviceList!=null&&serviceList.size()>0){
						for(int j=0;j<serviceList.size();j++){
							MonitorServiceStatus mss = (MonitorServiceStatus)serviceList.get(j);
							MonitorService ms = monitorServiceDAO.get(mss.getServiceId());
							if(j<=9){
								hintinfo += "<font color=\"red\" align=\"left\">"+mh.getDisplayName()+"\t"+ms.getServiceName()+"\t"+mh.getHostAddress()+"\t"+mss.getOutput()+"</font><br>";
							}
						}
						if(serviceList.size()>2){
							mtserverstat.setStatus(2);
						}else{
							mtserverstat.setStatus(1);
						}
					}
				}
				mtserverstat.setHintinfo(hintinfo);
				mtserverstat.setLastupdate(DateUtil.getNow());
				if(flag==0){
					monitorTopoServerStatisticDAO.save(mtserverstat);
				}else{
					monitorTopoServerStatisticDAO.update(mtserverstat);
				}
			}
		}
	}

	public void calculateTopoGroupStatistic(int param) {
		//
		try {
			if(param==0){
				List statList =  monitorTopoGroupStatisticDAO.getAll();
				for (int i = 0; i < statList.size(); i++) {
					monitorTopoGroupStatisticDAO.delete((MonitorTopoGroupStatistic)statList.get(i));
				}
			}
			
			List devgroupinfoList = monitorTopoDevgroupInfoDAO.getAll();
			for (int i = 0; i < devgroupinfoList.size(); i++) {
				int flag = 0;
				MonitorTopoDevgroupInfo mtdevgroupinfo = (MonitorTopoDevgroupInfo) devgroupinfoList
						.get(i);
				MonitorTopoDeviceDic mtdic = monitorTopoDeviceDicDAO.findDictByTypecode(mtdevgroupinfo.getDevphytype(), mtdevgroupinfo.getDevtypecode());
				if(mtdic==null){
					//字典沒有配置略去
					continue;
				}
				MonitorTopoGroupStatistic mtgs = null;
				try {
					 mtgs = monitorTopoGroupStatisticDAO.get(mtdevgroupinfo.getId());
				} catch (Exception e) {
					// TODO: handle exception
				}
				
				if (mtgs == null) {
					mtgs = new MonitorTopoGroupStatistic();
					mtgs.setMonitorTopoDevgroupInfo(mtdevgroupinfo);
					flag =0;
				}else{
					flag =1;
				}
				mtgs.setLastupdate(DateUtil.getNow());
				if ("0010".equals(mtdevgroupinfo.getDevtypecode())
						|| "0020".equals(mtdevgroupinfo.getDevtypecode())
						|| "5301".equals(mtdevgroupinfo.getDevtypecode())
						|| "5302".equals(mtdevgroupinfo.getDevtypecode())) {
					//服务器类型
					//host,hostservice
					String hostquery="select s from MonitorTopoDevgroupInfo a,TDevice b,MonitorTopoDeviceGroup c,MonitorHostStatus s," +
							"MonitorHostAll h where a.devtypecode=b.devtypecode and a.devphytype=b.devphytype " +
							"and a.devicegroupid=c.id.devicegroupid and c.id.deviceid=b.deviceid " +
							"and b.ip=h.hostAddress and s.hostId=h.hostId and s.currentState>0 " +
							"and (h.checkFlag is null or h.checkFlag=1) and a.devicegroupid="+mtdevgroupinfo.getDevicegroupid();
					String hosts_str="";
					List hostqueryList = monitorTopoGroupStatisticDAO.find(hostquery);
					if(hostqueryList!=null){
						int errs = hostqueryList.size();						
						if(errs>0){
							mtgs.setStatus(2);
							String wordinfo = mtdic.getDevtypename()+":"+errs+"/"+mtdevgroupinfo.getDevtypenum();
							mtgs.setWordinfo(wordinfo);
							String hintinfo = "";
							for(int j=0;j<hostqueryList.size();j++){
								MonitorHostStatus mthoststatus = (MonitorHostStatus)hostqueryList.get(j);
								MonitorHost mh = monitorHostDAO.get(mthoststatus.getHostId());
								hosts_str +=mh.getHostId()+",";
								if(j<=9){
									hintinfo += "<font color=\"red\" align=\"left\">"+mh.getDisplayName()+"\t"+mh.getHostAddress()+"\t"+mthoststatus.getOutput()+"</font><br>";
								}
								if(j==9){
									if(hostqueryList.size()>9){
										hintinfo+="<font align=\"right\"><a herf=\"#\" target=\"_blank\">more..</a></font>";
									}									
								}
							}
							mtgs.setHintinfo(hintinfo);
						}else{
							mtgs.setStatus(0);
							String wordinfo = mtdic.getDevtypename()+":0/"+mtdevgroupinfo.getDevtypenum();
							mtgs.setWordinfo(wordinfo);
							mtgs.setHintinfo("");
						}
					}else{
						mtgs.setStatus(0);
						String wordinfo = mtdic.getDevtypename()+":0/"+mtdevgroupinfo.getDevtypenum();
						mtgs.setWordinfo(wordinfo);
						mtgs.setHintinfo("");
					}
					
					String serviceQuery="select s from MonitorTopoDevgroupInfo a,TDevice b,MonitorTopoDeviceGroup c,MonitorServiceStatus s," +
							"MonitorService h where a.devtypecode=b.devtypecode and a.devphytype=b.devphytype " +
							"and a.devicegroupid=c.id.devicegroupid and c.id.deviceid=b.deviceid " +
							"and b.ip=h.monitorHost.hostAddress and s.serviceId=h.serviceId " +
							"and h.monitorHost.hostId not in("+hosts_str+"-1) and s.currentState>0 and a.devicegroupid="+mtdevgroupinfo.getDevicegroupid();
					List servicequeryList = monitorTopoGroupStatisticDAO.find(serviceQuery);
					if(servicequeryList!=null){
						int errs = servicequeryList.size();					
						if(errs>0){
							mtgs.setStatus(2);
								String wordinfo = mtdic.getDevtypename()+":"+errs+"/"+mtdevgroupinfo.getDevtypenum();
								mtgs.setWordinfo(wordinfo);
								String hintinfo = "";
								for(int j=0;j<servicequeryList.size();j++){
									MonitorServiceStatus mtservicetatus = (MonitorServiceStatus)servicequeryList.get(j);
									MonitorService ms = monitorServiceDAO.get(mtservicetatus.getServiceId());
									if(j<=9){
										hintinfo += "<font color=\"red\" align=\"left\">"+ms.getMonitorHost().getDisplayName()+"\t"+ms.getMonitorHost().getHostAddress()+"\t"+mtservicetatus.getOutput()+"</font><br>";
									}
									if(j==9){
										if(hostqueryList.size()>9){
											hintinfo+="<font align=\"right\"><a herf=\"#\" target=\"_blank\">more..</a></font>";
										}									
									}
								}
								mtgs.setHintinfo(hintinfo);
						}else{
							mtgs.setStatus(0);
							String wordinfo = mtdic.getDevtypename()+":0/"+mtdevgroupinfo.getDevtypenum();
							mtgs.setWordinfo(wordinfo);
							mtgs.setHintinfo("");
						}
					}else{
						mtgs.setStatus(0);
						String wordinfo = mtdic.getDevtypename()+":0/"+mtdevgroupinfo.getDevtypenum();
						mtgs.setWordinfo(wordinfo);
						mtgs.setHintinfo("");
					}
				}else{
					//普通设备
					String termdevQuery="select s from MonitorTopoDevgroupInfo a,TDevice b,MonitorTopoDeviceGroup c,MonitorTermdeviceStatus s " +
							"where a.devtypecode=b.devtypecode and a.devphytype=b.devphytype " +
							"and a.devicegroupid=c.id.devicegroupid and c.id.deviceid=b.deviceid " +
							"and b.deviceid=s.deviceId and s.currentState>0 and a.devicegroupid="+mtdevgroupinfo.getDevicegroupid();
					List termdevList = monitorTopoGroupStatisticDAO.find(termdevQuery);
					if(termdevList!=null){
						int errs = termdevList.size();					
						if(errs>0){
							mtgs.setStatus(1);
								String wordinfo = mtdic.getDevtypename()+":"+errs+"/"+mtdevgroupinfo.getDevtypenum();
								mtgs.setWordinfo(wordinfo);							
							String hintinfo = "";
							for(int j=0;j<termdevList.size();j++){
								if(termdevList.size()>5&&mtdevgroupinfo.getDevtypenum()>0&&termdevList.size()*100/mtdevgroupinfo.getDevtypenum()>10){
									mtgs.setStatus(2);
								}
								MonitorTermdeviceStatus mttdstatus = (MonitorTermdeviceStatus)termdevList.get(j);
								TDevice device = monitorTopoGroupStatisticDAO.getDevice((long)mttdstatus.getDeviceId());
								String intervaltime;
								try {
									intervaltime = DateUtil.convertTime(mttdstatus.getLastStateChange());
								} catch (ParseException e) {
									// TODO Auto-generated catch block
									intervaltime = "";
								}
								if(j<=9){
									hintinfo += "<font color=\"red\" align=\"left\">"+device.getDevicename()+"\t"+intervaltime+"\t"+mttdstatus.getOutput()+"</font><br>";
								}
								if(j==9){
									if(termdevList.size()>9){
										hintinfo+="<font align=\"right\"><a herf=\"#\" target=\"_blank\">more..</a></font>";
									}									
								}
							}
							mtgs.setHintinfo(hintinfo);
						}else{
							mtgs.setStatus(0);
							String wordinfo = mtdic.getDevtypename()+":0/"+mtdevgroupinfo.getDevtypenum();
							mtgs.setWordinfo(wordinfo);
							mtgs.setHintinfo("");
						}
					}else{
						mtgs.setStatus(0);
						String wordinfo = mtdic.getDevtypename()+":0/"+mtdevgroupinfo.getDevtypenum();
						mtgs.setWordinfo(wordinfo);
						mtgs.setHintinfo("");
					}
				}
				
				if(flag==0){
					monitorTopoGroupStatisticDAO.save(mtgs);
				}else{
					monitorTopoGroupStatisticDAO.update(mtgs);
				}

			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.service.TopoCalculatorService#calculateDivHtml()
	 */
	public void calculateDivHtml() {
		
		try{
			String basicVML = "<v:group id=\"group_groupid\" style=\"position:absolute;left:group_left;top:group_top;z-index:1000;width:100;height:100\" coordsize=\"100,100\">"
				+ "<v:roundrect style=\"Z-INDEX:1000;WIDTH:rect_width;HEIGHT:rect_height;TOP:rect_top;LEFT:rect_left\" id=div_rect arcsize=\"1311f\" fillcolor=\"#d6ffd6\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:1002;TOP:line_top;LEFT:line_left\" id=div_line from=\"0,0\" to=\"line_width,0\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:roundrect style=\"Z-INDEX:1001;WIDTH:groupname_width;HEIGHT:30;TOP:groupname_top;LEFT:groupname_left\" arcsize=\"1311f\" fillcolor=\"#d6ffd6\" strokecolor=\"#d6ffd6\" strokeweight=\".5pt\">"
				+ "<v:Textbox style=\"TEXT-ALIGN:center;FONT-FAMILY:宋体;COLOR:#000000;FONT-SIZE:15;WORD-BREAK:break-all;\" id=div_groupname inset=\"0pt,5pt,0pt,5pt\" print=\"t\"><b>group_name</b></v:Textbox></v:roundrect>"
				+ "<v:Image style=\"Z-INDEX:1003;WIDTH:49;HEIGHT:21;TOP:exchange_top;LEFT:exchange_left\" id=div_exchange src=\"/monitorsys/pages/images/vml/exchange.png\" bilevel=\"f\"/>"
				+ "<v:roundrect style=\"Z-INDEX:1004;WIDTH:txtbox_width;HEIGHT:txtbox_height;TOP:txtbox_top;LEFT:txtbox_left\" arcsize=\"4321f\" fillcolor=\"#d6ffd6\" strokecolor=\"#d6ffd6\" strokeweight=\".5pt\">"
				+ "<v:Textbox style=\"TEXT-ALIGN:left;FONT-FAMILY:宋体;COLOR:#bd231b;FONT-SIZE:12;WORD-BREAK:break-all;\" id=div_txtbox inset=\"5pt,0pt,5pt,0pt\" print=\"t\"><b>txtbox_info</b></v:Textbox></v:roundrect>";
		String imageVML = "<v:Image style=\"Z-INDEX:1005;WIDTH:img_width;HEIGHT:img_height;TOP:img_top;LEFT:img_left\" id=div_img onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"img_path\" bilevel=\"f\"/>";
		String statimageVML = "<v:Image style=\"Z-INDEX:1006;WIDTH:18;HEIGHT:18;TOP:img_top;LEFT:img_left\" id=div_stat src=\"/monitorsys/pages/images/vml/green.png\" bilevel=\"f\"/>";
		String lineVML = "<v:line style=\"Z-INDEX:1001;TOP:line_top;LEFT:line_left\" id=type_line from=\"0,0\" to=\"line_width,line_height\" strokecolor=\"black\" strokeweight=\"1px\"/>";
		String endVML = "</v:group>";
		String imgPath = "/monitorsys/pages/images/vml/";
		List groupinfoList = monitorTopoGroupInfoDAO.getAll();
		for (int i = 0; i < groupinfoList.size(); i++) {
			monitorTopoGroupInfoDAO.delete((MonitorTopoGroupInfo) groupinfoList
					.get(i));
		}

		List groupList = monitorTopoGroupDAO.getAllTopoGroupWithLocationOrder();
		for (int j = 0; j < groupList.size(); j++) {
			String tempVML = basicVML;
			MonitorTopoGroup mtgroup = (MonitorTopoGroup) groupList.get(j);

			Integer devgroupid = mtgroup.getDevicegroupid();
			// 各组件id
			String group_groupid = "group_" + devgroupid;
			String div_rect = "div_rect_" + devgroupid;
			String div_line = "div_line_" + devgroupid;
			String div_groupname = "div_groupname_" + devgroupid;
			String div_exchange = "div_exchange_" + devgroupid;
			String div_txtbox = "div_txtbox_" + devgroupid;
			// 组别名称
			String group_name = mtgroup.getDevicegroupname();

			tempVML = tempVML.replaceAll("group_groupid", String
					.valueOf(group_groupid));
			tempVML = tempVML.replaceAll("div_rect", String.valueOf(div_rect));
			tempVML = tempVML.replaceAll("div_line", String.valueOf(div_line));
			tempVML = tempVML.replaceAll("div_groupname", String
					.valueOf(div_groupname));
			tempVML = tempVML.replaceAll("div_exchange", String
					.valueOf(div_exchange));
			tempVML = tempVML.replaceAll("div_txtbox", String
					.valueOf(div_txtbox));
			tempVML = tempVML.replaceAll("group_name", String
					.valueOf(group_name));

			//
			String txtbox_info = "";
			List devgroupinfoList = monitorTopoDevgroupInfoDAO
					.getDevgroupInfoByGroupid(devgroupid);
			for (int k = 0; k < devgroupinfoList.size(); k++) {
				MonitorTopoDevgroupInfo mtdevgroupinfo = (MonitorTopoDevgroupInfo) devgroupinfoList
						.get(k);
				MonitorTopoDeviceDic mtdic = monitorTopoDeviceDicDAO
						.findDictByTypecode(mtdevgroupinfo.getDevphytype(),
								mtdevgroupinfo.getDevtypecode());
				if(mtdic!=null){
					txtbox_info += mtdic.getDevtypename() + ": 0/0<br>";
				}else{
					txtbox_info += "未知设备: 0/0<br>";
				}
			}

			int rect_width = 120;
			int rect_height = 240;
			int rect_top = 0;
			int rect_left = 0;
			int txtbox_height = 68;

			int devgroupsize = devgroupinfoList.size();
			switch (devgroupsize) {
			case 0:
			case 1:
				rect_width = 120;
				for (int k = 0; k < devgroupinfoList.size(); k++) {
					String tempImgVML = "";
					String tempLineVML = "";
					MonitorTopoDevgroupInfo mtdevgroupinfo = (MonitorTopoDevgroupInfo) devgroupinfoList
							.get(k);
					MonitorTopoDeviceDic mtdic = monitorTopoDeviceDicDAO
							.findDictByTypecode(mtdevgroupinfo.getDevphytype(),
									mtdevgroupinfo.getDevtypecode());
					if (mtdic != null) {
						tempImgVML += imageVML;
						tempImgVML += statimageVML;
						tempImgVML = tempImgVML.replaceAll("img_width", String
								.valueOf(mtdic.getImagewidth()));
						tempImgVML = tempImgVML.replaceAll("img_height", String
								.valueOf(mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_top", String
								.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_left", String
								.valueOf(rect_left + rect_width / 2
										- mtdic.getImagewidth() / 2));
						tempImgVML = tempImgVML.replaceAll("div_img", String
								.valueOf("div_img_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempImgVML = tempImgVML.replaceAll("img_path", String
								.valueOf(imgPath + mtdic.getDeviceimage()));
						tempImgVML = tempImgVML.replaceAll("div_stat", String
								.valueOf("div_stat_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));

						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45));
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_1"));
						tempLineVML = tempLineVML.replaceAll("line_height",
								String.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- mtdic.getImageheight() / 2
										- (rect_top + 45)));
						tempLineVML = tempLineVML.replaceAll("line_width", "0");
						tempVML += tempImgVML;
						tempVML += tempLineVML;
					}
				}
				break;
			case 2:
				rect_width = 120;
				for (int k = 0; k < devgroupinfoList.size(); k++) {
					String tempImgVML = "";
					String tempLineVML = "";
					MonitorTopoDevgroupInfo mtdevgroupinfo = (MonitorTopoDevgroupInfo) devgroupinfoList
							.get(k);
					MonitorTopoDeviceDic mtdic = monitorTopoDeviceDicDAO
							.findDictByTypecode(mtdevgroupinfo.getDevphytype(),
									mtdevgroupinfo.getDevtypecode());
					if (mtdic != null) {
						tempImgVML += imageVML;
						tempImgVML += statimageVML;
						tempImgVML = tempImgVML.replaceAll("img_width", String
								.valueOf(mtdic.getImagewidth()));
						tempImgVML = tempImgVML.replaceAll("img_height", String
								.valueOf(mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_top", String
								.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- k * 20 - mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_left", String
								.valueOf(rect_left + rect_width / 2
										- mtdic.getImagewidth() / 2 - 15 + 30
										* k));
						tempImgVML = tempImgVML.replaceAll("div_img", String
								.valueOf("div_img_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempImgVML = tempImgVML.replaceAll("img_path", String
								.valueOf(imgPath + mtdic.getDeviceimage()));
						tempImgVML = tempImgVML.replaceAll("div_stat", String
								.valueOf("div_stat_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45));
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2 - 15
										+ 30 * k));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_" + (k + 1)));
						tempLineVML = tempLineVML.replaceAll("line_height",
								String.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- k * 20 - mtdic.getImageheight() / 2
										- (rect_top + 45)));
						tempLineVML = tempLineVML.replaceAll("line_width", "0");
						tempVML += tempImgVML;
						tempVML += tempLineVML;
					}
				}

				break;
			case 3:
				rect_width = 160;
				for (int k = 0; k < devgroupinfoList.size(); k++) {
					String tempImgVML = "";
					String tempLineVML = "";
					MonitorTopoDevgroupInfo mtdevgroupinfo = (MonitorTopoDevgroupInfo) devgroupinfoList
							.get(k);
					MonitorTopoDeviceDic mtdic = monitorTopoDeviceDicDAO
							.findDictByTypecode(mtdevgroupinfo.getDevphytype(),
									mtdevgroupinfo.getDevtypecode());
					if (mtdic != null) {
						tempImgVML += imageVML;
						tempImgVML += statimageVML;
						tempImgVML = tempImgVML.replaceAll("img_width", String
								.valueOf(mtdic.getImagewidth()));
						tempImgVML = tempImgVML.replaceAll("img_height", String
								.valueOf(mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_top", String
								.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- (1 - k * (2 - k)) * 40
										- mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_left", String
								.valueOf(rect_left + rect_width / 2
										- mtdic.getImagewidth() / 2 - 45 + 45
										* k));
						tempImgVML = tempImgVML.replaceAll("div_img", String
								.valueOf("div_img_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempImgVML = tempImgVML.replaceAll("img_path", String
								.valueOf(imgPath + mtdic.getDeviceimage()));
						tempImgVML = tempImgVML.replaceAll("div_stat", String
								.valueOf("div_stat_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45));
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2 - 15
										+ 15 * k));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_v_" + (k + 1)));
						tempLineVML = tempLineVML.replaceAll("line_height",
								String.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- (1 - k * (2 - k)) * 40
										- mtdic.getImageheight() / 2
										- (rect_top + 45)));
						tempLineVML = tempLineVML.replaceAll("line_width", "0");
						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45 + rect_top
										+ (rect_height - txtbox_height) - 10
										- (1 - k * (2 - k)) * 40
										- mtdic.getImageheight() / 2
										- (rect_top + 45)));
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2 - 15
										+ 15 * k));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_h_" + (k + 1)));
						tempLineVML = tempLineVML
								.replaceAll("line_height", "0");
						tempLineVML = tempLineVML.replaceAll("line_width",
								String.valueOf(30 * k - 30));
						tempVML += tempImgVML;
						tempVML += tempLineVML;
					}
				}

				break;
			case 4:
				rect_width = 200;
				for (int k = 0; k < devgroupinfoList.size(); k++) {
					String tempImgVML = "";
					String tempLineVML = "";
					MonitorTopoDevgroupInfo mtdevgroupinfo = (MonitorTopoDevgroupInfo) devgroupinfoList
							.get(k);
					MonitorTopoDeviceDic mtdic = monitorTopoDeviceDicDAO
							.findDictByTypecode(mtdevgroupinfo.getDevphytype(),
									mtdevgroupinfo.getDevtypecode());
					if (mtdic != null) {
						int l_h_offset = 0;
						int l_img_offset = 0;
						int img_height = 0;
						switch (k) {
						case 0:
							img_height = 40;
							l_h_offset = -15;
							l_img_offset = -60;
							break;
						case 1:
							img_height = 0;
							l_h_offset = 0;
							l_img_offset = -30;
							break;
						case 2:
							img_height = 0;
							l_h_offset = 0;
							l_img_offset = 30;
							break;
						case 3:
							img_height = 40;
							l_h_offset = 15;
							l_img_offset = 60;
							break;
						default:
							break;
						}
						tempImgVML += imageVML;
						tempImgVML += statimageVML;
						tempImgVML = tempImgVML.replaceAll("img_width", String
								.valueOf(mtdic.getImagewidth()));
						tempImgVML = tempImgVML.replaceAll("img_height", String
								.valueOf(mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_top", String
								.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- img_height
										- mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_left", String
								.valueOf(rect_left + rect_width / 2
										- mtdic.getImagewidth() / 2 + l_img_offset + l_h_offset));
						tempImgVML = tempImgVML.replaceAll("div_img", String
								.valueOf("div_img_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempImgVML = tempImgVML.replaceAll("img_path", String
								.valueOf(imgPath + mtdic.getDeviceimage()));
						tempImgVML = tempImgVML.replaceAll("div_stat", String
								.valueOf("div_stat_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45));
						
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2 + l_h_offset));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_v_" + (k + 1)));
						tempLineVML = tempLineVML.replaceAll("line_height",
								String.valueOf(
										rect_top
										+ (rect_height - txtbox_height) - 10
										- img_height
										- mtdic.getImageheight()/2 -(rect_top + 45)
										));
						tempLineVML = tempLineVML.replaceAll("line_width", "0");
						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45 +rect_top
										+ (rect_height - txtbox_height) - 10
										- img_height
										- mtdic.getImageheight()/2 -(rect_top + 45)
										));
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2 +l_h_offset
									));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_h_" + (k + 1)));
						tempLineVML = tempLineVML
								.replaceAll("line_height", "0");
						tempLineVML = tempLineVML.replaceAll("line_width",
								String.valueOf(l_img_offset));
						tempVML += tempImgVML;
						tempVML += tempLineVML;
					}
				}

				break;
			default:
				rect_width = 220;
				for (int k = 0; k < devgroupinfoList.size(); k++) {
					String tempImgVML = "";
					String tempLineVML = "";
					MonitorTopoDevgroupInfo mtdevgroupinfo = (MonitorTopoDevgroupInfo) devgroupinfoList
							.get(k);
					MonitorTopoDeviceDic mtdic = monitorTopoDeviceDicDAO
							.findDictByTypecode(mtdevgroupinfo.getDevphytype(),
									mtdevgroupinfo.getDevtypecode());
					if (mtdic != null) {
						int l_h_offset = 0;
						int l_img_offset = 0;
						int img_height = 0;
						switch (k) {
						case 0:
							img_height = 60;
							l_h_offset = -15;
							l_img_offset = -70;
							break;
						case 1:
							img_height = 20;
							l_h_offset = 0;
							l_img_offset = -40;
							break;
						case 2:
							img_height = 0;
							l_h_offset = 0;
							l_img_offset = 0;
							break;
						case 3:
							img_height = 20;
							l_h_offset = 0;
							l_img_offset = 40;
							break;
						case 4:
							img_height = 60;
							l_h_offset = 15;
							l_img_offset = 70;
						default:
							break;
						}
						tempImgVML += imageVML;
						tempImgVML += statimageVML;
						tempImgVML = tempImgVML.replaceAll("img_width", String
								.valueOf(mtdic.getImagewidth()));
						tempImgVML = tempImgVML.replaceAll("img_height", String
								.valueOf(mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_top", String
								.valueOf(rect_top
										+ (rect_height - txtbox_height) - 10
										- img_height
										- mtdic.getImageheight()));
						tempImgVML = tempImgVML.replaceAll("img_left", String
								.valueOf(rect_left + rect_width / 2
										- mtdic.getImagewidth() / 2 + l_img_offset + l_h_offset));
						tempImgVML = tempImgVML.replaceAll("div_img", String
								.valueOf("div_img_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempImgVML = tempImgVML.replaceAll("img_path", String
								.valueOf(imgPath + mtdic.getDeviceimage()));
						tempImgVML = tempImgVML.replaceAll("div_stat", String
								.valueOf("div_stat_" + devgroupid + "_"
										+ mtdic.getDevphytype() + "_"
										+ mtdic.getDevtypecode()));
						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45));
						
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2 + l_h_offset));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_v_" + (k + 1)));
						tempLineVML = tempLineVML.replaceAll("line_height",
								String.valueOf(
										rect_top
										+ (rect_height - txtbox_height) - 10
										- img_height
										- mtdic.getImageheight()/2 -(rect_top + 45)
										));
						tempLineVML = tempLineVML.replaceAll("line_width", "0");
						tempLineVML += lineVML;
						tempLineVML = tempLineVML.replaceAll("line_top", String
								.valueOf(rect_top + 45 +rect_top
										+ (rect_height - txtbox_height) - 10
										- img_height
										- mtdic.getImageheight()/2 -(rect_top + 45)
										));
						tempLineVML = tempLineVML.replaceAll("line_left",
								String.valueOf(rect_left + rect_width / 2 +l_h_offset
									));
						tempLineVML = tempLineVML.replaceAll("type_line",
								String.valueOf("type_line_h_" + (k + 1)));
						tempLineVML = tempLineVML
								.replaceAll("line_height", "0");
						tempLineVML = tempLineVML.replaceAll("line_width",
								String.valueOf(l_img_offset));
						tempVML += tempImgVML;
						tempVML += tempLineVML;
					}
				}
				break;
			}

			int line_top = rect_top + 30;
			int line_left = rect_left;
			int line_width = rect_width;
			int groupname_width = rect_width - 2;
			int groupname_top = rect_top + 1;
			int groupname_left = rect_left + 1;
			int exchange_top = rect_top + 35;
			int exchange_left = rect_left + rect_width / 2 - 25;
			int txtbox_width = rect_width - 2;
			int txtbox_top = rect_top + (rect_height - txtbox_height);
			int txtbox_left = rect_left + 1;

			tempVML = tempVML.replaceAll("rect_top", String.valueOf(rect_top));
			tempVML = tempVML
					.replaceAll("rect_left", String.valueOf(rect_left));
			tempVML = tempVML.replaceAll("rect_width", String
					.valueOf(rect_width));
			tempVML = tempVML.replaceAll("rect_height", String
					.valueOf(rect_height));
			tempVML = tempVML.replaceAll("line_top", String.valueOf(line_top));
			tempVML = tempVML
					.replaceAll("line_left", String.valueOf(line_left));
			tempVML = tempVML.replaceAll("line_width", String
					.valueOf(line_width));
			tempVML = tempVML.replaceAll("groupname_width", String
					.valueOf(groupname_width));
			tempVML = tempVML.replaceAll("groupname_top", String
					.valueOf(groupname_top));
			tempVML = tempVML.replaceAll("groupname_left", String
					.valueOf(groupname_left));
			tempVML = tempVML.replaceAll("exchange_top", String
					.valueOf(exchange_top));
			tempVML = tempVML.replaceAll("exchange_left", String
					.valueOf(exchange_left));
			tempVML = tempVML.replaceAll("txtbox_width", String
					.valueOf(txtbox_width));
			tempVML = tempVML.replaceAll("txtbox_height", String
					.valueOf(txtbox_height-2));
			tempVML = tempVML.replaceAll("txtbox_top", String
					.valueOf(txtbox_top));
			tempVML = tempVML.replaceAll("txtbox_left", String
					.valueOf(txtbox_left));
			tempVML = tempVML.replaceAll("txtbox_info", String
					.valueOf(txtbox_info));

			tempVML += endVML;
			MonitorTopoGroupInfo mtg = new MonitorTopoGroupInfo();
			mtg.setDevicegroupid(mtgroup.getDevicegroupid());
			mtg.setGroupheight(rect_height);
			mtg.setGroupwidth(rect_width);
			mtg.setGroupvml(tempVML);
			mtg.setLastupdate(DateUtil.getNow());
			monitorTopoGroupInfoDAO.save(mtg);

		}

		String netVML = "<v:group id=\"net_location\" style=\"position:absolute;left:net_left;top:net_top;z-index:1000;width:100;height:100\" coordsize=\"100,100\">"
				+ "<v:roundrect style=\"Z-INDEX:3800;WIDTH:net_width;HEIGHT:12;TOP:0;LEFT:0\" id=div_rect arcsize=\"19661f\" filled=\"t\" fillcolor=\"silver\" stroked=\"t\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:oval style=\"Z-INDEX:3850;WIDTH:4;HEIGHT:12;TOP:0;LEFT:0\" id=net_oval fillcolor=\"white\" stroked=\"t\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3851;TOP:6;LEFT:15\" id=net_line from=\"0,0\" to=\"line_width,0\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:roundrect style=\"Z-INDEX:3860;WIDTH:word_width;HEIGHT:12;TOP:word_top;LEFT:word_left\" arcsize=\"4321f\" fillcolor=\"silver\" strokecolor=\"silver\" strokeweight=\".75pt\">"
				+ "<v:Textbox style=\"TEXT-ALIGN:center;FONT-FAMILY:宋体;COLOR:#000000;FONT-SIZE:10;WORD-BREAK:break-all;\" id=net_word inset=\"1pt,0pt,1pt,0pt\" print=\"t\"><b>word_content</b></v:Textbox></v:roundrect></v:group>";
		List locationList = monitorTopoLocationDAO.getAll();
		int locationsize = locationList.size();
		int location = -1;
		int yindex = -1;
		int leftindex = 60;
		int topindex = 350;
		int end_a = 645;
		int middle_a_b = 665;
		int start_b = 685;
		int rect_height = 240;
		for (int j = 0; j < groupList.size(); j++) {
			MonitorTopoGroup mtgroup = (MonitorTopoGroup) groupList.get(j);
			MonitorTopoGroupInfo mtgi = monitorTopoGroupInfoDAO.get(mtgroup
					.getDevicegroupid());
			MonitorTopoLocation mtlocation = monitorTopoLocationDAO.get(mtgroup
					.getLocation().getLocationid());
			if (location == mtgroup.getLocation().getLocationid().intValue()) {
				if (yindex == mtgroup.getGroupyindex()) {
					leftindex += mtgi.getGroupwidth();
				} else {
					topindex += mtgi.getGroupheight().intValue();
					switch (mtlocation.getLocationindex().intValue() % 2) {
					case 0:
						leftindex = start_b + mtgi.getGroupwidth();
						break;
					default:
						int xwidth = monitorTopoGroupDAO
								.getXWidthbyLocationAndYindex(mtgroup
										.getLocation().getLocationid(), mtgroup
										.getGroupyindex());
						if (locationsize <= 1) {
							if (xwidth > 0) {
								leftindex = middle_a_b - xwidth / 2
										+ mtgi.getGroupwidth();
							}
						} else {
							if (xwidth > 0) {
								leftindex = end_a - xwidth
										+ mtgi.getGroupwidth();
							}
						}
						break;
					}

					yindex = mtgroup.getGroupyindex();

				}

			} else {
				String tempnetvml = netVML;
				location = mtgroup.getLocation().getLocationid().intValue();
				int xwidth = monitorTopoGroupDAO.getXWidthbyLocationAndYindex(
						mtgroup.getLocation().getLocationid(), mtgroup.getGroupyindex());
				int yheight = monitorTopoGroupDAO.getYHeightbyLocation(mtgroup
						.getLocation().getLocationid());
				if (mtgi != null) {
					topindex = 350 + ((mtgroup.getGroupyindex() + 1) / 2 - 1)
							* 30 + yheight;
				} else {
					topindex = 350 + ((mtgroup.getGroupyindex() + 1) / 2 - 1)
							* 30 + rect_height;
				}
				switch (mtlocation.getLocationindex().intValue() % 2) {
				case 0:
					leftindex = start_b + mtgi.getGroupwidth();
					break;
				default:

					if (locationsize <= 1) {
						if (xwidth > 0) {
							leftindex = middle_a_b - xwidth / 2
									+ mtgi.getGroupwidth();
						}
					} else {
						if (xwidth > 0) {
							leftindex = end_a - xwidth + mtgi.getGroupwidth();
						}
					}
					break;
				}
				tempnetvml = tempnetvml.replaceAll("net_location", "net_group_"
						+ location);
				tempnetvml = tempnetvml.replaceAll("net_left", String
						.valueOf(leftindex - mtgi.getGroupwidth()));
				tempnetvml = tempnetvml.replaceAll("net_top", String
						.valueOf(topindex - 20));
				tempnetvml = tempnetvml.replaceAll("net_width", String
						.valueOf(xwidth < 150 ? 150 : xwidth));
				tempnetvml = tempnetvml.replaceAll("div_rect", "net_rect_"
						+ location);
				tempnetvml = tempnetvml.replaceAll("net_oval", "net_oval_"
						+ location);
				tempnetvml = tempnetvml.replaceAll("net_line", "net_line_"
						+ location);
				tempnetvml = tempnetvml.replaceAll("line_width", String
						.valueOf(xwidth - 30));
				tempnetvml = tempnetvml.replaceAll("word_width", String
						.valueOf(xwidth / 4 > 100 ? xwidth / 4 : 100));

				tempnetvml = tempnetvml.replaceAll("word_top", "0");
				tempnetvml = tempnetvml.replaceAll("word_left", String
						.valueOf(xwidth / 2
								- (xwidth / 4 > 100 ? xwidth / 4 : 100) / 2));
				tempnetvml = tempnetvml.replaceAll("net_word", "net_word_"
						+ location);
				tempnetvml = tempnetvml.replaceAll("word_content", mtlocation
						.getLocationname());

				yindex = mtgroup.getGroupyindex();

				mtgi.setGroupvml(mtgi.getGroupvml() + tempnetvml);
			}

			String vml = mtgi.getGroupvml();

			vml = vml.replaceAll("group_left", String.valueOf(leftindex
					- mtgi.getGroupwidth()));
			vml = vml.replaceAll("group_top", String.valueOf(topindex));

			mtgi.setGroupvml(vml);
			monitorTopoGroupInfoDAO.update(mtgi);

		}
		}catch (Exception e) {
			e.printStackTrace();
		}

	

	}

	public List getTopoGroupInfoList() {

		return monitorTopoGroupInfoDAO.getAll();
	}

	public String getTopoHeadVMLInfo() {
		String headVML = "<v:group style=\"Z-INDEX:2000;POSITION:absolute;WIDTH:100;HEIGHT:100;TOP:54;LEFT:280\" id=top_head coordsize=\"100,100\"> "
				+ "<v:roundrect style=\"Z-INDEX:3000;WIDTH:365;HEIGHT:135;TOP:0;LEFT:0\" id=head_rec_1 arcsize=\"1511f\" filled=\"t\" fillcolor=\"#cf9\" stroked=\"t\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:roundrect style=\"Z-INDEX:3000;WIDTH:240;HEIGHT:135;TOP:0;LEFT:405\" id=head_rec_2 arcsize=\"1311f\" filled=\"t\" fillcolor=\"#cf9\" stroked=\"t\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:roundrect style=\"Z-INDEX:3000;WIDTH:365;HEIGHT:115;TOP:155;LEFT:0\" id=head_rec_3 arcsize=\"1311f\" filled=\"t\" fillcolor=\"#fcc\" stroked=\"t\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:roundrect style=\"Z-INDEX:3000;WIDTH:240;HEIGHT:115;TOP:155;LEFT:405\" id=head_rec_4 arcsize=\"1311f\" filled=\"t\" fillcolor=\"#fcc\" stroked=\"t\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:Image style=\"Z-INDEX:3507;WIDTH:100;HEIGHT:100;TOP:105;LEFT:-130\" id=rada src=\"/monitorsys/pages/images/vml/rada.gif\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:36;HEIGHT:112;TOP:17;LEFT:14\" id=head_img_dataserver_1 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/dataserver.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:50;HEIGHT:45;TOP:46;LEFT:57\" id=head_img_datastore_1 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/datastore-m.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:50;HEIGHT:45;TOP:45;LEFT:437\" id=head_img_datastore_2 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/datastore-b.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:29;HEIGHT:45;TOP:14;LEFT:195\" id=head_img_pc_server_1 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/web-server.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:29;HEIGHT:45;TOP:14;LEFT:242\" id=head_img_pc_server_2 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/front-server.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:29;HEIGHT:45;TOP:14;LEFT:286\" id=head_img_pc_server_3 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/qc-server.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:45;TOP:14;LEFT:329\" id=head_img_pc_server_4 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/yy-server.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:32;HEIGHT:45;TOP:75;LEFT:250\" id=head_img_pc_server_5 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/front-server.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:29;HEIGHT:46;TOP:75;LEFT:517\" id=head_img_pc_server_6 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/front-server.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:32;HEIGHT:46;TOP:75;LEFT:571\" id=head_img_pc_server_7 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/front-server.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:70;HEIGHT:19;TOP:15;LEFT:112\" id=head_img_server_1 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/server-a.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:70;HEIGHT:19;TOP:38;LEFT:112\" id=head_img_server_2 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/server-b.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:70;HEIGHT:19;TOP:62;LEFT:112\" id=head_img_server_3 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/eserver-a.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:70;HEIGHT:19;TOP:87;LEFT:112\" id=head_img_server_4 onmousemove=\"javascript:showtuna_jmpinfo(this);\" onmouseout=\"javascript:notshowtuna_jmpinfo();\" src=\"IMAGE_PATH/eserver-b.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:17;LEFT:14\" id=head_stat_dataserver_1 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:46;LEFT:57\" id=head_stat_datastore_1 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:45;LEFT:437\" id=head_stat_datastore_2 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:14;LEFT:195\" id=head_stat_pc_server_1 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:14;LEFT:242\" id=head_stat_pc_server_2 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:14;LEFT:286\" id=head_stat_pc_server_3 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:14;LEFT:329\" id=head_stat_pc_server_4 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:75;LEFT:250\" id=head_stat_pc_server_5 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:75;LEFT:517\" id=head_stat_pc_server_6 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:75;LEFT:571\" id=head_stat_pc_server_7 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:15;LEFT:112\" id=head_stat_server_1 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:38;LEFT:112\" id=head_stat_server_2 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:62;LEFT:112\" id=head_stat_server_3 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3501;WIDTH:18;HEIGHT:18;TOP:87;LEFT:112\" id=head_stat_server_4 src=\"IMAGE_PATH/green.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:29;HEIGHT:52;TOP:163;LEFT:144\" id=head_img_coreexchange_1 src=\"IMAGE_PATH/coreexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:29;HEIGHT:52;TOP:163;LEFT:231\" id=head_img_coreexchange_2 src=\"IMAGE_PATH/coreexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:29;HEIGHT:52;TOP:163;LEFT:509\" id=head_img_coreexchange_3 src=\"IMAGE_PATH/coreexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:27;TOP:233;LEFT:52\" id=head_img_rejoinexchange_1 src=\"IMAGE_PATH/rejoinexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:27;TOP:233;LEFT:135\" id=head_img_rejoinexchange_2 src=\"IMAGE_PATH/rejoinexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:27;TOP:233;LEFT:215\" id=head_img_rejoinexchange_3 src=\"IMAGE_PATH/rejoinexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:27;TOP:233;LEFT:298\" id=head_img_rejoinexchange_4 src=\"IMAGE_PATH/rejoinexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:27;TOP:233;LEFT:427\" id=head_img_rejoinexchange_5 src=\"IMAGE_PATH/rejoinexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:27;TOP:233;LEFT:510\" id=head_img_rejoinexchange_6 src=\"IMAGE_PATH/rejoinexchange.png\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3500;WIDTH:31;HEIGHT:27;TOP:233;LEFT:597\" id=head_img_rejoinexchange_7 src=\"IMAGE_PATH/rejoinexchange.png\" bilevel=\"f\"/>"				
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:158\" id=head_line_10 from=\"0,0\" to=\"87,0\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:158\" id=head_line_11 from=\"0,0\" to=\"-92,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:158\" id=head_line_12 from=\"0,0\" to=\"-9,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:158\" id=head_line_13 from=\"0,0\" to=\"71,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:158\" id=head_line_14 from=\"0,0\" to=\"154,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:245\" id=head_line_20 from=\"0,0\" to=\"-179,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:245\" id=head_line_22 from=\"0,0\" to=\"-96,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:245\" id=head_line_23 from=\"0,0\" to=\"-16,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:245\" id=head_line_24 from=\"0,0\" to=\"67,60\" strokecolor=\"black\" strokeweight=\"1px\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:245\" id=head_line_30 from=\"0,0\" to=\"278,0\" strokecolor=\"green\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:523\" id=head_line_31 from=\"0,0\" to=\"-82,60\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:523\" id=head_line_32 from=\"0,0\" to=\"1,60\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:189;LEFT:523\" id=head_line_33 from=\"0,0\" to=\"88,60\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:73;LEFT:32\" id=head_line_40 from=\"0,0\" to=\"126,116\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:73;LEFT:32\" id=head_line_41 from=\"0,0\" to=\"50,0\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:73;LEFT:82\" id=head_line_42 from=\"0,0\" to=\"65,-49\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:73;LEFT:82\" id=head_line_43 from=\"0,0\" to=\"65,-26\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:73;LEFT:82\" id=head_line_44 from=\"0,0\" to=\"65,-2\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:73;LEFT:82\" id=head_line_45 from=\"0,0\" to=\"65,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:36;LEFT:209\" id=head_line_50 from=\"0,0\" to=\"-51,153\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:36;LEFT:256\" id=head_line_51 from=\"0,0\" to=\"-98,153\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:36;LEFT:300\" id=head_line_52 from=\"0,0\" to=\"-142,153\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:36;LEFT:343\" id=head_line_53 from=\"0,0\" to=\"-185,153\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:100;LEFT:260\" id=head_line_54 from=\"0,0\" to=\"-108,92\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:24;LEFT:172\" id=head_line_60 from=\"0,0\" to=\"-14,165\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:47;LEFT:157\" id=head_line_61 from=\"0,0\" to=\"1,142\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:71;LEFT:142\" id=head_line_62 from=\"0,0\" to=\"16,118\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:96;LEFT:127\" id=head_line_63 from=\"0,0\" to=\"31,93\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:67;LEFT:462\" id=head_line_70 from=\"0,0\" to=\"61,122\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:98;LEFT:531\" id=head_line_71 from=\"0,0\" to=\"-8,91\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:98;LEFT:587\" id=head_line_72 from=\"0,0\" to=\"-64,91\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:259;LEFT:66\" id=head_line_80 from=\"0,0\" to=\"0,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:259;LEFT:149\" id=head_line_81 from=\"0,0\" to=\"0,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:259;LEFT:229\" id=head_line_82 from=\"0,0\" to=\"0,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:259;LEFT:312\" id=head_line_83 from=\"0,0\" to=\"0,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:259;LEFT:441\" id=head_line_84 from=\"0,0\" to=\"0,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:259;LEFT:524\" id=head_line_85 from=\"0,0\" to=\"0,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:line style=\"Z-INDEX:3200;TOP:259;LEFT:611\" id=head_line_86 from=\"0,0\" to=\"0,23\" strokecolor=\"black\" strokeweight=\"1pt\"/>"
				+ "<v:Image style=\"Z-INDEX:3505;WIDTH:18;HEIGHT:18;TOP:5;LEFT:660\" id=head_cutline_1 src=\"IMAGE_PATH/green.png\" onmousemove=\"javascript:self_showtuna_jmpinfo(this);\" onmouseout=\"javascript:self_notshowtuna_jmpinfo();\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3505;WIDTH:18;HEIGHT:18;TOP:40;LEFT:660\" id=head_cutline_2 src=\"IMAGE_PATH/yellow.gif\" onmousemove=\"javascript:self_showtuna_jmpinfo(this);\" onmouseout=\"javascript:self_notshowtuna_jmpinfo();\" bilevel=\"f\"/>"
				+ "<v:Image style=\"Z-INDEX:3505;WIDTH:18;HEIGHT:18;TOP:75;LEFT:660\" id=head_cutline_3 src=\"IMAGE_PATH/red.gif\" onmousemove=\"javascript:self_showtuna_jmpinfo(this);\" onmouseout=\"javascript:self_notshowtuna_jmpinfo();\" bilevel=\"f\"/>"
				+ "<v:roundrect style=\"Z-INDEX:3505;WIDTH:120;HEIGHT:20;TOP:5;LEFT:680\" arcsize=\"4321f\" fillcolor=\"white\" strokecolor=\"#d6ffd6\" strokeweight=\".5pt\">"
				+ "<v:Textbox style=\"TEXT-ALIGN:left;FONT-FAMILY:宋体;COLOR:#bd231b;FONT-SIZE:12;WORD-BREAK:break-all;\" id=head_cutline_word_1 inset=\"5pt,3pt,5pt,0pt\" print=\"t\"><b>Status Ok</b></v:Textbox></v:roundrect>"
				+ "<v:roundrect style=\"Z-INDEX:3505;WIDTH:120;HEIGHT:20;TOP:40;LEFT:680\" arcsize=\"4321f\" fillcolor=\"white\" strokecolor=\"#d6ffd6\" strokeweight=\".5pt\">"
				+ "<v:Textbox style=\"TEXT-ALIGN:left;FONT-FAMILY:宋体;COLOR:#bd231b;FONT-SIZE:12;WORD-BREAK:break-all;\" id=head_cutline_word_3 inset=\"5pt,3pt,5pt,0pt\" print=\"t\"><b>Status Warning</b></v:Textbox></v:roundrect>"
				+ "<v:roundrect style=\"Z-INDEX:3505;WIDTH:120;HEIGHT:20;TOP:75;LEFT:680\" arcsize=\"4321f\" fillcolor=\"white\" strokecolor=\"#d6ffd6\" strokeweight=\".5pt\">"
				+ "<v:Textbox style=\"TEXT-ALIGN:left;FONT-FAMILY:宋体;COLOR:#bd231b;FONT-SIZE:12;WORD-BREAK:break-all;\" id=head_cutline_word_3 inset=\"5pt,3pt,5pt,0pt\" print=\"t\"><b>Status Critical</b></v:Textbox></v:roundrect>"
				+ "</v:group>";
		String imapge_path = "/monitorsys/pages/images/vml";
		headVML = headVML.replaceAll("IMAGE_PATH", imapge_path);
		return headVML;
	}


	public List getTopoGroupStatisticList() {
		// TODO Auto-generated method stub
		return monitorTopoGroupStatisticDAO.getAll();
	}

	public List getServerStatisticList() {
		// TODO Auto-generated method stub
		return monitorTopoServerStatisticDAO.getAll();
	}

}
