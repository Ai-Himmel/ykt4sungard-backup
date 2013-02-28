#!/usr/bin/env
# -*- coding: utf-8 -*-
import sys

class CalcBankCard:
    def __init__(self,bankno):
        self.bankno=bankno
        self.checkbit=0
        
    def calc(self):
        oddnum=[] # ����λ
        evennum=[] # ż��λ
        for i in range(len(self.bankno)):
            if i % 2 == 0:
                oddnum.append(int(self.bankno[i]) * 2)
            else:
                evennum.append(int(self.bankno[i]))
        
        sum = 0
        # ����λ ʮλ + ��λ
        for o in oddnum:
            while o > 0:
                sum += o % 10
                o = o / 10
        # ż��λֱ�����
        for o in evennum:
            sum += o
            
        # sum ����У��λ֮���ܱ� 10 ����
        if sum % 10 == 0:
            self.checkbit = 0
        else:
            self.checkbit = 10 - (sum % 10)
        return self.checkbit

def checkBank(bankno):
    bank = CalcBankCard(bankno)
    checkbit = bank.calc()
    print "No: %s  checkbit: %d" % (bankno,checkbit)
 
def calcBankInput():
    while True:
        prompt="�����̻��Ų��س�����������ֱ�ӻس� :"
        input = raw_input(prompt)
        if len(input) == 0:
            break
        checkBank(input)
        print "==============================================================="
        
if __name__ == "__main__":
    #bankno=["622588141420743","000000000000000","19000001","19000002","19000003","190000001","190000002","190000003"]
    #for b in bankno:
    #    checkBank(b)
    if len(sys.argv) > 1:
        for b in sys.argv[1:]:
            checkBank(b)
    else:
        calcBankInput()
    