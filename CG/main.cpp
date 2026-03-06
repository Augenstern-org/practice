#include <QCoreApplication>
#include <QtGlobal>
#include <QDebug>

//1.字符串初始化
void demo1()
{
    //1.1直接复制
    QString str1 = "init";
    qDebug()<<str1;

    //1.2索引赋值
    QString str2;
    str2.resize(1);
    str2[0]='0';
    qDebug()<<str2;

    //1.3构造赋值
    QString str3(str2);

    //1.4单字符初始化
    QString str4(static_cast<QChar>(0x01));

    //1.5char数组初始化
    QChar p[5] = {'1','1','1',static_cast<QChar>(0x30)};
    const  char* pstr = "test";
    QString str5(p,5);
    QString str6(pstr);
    qDebug()<<str5;
    qDebug()<<str6;

}

//2.字符串拼接
void demo2()
{
    QString  str1 = "apple";
    QString  str2 = "pen";

    //2.1使用重载+
    QString str3 = str1+str2;
    //2.2调用append
    QString str4 = str1.append(str2);
    //2.3调用asprintf函数
    QString str5 = QString::asprintf("%s,%s",str1.data(),str2.data());
    //2.4调用arg函数
    QString str6 = QString("%1%2").arg(str1).arg(str2);
}

//3.字符串插入
void demo3()
{
    QString str = "helloworld";

    //3.1.insert 字符串
    str.insert(0,"123");
    qDebug()<<str;

    //3.2 insert 插入字符
    str = "helloworld";
    str.insert(1,'a');
    qDebug()<<str;

}

//4.字符串转数字
void demo4()
{
    QString str1 = "123";
    qDebug()<<str1.toUInt();

    QString str2 = "1.1";
    qDebug()<<str2.toFloat();

}

//5.数字转字符串
void demo5()
{
    float f1 = 1.234f;
    quint32 uit = 1234;

    //转字符串
    qDebug()<<QString::asprintf("%f",f1);

    //保留2位有效数字
    qDebug()<<QString::asprintf("%.2f",f1);
    qDebug()<<QString::number(f1,'f',2);

    //转换16进制
    qDebug()<<QString::number(uit,16);
    //转换8进制
    qDebug()<<QString::number(uit,8);

}

//6.字符串统计
void demo6()
{
    QString str = "hellohellohello";
    qDebug()<<str.count("h");

}

//7.字符串查找
void demo7()
{
    QString str ="11223344";

    //正序查找
    qDebug()<<str.indexOf("1");

    //倒叙查找
    qDebug()<<str.lastIndexOf("1");

    //查找char 0x32 是 2
    qDebug()<<str.indexOf(static_cast<char>(0x32));

    //判断是否包含
    qDebug()<<str.contains("22");


    QString str2 = "Bananas";

    //判断是否以什么开头,区分大小写
    str2.startsWith("Ban",Qt::CaseSensitive);

    //判断是否以什么开头,不区分大小写
    str2.startsWith("ban",Qt::CaseInsensitive);
    str2.startsWith("Car",Qt::CaseSensitive);
}

//8.16进制字符串 转QByteArray
char char2hex(char v)
{
    if(v >= '0' && v <= '9')
    {
        v -= '0';
    }
    else if(v >= 'a' && v <= 'f')
    {
        v = v - 'a' + 10;
    }
    else if( (v >= 'A' && v <= 'F'))
    {
        v = v - 'A' + 10;
    }

    return v;
}



QByteArray hexStringtobytearray(QString strHex)
{
    bool isAddZero = (strHex.size()%2) > 0;
    if(isAddZero)
    {
        strHex.insert(0,QString("0"));
    }
    QByteArray ret;

    char hcode, lcode, val;

    for(quint16 i=0; i<strHex.length(); i+=2)
    {
        hcode = char2hex(strHex.at(i).unicode());
        lcode = char2hex(strHex.at(i+1).unicode());
        val = ((hcode << 4)&0xF0) | (lcode & 0x0F);
        ret.push_back(val);
    }
    return ret;
}

