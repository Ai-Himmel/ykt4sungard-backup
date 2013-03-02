package com.kingstargroup.fdykt.util;

import java.io.*;

public class RSA 
{
    private int p=47;
    private int q=59;
    private long n=2773;
    private long m=2668;
    
    private long public_key=63;//����
    private long private_key=847;//�ܳ�
    
    private long text=0;//����
    private long secretword=0;//����
    private long word=0;//���ܺ�����
    
    //�ж��Ƿ�Ϊ����
    public boolean primenumber(long t)
    {
        long k=0;
        k=(long)Math.sqrt((double)t);
        boolean flag=true;
        for(int i=2;i<=k;i++)
        {
            if((t%i)==0)
            {
                flag = false;
                break;
            }
        }
        return flag;
    }
    //����PQ
    public void inputPQ()throws Exception
    {
//        do{
//                System.out.println("����������p: ");
//                BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
//                String br=stdin.readLine();
//                this.p=Integer.parseInt(br);
//         }
//        while(!primenumber(this.p));
//        do{
//            System.out.println("����������q: ");
//            BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
//            String br=stdin.readLine();
//            this.q=Integer.parseInt(br);
//        }
//        while(!primenumber(this.q));
    	
        this.n=this.p*this.q;
        this.m=(p-1)*(q-1);
        System.out.println("�����������ĳ˻�Ϊp*q��"+this.n);
        System.out.println("���õ�С�ڣβ�����λ��ص������ĸ���Ϊm=(p-1)(q-1)��"+this.m);
    }
    //�����Լ��
    public long gcd(long a,long b)
    {
        long gcd;
        if(b==0)
            gcd=a;
        else
            gcd=gcd(b,a%b);
//        System.out.println("gcd:"+gcd);
        return gcd;
        
    }
    //���빫��
    public void getPublic_key()throws Exception
    {
        do{
            System.out.println("������һ����Կ��ֵ�����ֵҪ��С��m���Һ�m���ʣ� ");
            BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
            String br=stdin.readLine();
            this.public_key=Long.parseLong(br);
        }while((this.public_key >= this.m) || (this.gcd(this.m,this.public_key)!=1));
        System.out.println("��ԿΪ��"+this.public_key);
    }
    //����õ��ܳ�
    public void getPrivate_key()
    {
        long value=1;
        for(long i=1;;i++)
        {
            value=i*this.m+1;
//            System.out.println("value:  "+value);
            if((value%this.public_key==0)&& (value/this.public_key < this.m))
            {
                this.private_key=value/this.public_key;
                break;
            }
        }
        System.out.println("������һ��˽ԿΪ��"+this.private_key);
    }
    //��������
    public void getText()throws Exception
    {
        System.out.println("���������ģ�");
        BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
        String br=stdin.readLine();
        this.text=Long.parseLong(br);
    }
    //���ܡ����ܼ���
    public long colum(long y,long n,long key)
    {
        long mul = 0;
        if(key==1)
            mul=y%n;
        else 
            mul=y*this.colum(y,n,key-1)%n;
        return mul;
    }
    
    //���ܺ����
    public void pascolum()throws Exception
    {
//        this.getText();
    	for(int i=10;i<20;i++){
    		this.text = i;
            System.out.println("��������Ϊ: "+this.text);
            //����
            this.secretword=this.colum(this.text,this.n,this.private_key);
            System.out.println("���õ�����Ϊ��"+this.secretword);
            //����
            this.word=this.colum(this.secretword,this.n,this.public_key);
            System.out.println("���ܺ����õ�����Ϊ��"+this.word);
    	}

        
    }
    
    public long ency(long y){
    	this.secretword = this.colum(y, n, this.private_key);
    	return secretword;
    }
    
    public long decode(long y){
    	this.word = this.colum(y, n, this.public_key);
    	return word;
    }
    
    
    public static void main(String []args)throws Exception
    {
        RSA t = new RSA();
//        t.inputPQ();
//        t.getPublic_key();
//        t.getPrivate_key();
        t.pascolum();
    }

}


