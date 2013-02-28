#!/usr/bin/env
# -*- coding: utf-8 -*-
import sys,getopt,os
import cx_Oracle


class DBActGen:
    VERSION="1.0"
    def __init__(self):
        os.environ["NLS_LANG"] = "SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
        self.dbname=''
        self.dbuser=''
        self.dbpswd=''
        self.output_dir='.'
        if os.environ.has_key('YKT_DBNAME'):
            self.dbname=os.environ["YKT_DBNAME"]
        if os.environ.has_key('YKT_USER'):
            self.dbuser=os.environ['YKT_USER']
        if os.environ.has_key('YKT_PWD'):
            self.dbpswd=os.environ['YKT_PWD']
        self.cursor=None
        self.connect=None
        
    def __print_usage(self):
        print "Version : ",DBActGen.VERSION
        print "DBActGen.py [-h] | [-n dbname] [-u dbuser] [-p dbpassword] [-o output dir] table1 table2 ..."
        
    def __connect_to_db(self):
        if self.dbname == '' or self.dbuser == '':
            print "DB name or user name is empty"
            sys.exit(1)
            
        try:
            self.connect = cx_Oracle.Connection(self.dbuser + "/" + self.dbpswd + "@" + self.dbname)
            self.cursor = self.connect.cursor()
        except cx_Oracle.DatabaseError, exc:
            error, = exc.args
            print "连接数据库失败[ORA-%d][%s]" % (error.code,error.message)
            if self.connect <> None:
                self.connect.close()
            return False
        return True
        
    
    def __check_output_dir(self):
        if len(self.output_dir) == 0:
            return False
        if os.path.exists(self.output_dir):
            if os.path.isdir(self.output_dir):
                return True
        else:
            os.makedirs(self.output_dir)
            return True
        return False
    
    def __get_actfile_name(self,schema,objname):
        fname = objname.lower()
        s=schema.lower()
        if fname[0:2] == 't_':
            fname = fname[2:]
        if schema == self.dbuser.upper():
            return fname+'.act'
        else:
            return s+fname+'.act'
        
    def __output_2_file(self,schema,objname,actstr):
        fname = self.__get_actfile_name(schema,objname)
        fullname = os.path.join(self.output_dir,fname)
        
        overwrite = False
        if os.path.exists(fullname):
            if os.path.isfile(fullname):
                aws = raw_input('file [%s] already exists, overwrite?(N/(A)ppend/(Y)es)' % fname)
                if aws in ('Y','y','yes','YES'):
                    overwrite = True
                elif aws in ('a','A'):
                    overwrite = False
                else:
                    print "ignore file [%s]" % fname
                    return False
            else:
                return False
        handle = None
        if overwrite:
            handle = open(fullname,'w+b')
        else:
            handle = open(fullname,'a+b')
        handle.write(actstr)
        handle.close()
        print "generator act file [%s] success" % fname
        return True
        
    def __gen_act(self,schema,objname):
        sql = "select column_name,data_type,data_length,data_precision,data_scale \
                from all_tab_columns where owner='%s' and TABLE_NAME='%s'" % (schema,objname)
                
        sql2 = "select a.column_name from all_cons_columns a, all_constraints b \
                where a.owner=b.owner and a.table_name=b.table_name and b.constraint_type='P' and \
                a.constraint_name=b.constraint_name and b.owner='%s' and b.table_name='%s' " % (schema,objname)
                
        rows = None
        try:
            rows = self.cursor.execute(sql2)
        except cx_Oracle.DatabaseError, exc:
            error, = exc.args
            print "查询数据库失败[ORA-%d][%s]" % (error.code,error.message)
            return False
        
        primary_keys = []
        for row in rows:
            primary_keys.append(row[0])
            
            
        try:
            rows = self.cursor.execute(sql)
        except cx_Oracle.DatabaseError, exc:
            error, = exc.args
            print "查询数据库失败[ORA-%d][%s]" % (error.code,error.message)
            return False
            
        begin_act = 'create table %s \n( \n' % objname
        action_act = 'begin \naction modename %s end \n' \
                    'action add end \n' % schema
        
        delete_act = ''
        update_act = ''
        read_act = ''
        end_act = 'end\n'
        fld_act = ''
        is_first = True
        for row in rows:
            colname=row[0]
            coltype=row[1]
            datalen=row[2]
            datapri=row[3]
            datascale=row[4]
            
            typestr=''
            if coltype == 'NUMBER':
                if datapri > 0:
                    if datascale > 0:
                        typestr='NUMBER(%d,%d)' % (datapri,datascale)
                    else:
                        typestr='NUMBER(%d)' % datapri
                else:
                    typestr='NUMBER '
            elif datapri > 0 or datascale > 0:
                typestr = coltype
            else:
                typestr = '%s(%d)' % (coltype,datalen)
            #print "colname [%s]" % colname
            if is_first:
                fldstr = '%s %s ' % (colname,typestr)
                is_first = False
            else:
                fldstr = ', \n%s %s ' % (colname,typestr)
            fld_act += fldstr
        
        if is_first:
            print "table [%s.%s] not exists" % (schema,objname)
            return False
        begin_act += fld_act + '\n)\n'
        
        if len(primary_keys) > 0:
            all_keyfld = ''
            for x in primary_keys:
                all_keyfld += ' ' + x
            
            read_act = 'action read_by %s end\n' % all_keyfld
                       
            update_act = 'action update_by %s end\n' % all_keyfld
                          
            delete_act = 'action del_by %s end\n' % all_keyfld 
            
            update_act += 'action read_lock_by c0 %s end\n' % all_keyfld + \
                           'action update_lock_by c0 end\n' \
                           'action del_lock_by c0 end\n' \
                           'action free_lock_by c0 end\n'

        action_act += read_act + delete_act + update_act
            
           
        act_str = begin_act + action_act + end_act
                
        return self.__output_2_file(schema,objname,act_str)
        
    def __gen_tables(self,tables):
        for tbl in tables:
            tbl_flds = tbl.split('.')
            schema=self.dbuser.upper()
            objname=''
            if len(tbl_flds)==1:
                objname = tbl_flds[0]
            elif len(tbl_flds) == 2:
                objname = tbl_flds[1]
                schema = tbl_flds[0]
            else:
                print "object [%s] error" % tbl
                continue
            objname = objname.upper()
            self.__gen_act(schema,objname)
                
        
    def gen_dbact(self,argc):
        args,tables = getopt.getopt(argc,':n:u:p:o:')
        for t,v in args:
            if t == "-n":
                self.dbname = v
            elif t == "-u":
                self.dbuser = v
            elif t == "-p":
                self.dbpswd = v
            elif t == '-o':
                self.output_dir = v
            elif t == "-h":
                self.__print_usage()
                sys.exit(0)
        
        if len(tables) == 0:
            self.__print_usage()
            sys.exit(0)
        
        if not self.__check_output_dir():
            print "output directory not exists[%s]" % self.output_dir
            sys.exit(1)
            
        # try connect to database
        if not self.__connect_to_db():
            sys.exit(1)
            
        self.__gen_tables(tables)
        
        if self.connect <> None:
            self.connect.close()
            

if __name__ == "__main__":
    gen = DBActGen()
    gen.gen_dbact(sys.argv[1:])
    