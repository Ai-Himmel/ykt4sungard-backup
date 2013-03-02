package com.kingstargroup.fdykt;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.HashMap;

import org.apache.xmlbeans.XmlException;

import com.kingstar.itemconfig.Configitem;
import com.kingstar.itemconfig.ItemConfigDocument;
import com.kingstar.itemconfig.ItemConfigDocument.ItemConfig;
import com.kingstargroup.fdykt.util.DateUtil;

public class ConfigItemInit {

	private static ItemConfigDocument itemConfigDocument = null;
	private static String file_path_name = "";
	private static HashMap cfgitem_map = new HashMap();

	private ConfigItemInit() {

	}

	public static ItemConfigDocument getInstance() {
		if (itemConfigDocument == null) {
			try {
				file_path_name = KSConfiguration.getInstance().getProperty(
						"item_config_doc");
//				URL url = ConfigItemInit.class
//						.getResource("/" + file_path_name);
//				System.out.println(url.toString());
				File cfile = new File(file_path_name);				
//				File cfile = new File(url.toString().substring(5));
				if (cfile.canRead()) {
					itemConfigDocument = ItemConfigDocument.Factory
							.parse(cfile);
					if (itemConfigDocument != null) {
						ItemConfig itemconfig = itemConfigDocument
								.getItemConfig();
						Configitem cfgitemArr[] = itemconfig.getItemArray();
						for (int i = 0; i < cfgitemArr.length; i++) {
							Configitem cfgitem = cfgitemArr[i];
							String starttime = cfgitem.getStartTime();
							String endtime = cfgitem.getEndTime();
							String display = cfgitem.getDisplay();
							String gid = cfgitem.getGid();
							String now = DateUtil.getNow("yyyy-MM-dd");
							if ("true".equals(display)) {
								if (DateUtil.checkSpecialTimeSequence(
										starttime, now, "yyyy-MM-dd") <= 0
										&& DateUtil.checkSpecialTimeSequence(
												endtime, now, "yyyy-MM-dd") >= 0) {
									cfgitem_map.put(gid, cfgitem);
								}
							}
						}
					}
				} else {
					System.out.println("专用收费配置文件不可读取,配置路径为" + file_path_name);
				}

			} catch (XmlException e) {
				// TODO Auto-generated catch block
				System.out.println("专用收费配置文件格式有误,配置路径为" + file_path_name);
				e.printStackTrace();
			} catch (IOException e) {
				System.out.println("专用收费配置文件IO读取失败,配置路径为" + file_path_name);
				e.printStackTrace();
			}
			return itemConfigDocument;
		} else {
			return itemConfigDocument;
		}
	}

	public static Configitem getConfigItembyGid(String gid) {
		return cfgitem_map.get(gid) == null ? null : (Configitem) cfgitem_map
				.get(gid);
	}

}
