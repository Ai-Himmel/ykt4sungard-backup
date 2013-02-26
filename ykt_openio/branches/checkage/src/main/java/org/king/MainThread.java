package org.king;

import org.apache.log4j.Logger;
import org.king.common.Configuration;
import org.king.common.Constant;
import org.king.dao.impl.OracleDaoImpl;
import org.king.http.HttpsRequester;
import org.king.service.CheckService;
import org.king.service.impl.JJLinkServiceImpl;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.impl.StdSchedulerFactory;

import javax.net.ssl.HttpsURLConnection;
import java.io.IOException;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.util.Scanner;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class MainThread {
    private static final Logger logger = Logger.getLogger(MainThread.class);

    private static CheckService checkService;

    public static void main(String[] args) {
        try {
            Configuration.load();
            checkService = new JJLinkServiceImpl();
            checkService.setJdbcDao(new OracleDaoImpl());
            Scheduler scheduler = StdSchedulerFactory.getDefaultScheduler();
            scheduler.start();
            logger.info("The main thread is working....");
            Scanner scanner = new Scanner(System.in);
            String code;
            while (true) {
                code = scanner.nextLine();
                if ("exit".equalsIgnoreCase(code)) {
                    break;
                } else if ("request".equalsIgnoreCase(code)) {
                    checkService.checkRecord();
                }
            }
            scheduler.shutdown();
        } catch (SchedulerException e) {
            logger.error(e);
        }
    }
}
