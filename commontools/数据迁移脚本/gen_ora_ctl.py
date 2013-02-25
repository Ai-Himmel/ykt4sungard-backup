#!/usr/bin/env python

import DB2
import sys,getopt,os

exec_name = sys.argv[0]
db_name = ''
db_user = ''
db_pwd = ''


def _parse_table_name(full_name):
    p = full_name.rfind('.')
    if p != -1:
        return full_name[p+1:]
    return full_name

def _gen_fields_from_db(cursor,writer,table_name):
    stmt = "select * from %s where 1 <> 1" % table_name
    short_name = _parse_table_name(table_name)
    cursor.execute(stmt)
    if cursor.description:
        writer.write("LOAD DATA \nINFILE '%s.txt'\nTRUNCATE\nINTO TABLE %s\n" % (short_name,table_name))
        writer.write("FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"'\n")
        writer.write("TRAILING NULLCOLS\n(\n")
        x = 0
        for fld in cursor.description2:
            #print fld
            fld_type = fld[1]
            if fld_type == 'VARCHAR':
                if fld[2] >= 255:
                    fld_type = 'CHAR(%d)' % fld[2]
                else:
                    fld_type = 'CHAR'
            elif fld_type == 'CHAR':
                if fld[2] >= 255:
                    fld_type = 'CHAR(%d)' % fld[2]
                else:
                    fld_type = 'CHAR'
            elif fld_type == 'NUMBER':
                fld_type = 'INTEGER EXTERNAL'
            elif fld_type == 'INTEGER':
                fld_type = 'INTEGER EXTERNAL'
            elif fld_type == 'DOUBLE':
                fld_type = 'DECIMAL EXTERNAL'
            elif fld_type == 'FLOAT':
                fld_type = 'DECIMAL EXTERNAL'
            elif fld_type == 'DECIMAL':
                fld_type = 'DECIMAL EXTERNAL'
            elif fld_type == 'BIGINT':
                fld_type = 'DECIMAL EXTERNAL'
            else:
                print "field [%s] type [%s] ignored " % (fld[0],fld_type)
                continue
            x+=1
            fld_name = fld[0]
            if fld_name == 'LEVEL':
                fld_name = '"LEVEL"'
            if x > 1:
                writer.write(",%s %s\n" % (fld_name,fld_type))
            else:
                writer.write("%s %s\n" % (fld_name,fld_type))

        writer.write(")\n")
        return 0

    return -1


def _print_usage():
    print "Usage: %s -d database -u userid -p passwd -t tablename -o outputfile " % os.path.basename(exec_name)
    sys.exit(1)

def _do_main(argv):
    global db_name,db_user,db_pwd
    exp_tbls = []
    output_file = 'dbctl.ctl'
    optlist,args = getopt.getopt(argv,'d:u:p:t:o:')
    for x,v in optlist:
        if x == '-d':
            db_name = v
        elif x == '-u':
            db_user = v
        elif x == '-p':
            db_pwd = v
        elif x == '-t':
            exp_tbls.append(v.upper())
        elif x == '-o':
            output_file = v
        else:
            print x
            _print_usage()

    #print " -d %s -u %s -p %s -o %s " % (db_name,db_user,db_pwd,output_file) 
    #print exp_tbls
    writer = None
    try:
        writer = open(output_file,"w+")
    except:
        print "cannot open file [%s] !!" % output_file
        sys.exit(1)

    conn = None
    cur = None
    try:
        conn = DB2.connect(db_name,db_user,db_pwd)
        cur = conn.cursor()
    except:
        print "Cannot connect to database "
        sys.exit(1)

    for x in exp_tbls:
        print "generate table [%s] ... " % x
        if _gen_fields_from_db(cur,writer,x) == 0:
            print "generate success!!"
        else:
            print "generate failed!!"

    cur.close()
    conn.close()
    writer.close()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        _print_usage()

    _do_main(sys.argv[1:])