void demo8()
{
    QString str = "AABB12";
    QByteArray arr = hexStringtobytearray(str);
}

//9.判断字符串是否为空
void demo9()
{
    //字符串没有字符
    QString().isEmpty();            // returns true
    QString("").isEmpty();          // returns true
    QString("x").isEmpty();         // returns false
    QString("abc").isEmpty();       // returns false

    //字符串为空
    QString().isNull();             // returns true
    QString("").isNull();           // returns false
    QString("abc").isNull();        // returns false
}
//10.字符串截取
void demo10()
{
    QString str1 = "helloworld";

    //从位置2开始截取，截取3个字符
    QString str2 = str1.mid(2, 3);//"llo"

    //从位置3开始截取，截取到最后
    QString str3 = str1.mid(3);//"loworld"

    //左边开始1个
    QString str4 = str1.left(1);//"h"
    //右边开始1个
    QString str5 = str1.right(1);//"d"

    //前3个
    QString str6 = str1.first(3);//"hel"

    //删除末尾2个
    QString str7;
    str7.chop(2);
    qDebug()<< str7;//"hello wor"
}

//11.以指定字符对字符串进行分割，将分割后的某一段取出
void demo11()
{
    QString str;
    QString csv = "forename,middlename,surname,phone";
    QString path = "/usr/local/bin/myapp"; // 第一个字段是空的
    QString::SectionFlag flag = QString::SectionSkipEmpty;

    //以“,”为分隔符，将从左往右的第2段返回
    str = csv.section(',', 2, 2);   // str == "surname"
    qDebug() <<str;
    //以“/”为分隔符，将从左往右的第3段到第4段返回
    str = path.section('/', 3, 4);  // str == "bin/myapp"
    qDebug() <<str;
    //以“/”为分隔符，将从左往右的第3段(忽略前面的空字段)
    str = path.section('/', 3, 3, flag); // str == "myapp"
    qDebug() <<str;

    //前面符号表示从右往左计数
    str = csv.section(',', -3, -2);  // str == "middlename,surname"
    str = path.section('/', -1); // str == "myapp"
}

//12.字符串删除
void demo12()
{
    //example 1
    QString str1="hello world";
    str1.clear();


    //example 2
    QString str2="hello world";
    str2="";
}

//13.字符串替换
void demo13()
{
    QString str = "helloworldhelloworld";
    //替换所有的h为Q
    str.replace("h","Q");


    QString str1 = "Say yes!";
    QString str2 = "no";

    //从位置4开始，替换3个字符
    str1.replace(4, 3, str2); // str1 == "Say no!"
}
//14.字符串分割
void demo14()
{

    QString str = QStringLiteral("a,,b,c");
    QStringList list1 = str.split(QLatin1Char(','));
     // list1: [ "a", "", "b", "c" ]

    //过滤空
    QStringList list2 = str.split(QLatin1Char(','), Qt::SkipEmptyParts);
     // list2: [ "a", "b", "c" ]
}

//15.字符串比较
void demo15()
{
    int x = QString::compare("aUtO", "AuTo", Qt::CaseInsensitive);  // x == 0
    int y = QString::compare("aUtO", "AuTo", Qt::CaseSensitive);    // x > 0

    int z = QString::compare("auto", "Car", Qt::CaseSensitive);     // y > 0
    int k = QString::compare("auto", "Car", Qt::CaseInsensitive);   // z < 0

    bool ret =  QString ("123") == QString("123");
}

//16.字符串长度
void demo16()
{
    QString str = "hello";

    //输出字符个数
    qDebug()<<str.length();

    //返回内部char个数
    qDebug()<<str.size();
    qDebug()<<str.count();

}

//17.大小写转换
void demo17()
{
    QString str = "ABCDEF";
    //小写
    qDebug()<<str.toLower();
    //转大写
    qDebug()<<str.toUpper();

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();
    demo6();
    demo7();
    demo8();
    demo9();
    demo10();
    demo11();
    demo12();
    demo13();
    demo14();
    demo15();
    demo16();
    demo17();
    return a.exec();
}
