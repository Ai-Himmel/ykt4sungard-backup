package com.kingstargroup.mobileMessage.util;

import org.apache.log4j.Logger;
import java.util.*;

  public class TestShowMessage extends  TimerTask{
	  
	  public void run() {
		  Calendar c = Calendar.getInstance();
		  log.info("=====Ç°Ê±¼ä===="+c.getTime());
	  }
	  private Logger log = Logger.getLogger(TestShowMessage.class);
  }
