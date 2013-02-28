create or replace procedure p_gencardlist(v_cardid  IN t_card.cardid%TYPE,
                                          v_makebatchno IN t_cardlist.batchno%TYPE) is
begin
  begin
    insert into t_cardlist
    select a.cardasno,
           v_makebatchno,
           a.cardno,
           a.cardphyid,
           a.issueunit,
           b.custname,
           b.idtype,
           b.idno,
           b.birthday,
           b.height,
           b.sex,
           b.tel,
           b.mobile,
           b.email,
           b.unitname,
           b.married,
           b.education,
           b.politics,
           b.incomesrc,
           b.country,
           b.nation,
           b.native,
           b.domiciletype,
           b.domicile,
           b.livereason,
           b.addr,
           b.livedate,
           b.arrivaldate,
           c.photo,
           0,
           0,
           to_char(sysdate, 'YYYYMMDDHH24MISS'),
           ''
      from t_card a
      left join t_customer b
        on a.custid = b.custid
      left join t_photo c
        on a.custid = c.custid
     where a.cardid = v_cardid; --and a.status=6;
  end;
end p_gencardlist;