package com.sungard.smartcard.modules.system.function;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.SiteService;


@SmartCardFunction(infotype = 3, funcnum = 10001101, name = "登陆站点设置")
@Component
public class SiteFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(SiteFunction.class);
	
	@Autowired
	private SiteService siteService;
	public void setSiteService(SiteService siteService) {
		this.siteService = siteService;
	}

	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		logger.info("------------站点新增业务启动------------------");
		Site s = super.getParameter(Site.class, session);
		siteService.addNewSite(s);
		logger.info("------------站点新增业务结束------------------");
	}

	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Site s = super.getParameter(Site.class, session);
		siteService.delSite(s);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Site s = super.getParameter(Site.class, session);
		List<Site> sites = siteService.querySite(s);
		outPack(sites,Site.class,session);
	}

	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Site s = super.getParameter(Site.class, session);
		siteService.modifySite(s);
	}
	
}
