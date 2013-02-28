package org.king.security.web.listener;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.Configuration;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.ServiceLocator;
import org.king.security.service.SecurityService;
import org.springframework.context.ApplicationContext;
import org.springframework.web.context.support.WebApplicationContextUtils;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import java.io.File;

public class InitListener implements ServletContextListener {
    private static Log log = LogFactory.getLog(InitListener.class);
    private ServletContext servletContext;

    /**
     * (non-Javadoc)
     *
     * @see javax.servlet.ServletContextListener#contextDestroyed(javax.servlet.ServletContextEvent)
     */
    public void contextDestroyed(ServletContextEvent arg0) {
    }

    /**
     * (non-Javadoc)
     *
     * @see javax.servlet.ServletContextListener#contextInitialized(javax.servlet.ServletContextEvent)
     */
    public void contextInitialized(ServletContextEvent event) {
        log.info("********* Initialized Epay now *********************");
        servletContext = event.getServletContext();
        initContext();
        initRootPath();
        initSecurity();
        Configuration.load();
        log.info("********* Initialized Epay success ******************");
    }

    private void initContext() {
        ApplicationContext ctx = WebApplicationContextUtils.getRequiredWebApplicationContext(servletContext);
        ServiceLocator.getInstance().setContext(ctx);
    }

    private void initRootPath() {
        String rootPath = servletContext.getRealPath("/");
        rootPath = rootPath.endsWith(File.separator) ? rootPath : (rootPath + File.separator);
    }

    private void initSecurity() {
        try {
            ((SecurityService) ServiceLocator.getInstance().getService("securityService")).initSecurity();
        } catch (BusinessException e) {
            log.error("starting spring error: ", e);
        }
    }
}
