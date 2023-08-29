/**
 * Calc V2
 *
 * By ABacker 9/18/2015
 */

#include "Calc.h"
#include "Algorithm.h"
#include "Common.h"
#include <cstring>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

bool SYMBOL_DEBUG = true;

static const char *helpInf = "Calc V2.0    2015    @ABacker\n"
                             "\n"
                             "##运算符优先级:\n"
                             "0	#\n"
                             "1	^(异或)		|(或)		&(与)		~(取反)\n"
                             "2	+		-		++(正)		--(负)\n"
                             "3	*		/		%%(取模)\n"
                             "4	**(乘方)	// (开方)\n"
                             "5	math_func\n"
                             "6	!(阶乘)		'(角度转弧度)\n"
                             "其中math_func包括:\n"
                             "pow(乘方),sqrt(方根),sin,cos,tan,arcsin,arccos,arctan,arc'(弧度转角度),"
                             "gcd(最大公约数),lcm(最小公倍数),log,ln\n"
                             "\n"
                             "##特殊命令:\n"
                             "cls: 清屏\n"
                             "debug on/debug off: 打开/关闭调试消息显示\n"
                             "\n"
                             "输入\"demo\"获取示例...\n";

void demo(const std::string &s, const char *ps = NULL) {
    bool SpecialCMD(const std::string &s);

    if (s == "")
        return;
    std::cout << ">" << s;
    if (ps != NULL) {
        int nSpace = 40 - (int)s.size();
        while (--nSpace && nSpace > 0)
            printf(" ");
        std::cout << "[" << ps << "]";
    }
    std::cout << std::endl;
}

void demo() {
    std::string s;
    SYMBOL_DEBUG = false;
    s = "3/2 + 1/3 + 1/(-3)";
    demo(s, "运算式中可以有空格"); // 1.5 3/2
    s = "3/(-2)";
    demo(s, "负号需要用括号括起来"); // -1.5 -3/2
    s = "1-(1+2)*3";
    demo(s, "末尾可以不加\"=\"符号"); // -8
    s = "(1+2)*3=";
    demo(s, "末尾可以加\"=\"符号"); // 9
    s = "2/{[1-(1+2)]*3}=";
    demo(s, "可以使用圆括号,方括号和花括号"); // -0.333 -1/3
    s = "10-3*(2/1-(6*2+(21+3/5)*8/3)*(-2))+8*2";
    demo(s, "括号嵌套"); // -397.6
    printf("\n");

    printf("##数学函数示例:\n");
    s = "pow(2,3)";
    demo(s, "乘方函数示例,2的3次方"); // 8
    s = "log(2,8)";
    demo(s, "对数函数示例,以2为底取8的对数"); // 3
    s = "ln(4)";
    demo(s, "以自然对数e=2.7182..为底的对数函数示例"); // 1.38629
    s = "sqrt(36)";
    demo(s, "平方根函数示例,36的平方根"); // 6
    s = "lcm(9,12)";
    demo(s, "最大公约数函数示例"); // 3
    s = "gcd(9,12)";
    demo(s, "最小公倍数函数示例"); // 36
    printf("\n");

    printf("##三角函数示例:\n");
    s = "sin(30')";
    demo(s,
         "使用sin,cos和tan函数参数类型为弧度,注意加'(角度转弧度)标识符"); // 0.5
    s = "cos(60')";
    demo(s); // 0.5
    s = "arc'(arccos(0.5))";
    demo(s,
         "使用arcsin,arccos和arctan函数运算结果为弧度,注意加arc'(弧度转角度)"
         "函数"); // 60
    printf("\n");

    printf("##特殊函数示例:\n");
    s = "hex(9*3)";
    demo(s, "十六进制输出函数示例"); // 27 1b
    s = "radix(20,cos(45'))";
    demo(s, "结果保留20位小数输出,此程序三角函数,开方函数和对数函数的精度最低为1e-"
            "12");
    s = "isprime(30+1)";
    demo(s,
         "判断数是否为质数,对大于等于1e9的数采用10000次费马测试方法"); // true
    printf("\n");

    printf("##自定义变量示例:(注:程序会在运算过程中依次循环产生A-Z变量,"
           "计算时可以使用这些变量)\n");
    s = "pi=3.14159";
    demo(s, "定义变量pi");
    s = "r=50.2";
    demo(s, "定义变量r");
    s = "2*pi*r";
    demo(s, "使用变量pi和r");
    s = "var";
    demo(s, "查看已定义变量");
    printf("\n");

    SYMBOL_DEBUG = true;
}

bool SpecialCMD(std::string &s, bool &quit) {
    RemoveSpaces(s);

    if (s == "")
        return true;
    else if (s == "exit" || s == "quit") {
        quit = true;
        return true;
    } else if (s == "cls") { // 清屏
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        return true;
    }

#ifdef _WIN32
    else if (s == "calc") { // 调用系统计算器
        system("calc");
        return true;
    }
#endif
    else if (getVar(s, 0) == "hex") { // 十六进制输出
        printHex(Calc(s.substr(4, s.size() - 5), false));
        return true;
    } else if (getVar(s, 0) == "radix") { // 以n位小数形式输出
        int pos = 6;
        unsigned int n = (unsigned int)getFigure(s, pos);
        printRadix(Calc(s.substr(pos + 2, s.size() - pos - 3), false), n);

        return true;
    } else if (getVar(s, 0) == "isprime") { // 判断数字是否为质数
        double ans = Calc(s.substr(7), false);
        printf(isPrime(ans) ? ("\t%" LLD " true\n") : ("\t%" LLD " false\n"), (long long)ans);

        return true;
    } else if (s == "debugon" || s == "debug on") { // 打开debug
        SYMBOL_DEBUG = true;
        return true;
    } else if (s == "debugoff" || s == "debug off") { // 关闭debug
        SYMBOL_DEBUG = false;
        return true;
    } else if (s == "help") { // 打开帮助信息
        printf("%s", helpInf);
        return true;
    } else if (s == "var") { // 打印全部自定义变量
        cache.printAll();
        return true;
    } else if (s == "demo") { // 显示示例
        demo();
        return true;
    } else if (isLtr(s[0])) { // 变量赋值
        int pos = 0;
        std::string var = getVar(s, pos);
        if (pos != -1 && (s[pos + 1] == '=')) {
            cache.set(var, Calc(s.substr(pos + 2, s.size() - pos - 2), false));

            return true;
        }
    }

    return false;
}

int main() {
#ifdef _WIN32
    system("chcp 65001");
    system("cls");
#endif

    std::cout << "输入\"help\"获取帮助信息...\n" << std::endl;

    bool quit = false;
    std::string s;
    while (printf(">"), getline(std::cin, s)) {
        try {
            if (!SpecialCMD(s, quit)) {
                Calc(s);
            } else if (quit) {
                break;
            }
        } catch (std::runtime_error &e) { std::cout << "\t" << e.what() << std::endl; } catch (...) {
            std::cout << "\tUnknown error" << std::endl;
        }
    }
    return 0;
}
