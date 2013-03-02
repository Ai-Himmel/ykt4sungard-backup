package com.kingstargroup.fdykt;

import org.apache.commons.configuration.Configuration;
import org.apache.commons.configuration.ConfigurationException;
import org.apache.commons.configuration.PropertiesConfiguration;

import java.io.IOException;

/**
 * Description: please input this class usage...
 * Author: Haiyu.Peng
 * Date: 2010-9-13
 * Time: 0:48:34
 */
public class ConfigMenu {
    protected ConfigMenu() {

    }
    //private static ConfigMenu _configMenu = null;
    private static Configuration _config = null;

    private static Configuration getInstance() {
        if (null == _config) {
            //_configMenu = new ConfigMenu();
            try {
                _config = new PropertiesConfiguration("menu.properties");
            } catch (ConfigurationException e) {
                e.printStackTrace();
            }
        }
        return _config;
    }

    public static boolean getMenuStatus(String propName){
        return getInstance().getBoolean(propName,false);
    }
}
