package org.king.task;

import org.apache.log4j.Logger;
import org.king.dao.impl.OracleDaoImpl;
import org.king.service.CheckService;
import org.king.service.impl.JJLinkServiceImpl;


public class TaskUtil {
    private static final Logger logger = Logger.getLogger(TaskUtil.class);

    private static CheckService checkService;

    static {
        checkService = new JJLinkServiceImpl();
        checkService.setJdbcDao(new OracleDaoImpl());
    }

    public static void jjlinkTask(){
        try {
            logger.info("start to execute jjlink task");
            checkService.checkRecord();
            logger.info("finish executing jjlink task");
        } catch (Exception e) {
            logger.error("fail to execute jjlink task");
        }
    }
}
