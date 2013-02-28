-- 圈存前置机配置参数

-- 加密前置机配置，通讯平台节点号、主功能号
delete from ykt_cur.t_frontcfg where paraname='encsvr.branchno';
delete from ykt_cur.t_frontcfg where paraname='encsvr.mainfunc';
insert into ykt_cur.t_frontcfg(paraname,paraval)values('encsvr.branchno','2000');
insert into ykt_cur.t_frontcfg(paraname,paraval)values('encsvr.mainfunc','8100');

insert into ykt_cur.t_bank(bankid,bankcode,bankname,enabled,svrbegintime,svrendtime,frontid,bankip,bankport,banktimeout)
values(1,'0000001','建邦圈存系统',1,20000,233000,10,'',0,3);

commit;
