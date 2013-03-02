
CREATE FUNCTION "YKTINST1"."TS_FMT"
 ("TS" TIMESTAMP,
  "FMT" VARCHAR(20)
 ) 
  RETURNS VARCHAR(50)
  SPECIFIC "YKTINST1"."SQL090108172524100"
  LANGUAGE SQL
  NOT DETERMINISTIC
  READS SQL DATA
  STATIC DISPATCH
  CALLED ON NULL INPUT
  EXTERNAL ACTION
  INHERIT SPECIAL REGISTERS
  RETURN
with tmp (dd,mm,yyyy,hh,mi,ss,nnnnnn) as (
  select substr( digits (day(TS)),9), substr( digits (month(TS)),9) , rtrim(
      char(year(TS))) , substr( digits (hour(TS)),9), substr( digits (minute(
      TS)),9), substr( digits (second(TS)),9), rtrim(char(microsecond(TS)))
    from sysibm.sysdummy1 )
  select
      case fmt
        when 'yyyymmdd'
          then yyyy || mm || dd
        when 'mm/dd/yyyy'
          then mm || '/' || dd || '/' || yyyy
        when 'yyyy/dd/mm hh:mi:ss'
          then yyyy || '/' || mm || '/' || dd || ' ' || hh || ':' || mi || ':'
            || ss
        when 'nnnnnn'
          then nnnnnn
        else 'date format ' || coalesce(fmt,' <null> ') || ' not recognized.'
      end
    from tmp;
    
    


CREATE FUNCTION YKT_CUR.LPAD
 (STR VARCHAR(20),
  LEN INTEGER,
  PAD varchar(1)
 ) 
  RETURNS VARCHAR(200)
  LANGUAGE SQL
  NOT DETERMINISTIC
  READS SQL DATA
  STATIC DISPATCH
  CALLED ON NULL INPUT
  EXTERNAL ACTION
  INHERIT SPECIAL REGISTERS
  begin atomic
  declare leftlen integer;
  declare strlen integer;
  set strlen = length(str);
  if len > strlen then
    set leftlen = len - strlen;
  	RETURN repeat(pad,leftlen)||str;
  end if;
  if len = strlen then
  	return str;
  end if;
 
  	set leftlen = strlen - len;
    return substr(str,len,strlen);
  end;
  
  

INSERT INTO YKT_CUR.T_PIF_SYSKEY(KEY_CODE,KEY_VALUE,KEY_NAME,MAX_VALUE,KEY_TYPE)
VALUES('T_CARDVER',1,'卡信息版本表',999999,'1');

CREATE TRIGGER YKT_CUR.TR_CARDVER1
  AFTER
  INSERT
  ON YKT_CUR.T_TIF_BLACK_SHEET
  REFERENCING
    NEW AS NEW_ROW
  FOR EACH ROW
  MODE DB2SQL
begin atomic
DECLARE curr_day varchar(8);
DECLARE verno varchar(12);
set curr_day=yktinst1.ts_fmt(current timestamp,'yyyymmdd');
for mycur as 
select ykt_cur.lpad(rtrim(char(int(key_value))),6,'0') as verkey from ykt_cur.t_pif_syskey where key_code='T_CARDVER'  do
set verno = mycur.verkey;	
INSERT INTO YKT_CUR.T_CARDVER(ACCDATE,CARDVERNO,CARDNO,CARDPHYID,CARDVERTYPE,ADDDELFLAG,STATUS)
SELECT curr_day,substr(curr_day,3,6)||verno,t.card_id,t.physical_no,
case when new_row.is_ad=0 then 3 
when new_row.is_ad=1 then 6
when new_row.is_ad=2 then 2
when new_row.is_ad=9 then 5
when new_row.is_ad=8 then 9
end,1,'0' FROM YKT_CUR.T_PIF_CARD T
WHERE T.CARD_ID=new_row.card_id;
update ykt_cur.t_pif_syskey set key_value=int(verno)+1 where key_code='T_CARDVER';
end for;
end;


CREATE TRIGGER YKT_CUR.TR_CARDVER2
  AFTER
  INSERT
  ON YKT_CUR.T_TIF_CUT_INFO_UPDATE
  REFERENCING
    NEW AS NEW_ROW
  FOR EACH ROW
  MODE DB2SQL
begin atomic
DECLARE curr_day varchar(8);
DECLARE verno varchar(12);
if new_row.flag>0 then
set curr_day=yktinst1.ts_fmt(current timestamp,'yyyymmdd');
for mycur as 
select ykt_cur.lpad(rtrim(char(int(key_value))),6,'0') as verkey from ykt_cur.t_pif_syskey where key_code='T_CARDVER'  do
set verno = mycur.verkey;
INSERT INTO YKT_CUR.T_CARDVER(ACCDATE,CARDVERNO,CARDNO,CARDPHYID,CARDVERTYPE,ADDDELFLAG,STATUS)
SELECT curr_day,substr(curr_day,3,6)||verno,t.card_id,t.physical_no,
case when new_row.flag=1 then 2 
when new_row.flag=2 then 1
when new_row.flag=3 then 8
when new_row.flag=4 then 5
end,1,'0' FROM YKT_CUR.T_PIF_CARD T
WHERE T.CARD_ID=new_row.card_id;
update ykt_cur.t_pif_syskey set key_value=int(verno)+1 where key_code='T_CARDVER';
end for;
end if;
end;

#SYNC 10;