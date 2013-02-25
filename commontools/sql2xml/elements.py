"""This module define two class which represent table
and field being parsed from SQL.
"""
#$Id: elements.py 3 2003-11-17 08:45:14Z cash $	


class Table:
    def __init__(self,name='',comment=''):
        self.name = name
        self.comment = comment
        self.__fields = {}

    def addField(self , field):
        self.__fields[field.name] = field

    def getFields(self):
        return self.__fields

    def removeField(self,fldName):
        f = self.__fields[fldName]
        del self.__fields[fldName]
        return f

class Field:
    def __init__(self,name,type,length,comment='',
                 primarykey=False,default='',notnull=False):
        self.name = name
        self.type = type
        self.length = length
        self.default = default
        self.notnull = notnull
        self.comment = comment
        self.primarykey = primarykey

    def setPrimaryKey(self,isPK):
        self.primarykey = isPK
        self.notnull = isPK

def test():
    f1 = Field('field1','varchar',10)
    f2 = Field('field2','integer',8)
    tbl = Table('table1')
    # test add field
    tbl.addField(f1)
    tbl.addField(f2)
    flds = tbl.getFields()
    for x , f in flds.items():
        print "Field [ %s ] with type [ %s ]" % (x , f.type)

    # test remove field
    f = tbl.removeField(f1.name)
    print "Remove field: %s" % f.name

    f = tbl.removeField(f2.name)
    print "Remove field: %s" % f.name

if __name__ == "__main__":
    test()
    
        
