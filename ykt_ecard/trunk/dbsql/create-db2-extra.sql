insert into ykt_web.Counter values ('com.liferay.portal.model.Address', 10);
insert into ykt_web.Counter values ('com.liferay.portal.model.Group', 20);
insert into ykt_web.Counter values ('com.liferay.portal.model.Role', 20);
insert into ykt_web.Counter values ('com.liferay.portal.model.User.liferay.com', 100);
insert into ykt_web.Counter values ('com.liferay.portlet.imagegallery.model.IGFolder', 20);
insert into ykt_web.Counter values ('com.liferay.portlet.imagegallery.model.IGImage.liferay.com', 42);
insert into ykt_web.Counter values ('com.liferay.portlet.polls.model.PollsQuestion', 10);
insert into ykt_web.Counter values ('com.liferay.portlet.shopping.model.ShoppingCategory', 20);
insert into ykt_web.Counter values ('com.liferay.portlet.shopping.ejb.ShoppingItem', 40);
insert into ykt_web.Counter values ('com.liferay.portlet.wiki.model.WikiNode', 10);

insert into ykt_web.Company (companyId, portalURL, homeURL, mx, name, shortName, type_, size_, emailAddress) values ('kingstargroup.com', '10.49.188.50', '10.49.188.50', 'kingstargroup.com', 'Kingstar, LLC', 'Kingstar', 'biz', '', 'admin@kingstargroup.com');

insert into ykt_web.Group_ (groupId, companyId, parentGroupId, name, friendlyURL, themeId, colorSchemeId) values ('1', 'kingstargroup.com', '-1', 'General Guest', '/guest', 'classic', '01');
insert into ykt_web.Group_ (groupId, companyId, parentGroupId, name, friendlyURL, themeId, colorSchemeId) values ('2', 'kingstargroup.com', '-1', 'General User', '', 'classic', '01');
insert into ykt_web.Group_ (groupId, companyId, parentGroupId, name, friendlyURL, themeId, colorSchemeId) values ('3', 'kingstargroup.com', '-1', 'YKT General Group', '/general', 'classic', '01');
insert into ykt_web.Group_ (groupId, companyId, parentGroupId, name, friendlyURL, themeId, colorSchemeId) values ('4', 'kingstargroup.com', '-1', 'YKT Admin Group', '/admin', 'classic', '01');

