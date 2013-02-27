--增加主机类型字段
ALTER TABLE ykt_mon.monitor_host ADD (HOST_TYPE VARCHAR2(10));

--删除状态图菜单权限
delete from ykt_mon.ico_role_menu where menu_id in ('16','1601','1602','1603','1604');

delete from ykt_mon.ICO_MENU;
commit;

insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('16', '0', '拓扑图设置', 'javascript: void(0);', null, null, null, null, null, 12);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1601', '16', '校区设置', 'location.do?method=listMonitorTopoLocation', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1602', '16', '组别设置', 'group.do?method=listMonitorTopoGroup', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1603', '16', '设备分组查询', 'deviceGroup.do?method=listMonitorTopoDeviceGroup', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1406', '14', '拓扑信息', 'showvml.do?method=showmvl', null, 'main', null, null, null, 1);
insert into ykt_mon.ico_menu (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1407', '14', '终端设备状态统计', 'termdeviceStatus.do?method=caculateDeviceStatus', '', 'main', '', '', '', 7);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('06', '0', '总体概览', 'javascript: void(0);', null, null, null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('07', '0', '监控地图', 'javascript: void(0);', null, null, null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('08', '0', '主机监控', 'javascript: void(0);', null, null, null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('09', '0', '主机服务监控', 'javascript: void(0);', null, null, null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('10', '0', '终端监控', 'javascript: void(0);', null, null, null, null, null, 5);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('11', '0', '业务监控', 'javascript: void(0);', null, null, null, null, null, 6);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1202', '12', '服务模板管理', 'serviceTemplate.do?method=listMonitorServiceTemplate', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1203', '12', '联系人模板管理', 'contactTemplate.do?method=listMonitorContactTemplate', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1204', '12', '时间域管理', 'timePeriods.do?method=listMonitorTimePeriods', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1205', '12', '设备模板管理', 'termdevTemplate.do?method=listMonitorTermdevTemplate', null, 'main', null, null, null, 5);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1307', '13', '主机组维护', 'hostgroups.do?method=listMonitorHostgroups', null, 'main', null, null, null, 6);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1308', '13', '联系人组维护', 'contactgroups.do?method=listMonitorContactgroups', null, 'main', null, null, null, 7);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('15', '0', '历史状态', 'javascript: void(0);', null, null, null, null, null, 14);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1501', '15', '主机历史状态', 'hostHistoryStatus.do?method=listHostHistoryStatus', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1502', '15', '服务历史状态', 'serviceHistoryStatus.do?method=listServiceHistoryStatus', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1503', '15', '终端设备历史状态', 'termdeviceHistoryStatus.do?method=listTermdeviceHistoryStatus', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1504', '15', '终端设备服务历史状态', 'termdevserviceHistoryStatus.do?method=listTermdevserviceHistoryStatus', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('12', '0', '模板管理', 'javascript: void(0);', null, null, null, null, null, 10);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1201', '12', '主机模板管理', 'hostTemplate.do?method=listMonitorHostTemplate', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0', '-1', '系统菜单', 'javascript: void(0);', null, null, null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('00', '0', '用户管理', 'javascript: void(0);', null, null, null, null, null, 7);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0001', '00', '用户管理', 'accountManager.do?method=searchAccount', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('01', '0', '权限管理', 'javascript: void(0);', null, null, null, null, null, 8);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0101', '01', '帐户管理', 'accountSecurityManager.do?method=searchAccount', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0102', '01', '角色管理', 'roleManager.do?method=loadRole', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0103', '01', '资源管理', 'resourceManager.do?method=loadResource', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('02', '0', '菜单管理', 'javascript: void(0);', null, null, null, null, null, 9);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0201', '02', '菜单管理', 'menuManager.do?method=searchMenu', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0202', '02', '菜单权限', 'menuSecurityManager.do?method=loadRole4GrantMenu', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('99', '0', '系统退出', 'javascript: void(0);', null, null, null, null, null, 99);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('9901', '99', '退出', 'logoutAction.do?method=logout', null, '_top', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('14', '0', '运行状态', 'javascript: void(0);', null, null, null, null, null, 13);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1401', '14', '全局信息统计', 'globalStatus.do?method=listGlobalStatus', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1402', '14', '主机信息列表', 'hostStatus.do?method=listMonitorHostStatus', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1403', '14', '服务信息列表', 'serviceStatus.do?method=listMonitorServiceStatus', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1404', '14', '终端设备信息列表', 'termdeviceStatus.do?method=listMonitorTermdeviceStatus', null, 'main', null, null, null, 5);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1405', '14', '终端设备服务信息列表', 'termdevserviceStatus.do?method=listMonitorTermdevserviceStatus', null, 'main', null, null, null, 6);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('13', '0', '配置管理', 'javascript: void(0);', null, null, null, null, null, 11);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1301', '13', '运行参数维护', 'runtimevariables.do?method=listMonitorRuntimevariables', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1302', '13', '主机信息维护', 'host.do?method=listMonitorHost', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1303', '13', '主机服务信息维护', 'hostservice.do?method=listMonitorService', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1309', '13', '设备信息', 'tdevice.do?method=listTDevice', null, 'main', null, null, null, 8);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1305', '13', '设备服务信息维护', 'termdevService.do?method=listMonitorTermdevService', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1306', '13', '联系人信息维护', 'contact.do?method=listMonitorContact', null, 'main', null, null, null, 5);
commit;

delete from ykt_mon.MONITOR_TOPO_DEVICE_DIC; 
commit;

insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0020', '0020.png', 26, 64, 1, '多媒体');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0010', '0010.png', 28, 44, 2, '圈存机');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0121', '0121.jpg', 20, 20, 3, '计时宝');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0226', '0226.png', 35, 50, 6, '消费pos');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0244', '0244.png', 35, 80, 9, '水控计费器');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0245', '999-0245.png', 35, 33, 10, '水控计费器');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1004, '5301', 'xsq-5301.png', 40, 30, 12, '消费CAN');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '5302', '999-5301.png', 40, 30, 13, 'LPROT');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1004, '5302', 'xsq-5301.png', 40, 30, 18, '消费CAN');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '5301', '999-5301.png', 40, 30, 19, 'JLPORT');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1001, '5301', 'hd-5301.png', 40, 23, 14, '汇多CCU');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1001, '0226', 'hd-0226.png', 33, 40, 15, '消费pos');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1004, '0226', 'xsq-0226.png', 35, 26, 16, '消费pos');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (2001, '0020', '0020.png', 26, 64, 17, '多媒体');
commit;