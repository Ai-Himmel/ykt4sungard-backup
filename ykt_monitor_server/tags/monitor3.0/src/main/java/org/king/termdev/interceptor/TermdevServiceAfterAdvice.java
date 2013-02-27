package org.king.termdev.interceptor;

import java.lang.reflect.Method;
import java.util.List;

import org.king.support.service.MonitorSupportService;
import org.king.termdev.domain.MonitorTermdevchecks;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.utils.DateUtil;
import org.springframework.aop.AfterReturningAdvice;

public class TermdevServiceAfterAdvice implements AfterReturningAdvice {
	
    private MonitorSupportService monitorSupportService;

	public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
		this.monitorSupportService = monitorSupportService;
	}

	public void afterReturning(Object returnValue, Method method, Object[] arg2,
			Object arg3) throws Throwable {
		try {
			if(method.getName().startsWith("save")){
				
				if(method.getName().equals("saveOrUpdateMonitorDevtem")){
					//模板有重新banding操作
					String datetime = DateUtil.getNow();
					List list  = monitorSupportService.findMonitorTermdeviceStatusOffTemplate();
					if(list!=null&&list.size()>0){
						for(int i=0;i<list.size();i++){
							MonitorTermdeviceStatus MTS = (MonitorTermdeviceStatus) list.get(i);
							MonitorTermdevchecks MTC = monitorSupportService.findLastMonitorTermdevchecksByTermid(MTS.getDeviceId());
							if(MTC!=null){
								long dtime = DateUtil.getDuration(MTC.getStartTime(),datetime);
								MTC.setEndTime(datetime);
								MTC.setTimeLast(Double.valueOf(dtime));
								monitorSupportService.updateLastMonitorTermdevchecks(MTC);
							}
							monitorSupportService.deleteMonitorTermdeviceStatusOffTemplate(MTS);
						}
					}
				}

			}else if(method.getName().startsWith("update")){
				if(method.getName().equals("updateBindingDevice")){
					//模板有重新banding操作
					String datetime = DateUtil.getNow();
					List list  = monitorSupportService.findMonitorTermdeviceStatusOffTemplate();
					if(list!=null&&list.size()>0){
						for(int i=0;i<list.size();i++){
							MonitorTermdeviceStatus MTS = (MonitorTermdeviceStatus) list.get(i);
							MonitorTermdevchecks MTC = monitorSupportService.findLastMonitorTermdevchecksByTermid(MTS.getDeviceId());
							if(MTC!=null){
								long dtime = DateUtil.getDuration(MTC.getStartTime(),datetime);
								MTC.setEndTime(datetime);
								MTC.setTimeLast(Double.valueOf(dtime));
								monitorSupportService.updateLastMonitorTermdevchecks(MTC);
							}
							monitorSupportService.deleteMonitorTermdeviceStatusOffTemplate(MTS);
						}
					}
				}

			}else if(method.getName().startsWith("delete")){
				//do nothing
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		
	  
	}
	
	

}