insert into ykt_web.Role_ (roleId, companyId, name) values ('1', 'kingstargroup.com', 'Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('2', 'kingstargroup.com', 'Guest');
insert into ykt_web.Role_ (roleId, companyId, name) values ('3', 'kingstargroup.com', 'User');
insert into ykt_web.Role_ (roleId, companyId, name) values ('4', 'kingstargroup.com', 'YKT General User');
insert into ykt_web.Role_ (roleId, companyId, name) values ('5', 'kingstargroup.com', 'YKT Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('6', 'kingstargroup.com', 'YKT News Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('7', 'kingstargroup.com', 'YKT Rule Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('8', 'kingstargroup.com', 'YKT Map Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('9', 'kingstargroup.com', 'YKT Tutorial Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('10', 'kingstargroup.com', 'YKT FAQ Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('11', 'kingstargroup.com', 'YKT Msgboard Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('12', 'kingstargroup.com', 'YKT Cardtransaction Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('13', 'kingstargroup.com', 'YKT Cardlist Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('14', 'kingstargroup.com', 'YKT Document Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('15', 'kingstargroup.com', 'YKT About Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('16', 'kingstargroup.com', 'YKT Hitinfo Administrator');
insert into ykt_web.Role_ (roleId, companyId, name) values ('17', 'kingstargroup.com', 'YKT Serviceinfo Administrator');


insert into ykt_web.Release_ (releaseId, createDate, modifiedDate, buildNumber) values ('1', current timestamp, current timestamp, 2215);

insert into ykt_web.User_ (userId, companyId, createDate, password_, passwordEncrypted, passwordReset, firstName, middleName, lastName, nickName, male, birthday, emailAddress, themeId, colorSchemeId, greeting, loginDate, failedLoginAttempts, agreedToTermsOfUse, active_, languageid, resolution) values ('admin', 'kingstargroup.com', current timestamp, 'test', '0', '0', '', '', '', '', '1', '1970-01-01-00.00.00.000000', 'admin@kingstargroup.com', 'classic', '01', '欢迎您?,管理员?!', current timestamp, 0, '1', '1', 'zh_cn', '1024x768');
insert into ykt_web.User_ (userId, companyId, createDate, password_, passwordEncrypted, passwordReset, firstName, middleName, lastName, nickName, male, birthday, emailAddress, themeId, colorSchemeId, greeting, loginDate, failedLoginAttempts, agreedToTermsOfUse, active_, languageid, resolution) values ('kingstargroup.com.default', 'default', current timestamp, 'password', '0', '0', '', '', '', '', '1', '1970-01-01-00.00.00.000000', 'default@kingstargroup.com', 'classic', '01', '欢迎访问校园一卡通综合查询?!', current timestamp, 0, '1', '1', 'zh_cn', '1024x768');

insert into ykt_web.Users_Groups values ('admin', '4');

insert into ykt_web.GROUPS_ROLES(groupid, roleid) values('3', '4');

insert into ykt_web.Users_Roles values('admin', '5');
insert into ykt_web.Users_Roles values('admin', '6');
insert into ykt_web.Users_Roles values('admin', '7');
insert into ykt_web.Users_Roles values('admin', '8');
insert into ykt_web.Users_Roles values('admin', '9');
insert into ykt_web.Users_Roles values('admin', '10');
insert into ykt_web.Users_Roles values('admin', '11');
insert into ykt_web.Users_Roles values('admin', '12');
insert into ykt_web.Users_Roles values('admin', '13');
insert into ykt_web.Users_Roles values('admin', '14');
insert into ykt_web.Users_Roles values('admin', '15');
insert into ykt_web.Users_Roles values('admin', '16');
insert into ykt_web.Users_Roles values('admin', '17');

insert into ykt_web.Ecard_Information values(1, '8', '', '', '', '1970-01-01-00.00.00.000000', 'admin');
insert into ykt_web.Ecard_Information values(2, '9', '', '', '', '1970-01-01-00.00.00.000000', 'admin');

insert into ykt_web.INFO_TYPE(info_type, info_name) values('4', 'FAQ');
insert into ykt_web.INFO_TYPE(info_type, info_name) values('4.1', '卡类');
insert into ykt_web.INFO_TYPE(info_type, info_name) values('4.2', '圈存类');
insert into ykt_web.INFO_TYPE(info_type, info_name) values('4.3', '其他类');

insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1', 'group.3', 'kingstargroup.com', '-1', '首页', 'portlet', '
narrow-1=cardinfo,querydetail,ecardlink
wide-1=ecardnews,ecardlist
column-order=n1,w1,', '', 0.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('2', 'group.3', 'kingstargroup.com', '-1', '校园卡使用', 'portlet', '
state-max=ecardtransaction
wide-1=ecardtransaction
column-order=w1,', '', 1.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('3', 'group.3', 'kingstargroup.com', '-1', '文档下载', 'portlet', '
wide-1=ecarddoc
state-max=ecarddoc
column-order=w1,', '', 2.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('4', 'group.3', 'kingstargroup.com', '-1', '系统图集', 'portlet', '
wide-1=distributionmap
state-max=distributionmap
column-order=w1,', '', 3.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('5', 'group.3', 'kingstargroup.com', '-1', '规章制度', 'portlet', '
wide-1=ecardrule
state-max=ecardrule
column-order=w1,', '', 4.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('6', 'group.3', 'kingstargroup.com', '-1', '操作指南', 'portlet', '
wide-1=ecardtutorial
state-max=ecardtutorial
column-order=w1,', '', 5.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('7', 'group.3', 'kingstargroup.com', '-1', 'FAQ', 'portlet', '
wide-1=ecardfaq
state-max=ecardfaq
column-order=w1,', '', 6.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('8', 'group.3', 'kingstargroup.com', '-1', '留言本', 'portlet', '
state-max=ecardmsgboard
wide-1=ecardmsgboard
column-order=w1,', '', 7.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('9', 'group.3', 'kingstargroup.com', '-1', '系统简介', 'portlet', '
state-max=ecardabout
wide-1=ecardabout
column-order=w1,', '', 8.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('10', 'group.3', 'kingstargroup.com', '-1', '服务信息', 'portlet', '
state-max=ecardservice
wide-1=ecardservice
column-order=w1,', '', 9.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.1', 'group.1', 'kingstargroup.com', '-1', '首页', 'portlet', '
narrow-1=58,ecardlink
wide-1=ecardnews,ecardlist
column-order=n1,w1,', '/home', 0.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.2', 'group.1', 'kingstargroup.com', '-1', '文档下载', 'portlet', '
wide-1=ecarddoc
state-max=ecarddoc
column-order=w1,', '/ecarddoc', 1.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.3', 'group.1', 'kingstargroup.com', '-1', '系统图集', 'portlet', '
wide-1=distributionmap
state-max=distributionmap
column-order=w1,', '/distributionmap', 2.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.4', 'group.1', 'kingstargroup.com', '-1', '规章制度', 'portlet', '
wide-1=ecardrule
state-max=ecardrule
column-order=w1,', '/ecardrule', 3.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.5', 'group.1', 'kingstargroup.com', '-1', '操作指南', 'portlet', '
wide-1=ecardtutorial
state-max=ecardtutorial
column-order=w1,', '/ecardtutorial', 4.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.6', 'group.1', 'kingstargroup.com', '-1', 'FAQ', 'portlet', '
wide-1=ecardfaq
state-max=ecardfaq
column-order=w1,', '/ecardfaq', 5.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.7', 'group.1', 'kingstargroup.com', '-1', '系统简介', 'portlet', '
wide-1=ecardabout
state-max=ecardabout
column-order=w1,', '/ecardabout', 6.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1.8', 'group.1', 'kingstargroup.com', '-1', '服务信息', 'portlet', '
wide-1=ecardservice
state-max=ecardservice
column-order=w1,', '/ecardservice', 7.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('1', 'group.4', 'kingstargroup.com', '-1', '首页', 'portlet', '
wide-1=ecardnews,ecardlist
column-order=w1,', '', 0.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('2', 'group.4', 'kingstargroup.com', '-1', '校园卡使用', 'portlet', '
state-max=ecardtransaction
wide-1=ecardtransaction
column-order=w1,', '', 1.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('3', 'group.4', 'kingstargroup.com', '-1', '文档下载', 'portlet', '
wide-1=ecarddoc
state-max=ecarddoc
column-order=w1,', '', 2.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('4', 'group.4', 'kingstargroup.com', '-1', '系统图集', 'portlet', '
wide-1=distributionmap
state-max=distributionmap
column-order=w1,', '', 3.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('5', 'group.4', 'kingstargroup.com', '-1', '规章制度', 'portlet', '
wide-1=ecardrule
state-max=ecardrule
column-order=w1,', '', 4.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('6', 'group.4', 'kingstargroup.com', '-1', '操作指南', 'portlet', '
wide-1=ecardtutorial
state-max=ecardtutorial
column-order=w1,', '', 5.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('7', 'group.4', 'kingstargroup.com', '-1', 'FAQ', 'portlet', '
wide-1=ecardfaq
state-max=ecardfaq
column-order=w1,', '', 6.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('8', 'group.4', 'kingstargroup.com', '-1', '留言本', 'portlet', '
state-max=ecardmsgboard
wide-1=ecardmsgboard
column-order=w1,', '', 7.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('9', 'group.4', 'kingstargroup.com', '-1', '滚动新闻', 'portlet', '
state-max=ecardhit
wide-1=ecardhit
column-order=w1,', '', 8.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('10', 'group.4', 'kingstargroup.com', '-1', '系统简介', 'portlet', '
state-max=ecardabout
wide-1=ecardabout
column-order=w1,', '', 9.0);
insert into ykt_web.Layout (layoutId, userId, companyId, parentLayoutId, name, type_, typeSettings, friendlyURL, priority) values ('11', 'group.4', 'kingstargroup.com', '-1', '服务信息', 'portlet', '
state-max=ecardservice
wide-1=ecardservice
column-order=w1,', '', 10.0);
